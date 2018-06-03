#include "stdafx.h"
#include "DataModelingModule.h"

#include "SSUtils/StringUtils.h"

namespace CARSDK
{
	const std::string DataModelingModule::DescriptionInfo("description");
	const std::string DataModelingModule::BaesTypePrefix("b");

	std::shared_ptr<DataModelingModule> DataModelingModule::instance(void)
	{
		static std::shared_ptr<DataModelingModule> ret(new DataModelingModule());
		return ret;
	}

	std::shared_ptr<XSDFrontend::XSDModel> DataModelingModule::normalize(const std::vector<Info>& infos, std::shared_ptr<XSDFrontend::XSDModel> originModel)
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

			if (info.experimentalFactorType.empty())
			{
				continue;
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

	std::shared_ptr<XSDFrontend::XSDModel> DataModelingModule::normalizeWithPublicModel(const std::vector<Info>& infos, const std::shared_ptr<XSDFrontend::XSDModel> publicModel, std::shared_ptr<XSDFrontend::XSDModel> originModel)
	{
		// to do : normalize infos to origin model and copy needed simple types from public model to origin model
		// if the type is in the origin model and public model, copy it from public model to origin model to refresh the one in origin model
		return std::shared_ptr<XSDFrontend::XSDModel>();
	}

	std::vector<DataModelingModule::Info> DataModelingModule::analyze(const std::shared_ptr<XSDFrontend::XSDModel> model)
	{
		std::vector<Info> ret;

		const auto simpleTypeModel(model->getSimpleTypeModel());
		const auto attributeModel(model->getAttributeModel());
		const auto complexTypeModel(model->getComplexTypeModel());

		for (const auto &pair : complexTypeModel->getSimpleContents())
		{
			if (pair.second->hasExAttr(ExperimentalFactorTypeAttr()))
			{
				const auto factor(pair.second);
				const auto *simpleType(simpleTypeModel->getSimpleType(factor->getBaseTypeName()));
				const auto attributeGroup(attributeModel->getAttributeGroup(factor->getAttributeGroupName()));
				const bool isDefaultTypeName();

				Info info;

				if (simpleType->getName() != (BaesTypePrefix + factor->getName()))
				{
					info.type.assign(simpleType->getName());
				}
				else if (simpleType->getSimpleType() == XSDFrontend::SimpleType::eSimpleType::tNumberType)
				{
					const auto numberType(simpleTypeModel->getNumberType(simpleType->getName()));
					info = saveSimpleType(numberType);
					info.type.assign(XSDFrontend::SimpleType::NumberType::String2Type.right.find(numberType->getBaseType())->second);
				}
				else if (simpleType->getSimpleType() == XSDFrontend::SimpleType::eSimpleType::tStringType)
				{
					const auto stringType(simpleTypeModel->getStringType(simpleType->getName()));
					info = saveSimpleType(stringType);
					info.type.assign(XSDFrontend::SimpleType::StringType::String2Type.right.find(stringType->getBaseType())->second);
				}
				else if (simpleType->getSimpleType() == XSDFrontend::SimpleType::eSimpleType::tDatetimeType)
				{
					const auto datetimeType(simpleTypeModel->getDatetimeType(simpleType->getName()));
					info = saveSimpleType(datetimeType);
					info.type.assign(XSDFrontend::SimpleType::DatetimeType::String2Type.right.find(datetimeType->getBaseType())->second);
				}
				else
				{
					return std::vector<Info>();
				}

				info.name = factor->getName();
				info.experimentalFactorType = factor->getExAttr(ExperimentalFactorTypeAttr());
				if (!factor->getDescription().empty())
				{
					info.infos.insert(std::make_pair(DescriptionInfo, factor->getDescription()));
				}

				for (const auto &exAttr : factor->getExAttrs())
				{
					if (exAttr.first != ExperimentalFactorTypeAttr())
					{
						info.attributes.insert(exAttr);
					}
				}

				ret.push_back(std::move(info));
			}
		}

		return ret;
	}

	std::shared_ptr<SSUtils::XML::Node> DataModelingModule::generateData(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::string &factorName)
	{
		return nullptr;
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

		it = info.validators.find(XSDFrontend::Token::LengthValidatorTag());
		if (it != info.validators.cend() && it->second.type() == typeid(int))
		{
			type->setLengthValidator(boost::any_cast<int>(it->second));
		}

		it = info.validators.find(XSDFrontend::Token::MinLengthValidatorTag());
		if (it != info.validators.cend() && it->second.type() == typeid(int))
		{
			type->setMinLengthValidator(boost::any_cast<int>(it->second));
		}

		it = info.validators.find(XSDFrontend::Token::MaxLengthValidatorTag());
		if (it != info.validators.cend() && it->second.type() == typeid(int))
		{
			type->setMaxLengthValidator(boost::any_cast<int>(it->second));
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
		if (it != info.validators.cend() && it->second.type() == typeid(std::vector<SSUtils::Datetime::DatetimeDuration>))
		{
			const std::vector<SSUtils::Datetime::DatetimeDuration> &enums(boost::any_cast<std::vector<SSUtils::Datetime::DatetimeDuration>>(it->second));
			type->setIsEnum(true);
			for (const auto &value : enums)
			{
				type->addEnumValue(value);
			};
		}

		return type;
	}

	DataModelingModule::Info DataModelingModule::saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::NumberType> type)
	{
		Info info;

		if (type->getFractionDigits() != XSDFrontend::SimpleType::NumberType::NoDigitValidator)
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::FractionDigitsTag(), boost::any(type->getFractionDigits())));
		}
		if (type->getTotalDigits() != XSDFrontend::SimpleType::NumberType::NoDigitValidator)
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::TotalDigitsTag(), boost::any(type->getTotalDigits())));
		}

		if (type->hasMaxExclusive())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::MaxExclusiveTag(), boost::any(type->getMaxExclusive())));
		}
		if (type->hasMaxInclusive())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::MaxInclusiveTag(), boost::any(type->getMaxInclusive())));
		}
		if (type->hasMinExclusive())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::MinExclusiveTag(), boost::any(type->getMinExclusive())));
		}
		if (type->hasMinInclusive())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::MinInclusiveTag(), boost::any(type->getMinInclusive())));
		}

		if (type->getIsEnum())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::EnumValidatorTag(), boost::any(type->getEnumValues())));
		}

		return info;
	}

	DataModelingModule::Info DataModelingModule::saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::StringType> type)
	{
		Info info;

		if (!type->getPattern().empty())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::PatternTag(), boost::any(type->getPattern())));
		}
		
		if (type->getLengthValidator() != XSDFrontend::SimpleType::StringType::NoLengthValidator)
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::LengthValidatorTag(), boost::any(type->getLengthValidator())));
		}
		if (type->getMinLengthValidator() != XSDFrontend::SimpleType::StringType::NoLengthValidator)
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::MinLengthValidatorTag(), boost::any(type->getLengthValidator())));
		}
		if (type->getMaxLengthValidator() != XSDFrontend::SimpleType::StringType::NoLengthValidator)
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::MaxLengthValidatorTag(), boost::any(type->getMaxLengthValidator())));
		}

		if (type->getIsEnum())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::EnumValidatorTag(), boost::any(type->getEnumValues())));
		}

		return info;
	}

	DataModelingModule::Info DataModelingModule::saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> type)
	{
		Info info;

		if (!type->getIsEnum())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::EnumValidatorTag(), boost::any(type->getEnumValues())));
		}

		if (!type->hasMaxExclusive())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::MaxExclusiveTag(), boost::any(type->getMaxExclusive())));
		}
		if (!type->hasMaxInclusive())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::MaxInclusiveTag(), boost::any(type->getMaxInclusive())));
		}
		if (!type->hasMinExclusive())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::MinExclusiveTag(), boost::any(type->getMinExclusive())));
		}
		if (!type->hasMinInclusive())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::MinInclusiveTag(), boost::any(type->getMinInclusive())));
		}

		return info;
	}
};
