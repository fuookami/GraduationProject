#include "stdafx.h"
#include "DataModelingModule.h"
#include "SSUtils/StringUtils.h"
#include "SSUtils/MathUtils.h"
#include <boost/preprocessor.hpp>

namespace CARSDK
{
	const std::string DataModelingModule::DescriptionInfo("description");
	const std::string DataModelingModule::BaesTypePrefix("b");

	const int DataModelingModule::getEnumNumber(const FactorType & factor)
	{
		auto it(factor.validators.find(XSDFrontend::Token::EnumValidatorTag()));
		if (it == factor.validators.cend())
		{
			return 0;
		}

		if (factor.simpleType == XSDFrontend::SimpleType::eSimpleType::tNumberType
			&& it->second.type() == typeid(DataModelingModule::NumberEnumContainer))
		{
			return boost::any_cast<DataModelingModule::NumberEnumContainer>(it->second).size();
		}
		else if (factor.simpleType == XSDFrontend::SimpleType::eSimpleType::tStringType
			&& it->second.type() == typeid(DataModelingModule::StringEnumContainer))
		{
			return boost::any_cast<DataModelingModule::StringEnumContainer>(it->second).size();
		}
		else if (factor.simpleType == XSDFrontend::SimpleType::eSimpleType::tDatetimeType
			&& it->second.type() == typeid(DataModelingModule::DatetimeEnumContainer))
		{
			return boost::any_cast<DataModelingModule::DatetimeEnumContainer>(it->second).size();
		}

		return 0;
	}

	std::vector<std::string> DataModelingModule::getEnumString(const FactorType & factor)
	{
		auto it(factor.validators.find(XSDFrontend::Token::EnumValidatorTag()));
		if (it == factor.validators.cend())
		{
			return std::vector<std::string>();
		}

		std::vector<std::string> ret;
		if (factor.simpleType == XSDFrontend::SimpleType::eSimpleType::tNumberType
			&& it->second.type() == typeid(DataModelingModule::NumberEnumContainer))
		{
			const auto &values(boost::any_cast<DataModelingModule::NumberEnumContainer>(it->second));

			auto digitIt(factor.attributes.find(DigitAttr()));
			if (digitIt == factor.attributes.cend())
			{
				for (const auto &value : values)
				{
					ret.push_back(value.toString());
				}
			}
			else
			{
				SSUtils::uint32 digits = SSUtils::Math::DefaultDigits;
				if (digitIt != factor.attributes.cend() && SSUtils::String::isPositiveDecInteger(digitIt->second))
				{
					digits = std::stoul(digitIt->second);
				}

				for (const auto &value : values)
				{
					ret.push_back(value.toDecimal().second.str(digits, std::ios::fixed));
				}
			}
		}
		else if (factor.simpleType == XSDFrontend::SimpleType::eSimpleType::tStringType
			&& it->second.type() == typeid(DataModelingModule::StringEnumContainer))
		{
			const auto &values(boost::any_cast<DataModelingModule::StringEnumContainer>(it->second));
			std::copy(values.cbegin(), values.cend(), std::back_inserter(ret));
		}
		else if (factor.simpleType == XSDFrontend::SimpleType::eSimpleType::tDatetimeType
			&& it->second.type() == typeid(DataModelingModule::DatetimeEnumContainer))
		{
			const auto &values(boost::any_cast<DataModelingModule::DatetimeEnumContainer>(it->second));
			std::transform(values.cbegin(), values.cend(), std::back_inserter(ret), [](const DatetimeEnumContainer::value_type &value) 
			{
				return value.toString();
			});
		}

		return ret;
	} 

	FactorTypeGroup DataModelingModule::divideToGroup(const std::vector<FactorType>& infos)
	{
		FactorTypeGroup group;

		for (const auto &info : infos)
		{
			auto it(ExperimentalFactorType2String().right.find(info.experimentalFactorType));
			if (it == ExperimentalFactorType2String().right.end())
			{
				continue;
			}

			if (it->second == ExperimentalFactorType::ExperimentalFactor)
			{
				group.experimentalFactors.push_back(info);
			}
			else if (it->second == ExperimentalFactorType::EvaluateFactor)
			{
				group.evaluateFactor.push_back(info);
			}
			else if (it->second == ExperimentalFactorType::NotEvaluateFactor)
			{
				group.notEvaluateFactor.push_back(info);
			}
		}

		return group;
	}

	std::shared_ptr<DataModelingModule> DataModelingModule::instance(void)
	{
		static std::shared_ptr<DataModelingModule> ret(new DataModelingModule());
		return ret;
	}

	std::shared_ptr<XSDFrontend::XSDModel> DataModelingModule::normalize(const std::vector<FactorType>& infos, std::shared_ptr<XSDFrontend::XSDModel> originModel)
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

	std::shared_ptr<XSDFrontend::XSDModel> DataModelingModule::normalizeWithPublicModel(const std::vector<FactorType>& infos, const std::shared_ptr<XSDFrontend::XSDModel> publicModel, std::shared_ptr<XSDFrontend::XSDModel> originModel)
	{
		// to do : normalize infos to origin model and copy needed simple types from public model to origin model
		// if the type is in the origin model and public model, copy it from public model to origin model to refresh the one in origin model
		return std::shared_ptr<XSDFrontend::XSDModel>();
	}

	std::vector<FactorType> DataModelingModule::analyze(const std::shared_ptr<XSDFrontend::XSDModel> model)
	{
		std::vector<FactorType> ret;

		const auto simpleTypeModel(model->getSimpleTypeModel());
		const auto attributeModel(model->getAttributeModel());
		const auto complexTypeModel(model->getComplexTypeModel());

		return ret;
	}

	std::vector<FactorType> DataModelingModule::analyzeForData(const std::shared_ptr<XSDFrontend::XSDModel> model)
	{
		std::vector<FactorType> ret;

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

				FactorType info;

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
					return std::vector<FactorType>();
				}

				info.name = factor->getName();
				info.experimentalFactorType = factor->getExAttr(ExperimentalFactorTypeAttr());
				info.simpleType = simpleType->getSimpleType();
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

	std::shared_ptr<XSDFrontend::SimpleType::NumberType> DataModelingModule::loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::NumberType> type, const FactorType & info)
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
		if (it != info.validators.cend() && it->second.type() == typeid(NumberEnumContainer))
		{
			const auto &enums(boost::any_cast<NumberEnumContainer>(it->second));
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

	std::shared_ptr<XSDFrontend::SimpleType::StringType> DataModelingModule::loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::StringType> type, const FactorType &info)
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
		if (it != info.validators.cend() && it->second.type() == typeid(StringEnumContainer))
		{
			const auto &enums(boost::any_cast<StringEnumContainer>(it->second));
			type->setIsEnum(true);
			for (const auto &value : enums)
			{
				type->addEnumValue(value);
			};
		}
		return type;
	}

	std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> DataModelingModule::loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> type, const FactorType &info)
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
		if (it != info.validators.cend() && it->second.type() == typeid(DatetimeEnumContainer))
		{
			const auto &enums(boost::any_cast<DatetimeEnumContainer>(it->second));
			type->setIsEnum(true);
			for (const auto &value : enums)
			{
				type->addEnumValue(value);
			};
		}

		return type;
	}

	FactorType DataModelingModule::saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::NumberType> type)
	{
		FactorType info;

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
			info.validators.insert(std::make_pair(XSDFrontend::Token::EnumValidatorTag(), boost::any(NumberEnumContainer(type->getEnumValues().cbegin(), type->getEnumValues().cend()))));
		}

		return info;
	}

	FactorType DataModelingModule::saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::StringType> type)
	{
		FactorType info;

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
			info.validators.insert(std::make_pair(XSDFrontend::Token::EnumValidatorTag(), boost::any(StringEnumContainer(type->getEnumValues().cbegin(), type->getEnumValues().cend()))));
		}

		return info;
	}

	FactorType DataModelingModule::saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> type)
	{
		FactorType info;

		if (!type->getIsEnum())
		{
			info.validators.insert(std::make_pair(XSDFrontend::Token::EnumValidatorTag(), boost::any(DatetimeEnumContainer(type->getEnumValues().cbegin(), type->getEnumValues().cend()))));
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
