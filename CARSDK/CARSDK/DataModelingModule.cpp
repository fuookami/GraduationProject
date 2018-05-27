#include "stdafx.h"
#include "DataModelingModule.h"

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
				if (XSDFrontend::SimpleType::NumberType::String2Type.left.find(info.type) != XSDFrontend::SimpleType::NumberType::String2Type.left.end())
				{
					auto numberType = loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::NumberType>(new XSDFrontend::SimpleType::NumberType(BaesTypePrefix + info.name, XSDFrontend::SimpleType::NumberType::String2Type.left.find(info.type)->second)), info);
					simpleTypeModel->getNumberTypes().insert(std::make_pair(numberType->getName(), numberType));
					baseType = dynamic_cast<XSDFrontend::SimpleType::ISimpleTypeInterface *>(numberType.get());
				}
				else if (XSDFrontend::SimpleType::StringType::String2Type.left.find(info.type) != XSDFrontend::SimpleType::StringType::String2Type.left.end())
				{
					auto stringType = loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::StringType>(new XSDFrontend::SimpleType::StringType(BaesTypePrefix + info.name, XSDFrontend::SimpleType::StringType::String2Type.left.find(info.type)->second)), info);
					simpleTypeModel->getStringTypes().insert(std::make_pair(stringType->getName(), stringType));
					baseType = dynamic_cast<XSDFrontend::SimpleType::ISimpleTypeInterface *>(stringType.get());
				}
				else if (XSDFrontend::SimpleType::DatetimeType::String2Type.left.find(info.type) != XSDFrontend::SimpleType::DatetimeType::String2Type.left.end())
				{
					auto datetimeType = loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::DatetimeType>(new XSDFrontend::SimpleType::DatetimeType(BaesTypePrefix + info.name, XSDFrontend::SimpleType::DatetimeType::String2Type.left.find(info.type)->second)), info);
					simpleTypeModel->getDatetimeTypes().insert(std::make_pair(datetimeType->getName(), datetimeType));
					baseType = dynamic_cast<XSDFrontend::SimpleType::ISimpleTypeInterface *>(datetimeType.get());
				}
				else
				{
					return nullptr;
				}

				simpleTypeModel->getSimpleTypes().insert(std::make_pair(baseType->getName(), baseType));
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

			factor->getExAttrs().clear();
			attrGroup->getAttributes().clear();
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
		// to do
		return type;
	}

	std::shared_ptr<XSDFrontend::SimpleType::StringType> DataModelingModule::loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::StringType> type, const Info &info)
	{
		// to do
		return type;
	}

	std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> DataModelingModule::loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> type, const Info &info)
	{
		// to do
		return type;
	}
};
