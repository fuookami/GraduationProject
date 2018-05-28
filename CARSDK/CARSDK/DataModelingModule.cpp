#include "stdafx.h"
#include "DataModelingModule.h"

#include "SSUtils/StringUtils.h"

namespace CARSDK
{
	const std::string DataModelingModule::DescriptionInfo("description");

	std::shared_ptr<DataModelingModule> DataModelingModule::instance(void)
	{
		static std::shared_ptr<DataModelingModule> ret(new DataModelingModule());
		return ret;
	}

	std::shared_ptr<XSDFrontend::XSDModel> DataModelingModule::normalize(const std::vector<Info>& infos, std::shared_ptr<XSDFrontend::XSDModel> originModel) const
	{
		if (originModel == nullptr)
		{
			originModel = XSDFrontend::XSDModel::generateNewXSDModel();
		}

		auto simpleTypeModel(originModel->getSimpleTypeModel());
		auto attributeModel(originModel->getAttributeModel());
		auto complexTypeModel(originModel->getComplexTypeModel());

		for (const auto &info : infos)
		{
			static const std::string BaesTypePrefix("b");

			if (simpleTypeModel->isSimpleType(info.name) || complexTypeModel->isComplexContent(info.name))
			{
				return nullptr;
			}

			XSDFrontend::SimpleType::ISimpleTypeInterface *baseType(nullptr);
			if (simpleTypeModel->isBaseType(info.type))
			{
				std::vector<std::string> baseTypeParts = SSUtils::String::split(info.type, XSDFrontend::Token::NamespaceSeparator());
				const std::string &baseTypeName(baseTypeParts.back());
				std::string typeName(BaesTypePrefix + info.name);

				if (XSDFrontend::SimpleType::NumberType::String2Type.left.find(baseTypeName) != XSDFrontend::SimpleType::NumberType::String2Type.left.end())
				{
					auto numberType = loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::NumberType>(new XSDFrontend::SimpleType::NumberType(typeName, XSDFrontend::SimpleType::NumberType::String2Type.left.find(baseTypeName)->second)), info);
					simpleTypeModel->getNumberTypes()[numberType->getName()] = numberType;
				}
				else if (XSDFrontend::SimpleType::StringType::String2Type.left.find(baseTypeParts.back()) != XSDFrontend::SimpleType::StringType::String2Type.left.end())
				{
					auto stringType = loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::StringType>(new XSDFrontend::SimpleType::StringType(typeName, XSDFrontend::SimpleType::StringType::String2Type.left.find(baseTypeName)->second)), info);
					simpleTypeModel->getStringTypes()[stringType->getName()] = stringType;
				}
				else if (XSDFrontend::SimpleType::DatetimeType::String2Type.left.find(baseTypeName) != XSDFrontend::SimpleType::DatetimeType::String2Type.left.end())
				{
					auto datetimeType = loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::DatetimeType>(new XSDFrontend::SimpleType::DatetimeType(typeName, XSDFrontend::SimpleType::DatetimeType::String2Type.left.find(baseTypeName)->second)), info);
					simpleTypeModel->getDatetimeTypes()[datetimeType->getName()] = datetimeType;
				}
				else
				{
					return nullptr;
				}

				baseType = simpleTypeModel->getSimpleType(typeName);
			}
			else if (simpleTypeModel->isSimpleType(info.type))
			{
				auto temp = simpleTypeModel->getSimpleType(info.type);
				auto simpleType = temp->getSimpleType();
				if (simpleType == XSDFrontend::SimpleType::eSimpleType::tNumberType
					|| simpleType == XSDFrontend::SimpleType::eSimpleType::tStringType
					|| simpleType == XSDFrontend::SimpleType::eSimpleType::tDatetimeType)
				{
					baseType = temp;
				}
				else
				{
					return nullptr;
				}
			}
			if (baseType == nullptr)
			{
				return nullptr;
			}

			std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> attrGroup;
			std::shared_ptr<XSDFrontend::ComplexType::SimpleContent> factor;

			if (complexTypeModel->isSimpleContent(info.name))
			{
				factor = complexTypeModel->getSimpleContent(info.name);
				attrGroup = attributeModel->getAttributeGroup(factor->getAttributeGroupName());
			}
			else
			{
				attrGroup.reset(new XSDFrontend::Attribute::AttributeGroup(attributeModel->getNewDefaultAttributeGroupName()));
				attrGroup->setAnonymous(true);
				attributeModel->getAttributeGroups().insert(std::make_pair(attrGroup->getName(), attrGroup));

				factor.reset(new XSDFrontend::ComplexType::SimpleContent(info.name));
				factor->setAttributeGroupName(attrGroup->getName());
				complexTypeModel->getSimpleContents().insert(std::make_pair(factor->getName(), factor));
			}

			factor->setSimpleTypeName(baseType->getName());
			factor->setBaseType(XSDFrontend::ComplexType::IComplexTypeInterface::eDerivedType::tExtension, baseType->getName());
			factor->getExAttrs().clear();
			attrGroup->getAttributes().clear();

			auto it(ExperimentalFactorType2String().right.find(info.experimentalFactorType));
			if (it == ExperimentalFactorType2String().right.end())
			{
				return nullptr;
			}
			factor->setExAttr(ExperimentalFactorTypeAttr(), info.experimentalFactorType);

			for (const auto &pair : info.infos)
			{
				if (pair.first == DescriptionInfo)
				{
					factor->setDescription(pair.second);
				}
			}

			for (const auto &pair : info.attributes)
			{
				factor->setExAttr(pair);
				auto attr = std::shared_ptr<XSDFrontend::Attribute::Attribute>(new XSDFrontend::Attribute::Attribute(pair.first, std::string("xs:string")));
				attr->setFixed(pair.second);
				attrGroup->setOrAddAttribute(attr);
			}
		}

		return originModel;
	}

	std::vector<DataModelingModule::Info> DataModelingModule::analyze(const std::shared_ptr<XSDFrontend::XSDModel> model) const
	{
		return std::vector<Info>();
	}

	std::shared_ptr<XSDFrontend::SimpleType::NumberType> DataModelingModule::loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::NumberType> type, const Info & info)
	{
		auto it(info.validators.find(XSDFrontend::Token::MaxExclusiveTag()));
		if (it != info.validators.cend() && it->second.type() == typeid(SSUtils::Math::Real))
		{
			type->setMaxExclusive(boost::any_cast<SSUtils::Math::Real>(it->second));
		}

		it = info.validators.find(XSDFrontend::Token::MaxInclusiveTag());
		if (it != info.validators.cend() && it->second.type() == typeid(SSUtils::Math::Real))
		{
			type->setMaxInclusive(boost::any_cast<SSUtils::Math::Real>(it->second));
		}

		it = info.validators.find(XSDFrontend::Token::MinExclusiveTag());
		if (it != info.validators.cend() && it->second.type() == typeid(SSUtils::Math::Real))
		{
			type->setMinExclusive(boost::any_cast<SSUtils::Math::Real>(it->second));
		}

		it = info.validators.find(XSDFrontend::Token::MinInclusiveTag());
		if (it != info.validators.cend() && it->second.type() == typeid(SSUtils::Math::Real))
		{
			type->setMinInclusive(boost::any_cast<SSUtils::Math::Real>(it->second));
		}

		it = info.validators.find(XSDFrontend::Token::EnumValidatorTag());
		if (it != info.validators.cend() && it->second.type() == typeid(std::vector<SSUtils::Math::Real>))
		{
			const auto &enums(boost::any_cast<std::vector<SSUtils::Math::Real>>(it->second));
			type->setIsEnum(true);
			for (const auto &value : enums)
			{
				type->addEnumValue(value);
			}
		}

		it = info.validators.find(XSDFrontend::Token::FractionDigitsTag());
		if (it != info.validators.cend() && it->second.type() == typeid(int))
		{
			type->setFractionDigits(boost::any_cast<int>(it->second));
		}

		it = info.validators.find(XSDFrontend::Token::TotalDigitsTag());
		if (it != info.validators.cend() && it->second.type() == typeid(int))
		{
			type->setTotalDigits(boost::any_cast<int>(it->second));
		}

		return type;
	}

	std::shared_ptr<XSDFrontend::SimpleType::StringType> DataModelingModule::loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::StringType> type, const Info &info)
	{
		auto it(info.validators.find(XSDFrontend::Token::PatternTag()));
		if (it != info.validators.cend() && it->second.type() == typeid(std::string))
		{
			type->setPattern(boost::any_cast<std::string>(it->second));
		}

		it = info.validators.find(XSDFrontend::Token::EnumValidatorTag());
		if (it != info.validators.cend() && it->second.type() == typeid(std::vector<std::string>))
		{
			const std::vector<std::string> &enums(boost::any_cast<std::vector<std::string>>(it->second));
			type->setIsEnum(true);
			for (const auto &value : enums)
			{
				type->addEnumValue(value);
			};
		}
		return type;
	}

	std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> DataModelingModule::loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> type, const Info &info)
	{
		auto it(info.validators.find(XSDFrontend::Token::MaxExclusiveTag()));
		if (it != info.validators.cend() && it->second.type() == typeid(std::string))
		{
			type->setMaxExclusive(SSUtils::Datetime::DatetimeDuration::fromString(boost::any_cast<std::string>(it->second)));
		}

		it = info.validators.find(XSDFrontend::Token::MaxInclusiveTag());
		if (it != info.validators.cend() && it->second.type() == typeid(std::string))
		{
			type->setMaxInclusive(SSUtils::Datetime::DatetimeDuration::fromString(boost::any_cast<std::string>(it->second)));
		}

		it = info.validators.find(XSDFrontend::Token::MinExclusiveTag());
		if (it != info.validators.cend() && it->second.type() == typeid(std::string))
		{
			type->setMinExclusive(SSUtils::Datetime::DatetimeDuration::fromString(boost::any_cast<std::string>(it->second)));
		}

		it = info.validators.find(XSDFrontend::Token::MinInclusiveTag());
		if (it != info.validators.cend() && it->second.type() == typeid(std::string))
		{
			type->setMinInclusive(SSUtils::Datetime::DatetimeDuration::fromString(boost::any_cast<std::string>(it->second)));
		}

		it = info.validators.find(XSDFrontend::Token::EnumValidatorTag());
		if (it != info.validators.cend() && it->second.type() == typeid(std::vector<std::string>))
		{
			const std::vector<std::string> &enums(boost::any_cast<std::vector<std::string>>(it->second));
			type->setIsEnum(true);
			for (const auto &value : enums)
			{
				type->addEnumValue(SSUtils::Datetime::DatetimeDuration::fromString(value));
			};
		}

		return type;
	}
};
