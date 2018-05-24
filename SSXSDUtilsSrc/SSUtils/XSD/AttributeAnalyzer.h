#pragma once

#include "SimpleTypeModel.h"
#include "AttributeModel.h"
#include "SimpleTypeAnalyzer.h"
#include "SSUtils\XMLUtils.h"

#include <functional>

namespace XSDAnalyzer
{
	class SSXSDUtils_API_DECLSPEC AttributeAnalyzer
	{
	public:
		AttributeAnalyzer(const std::shared_ptr<XSDFrontend::SimpleTypeModel> &simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel> &attributeModel, const std::reference_wrapper<SimpleTypeAnalyzer> &simpleTypeAnalyzer);
		AttributeAnalyzer(const AttributeAnalyzer &ano) = delete;
		AttributeAnalyzer(AttributeAnalyzer &&ano) = delete;
		AttributeAnalyzer &operator=(const AttributeAnalyzer &rhs) = delete;
		AttributeAnalyzer &operator=(AttributeAnalyzer &&rhs) = delete;
		~AttributeAnalyzer(void) = default;

		std::shared_ptr<XSDFrontend::Attribute::Attribute> scanAttribute(const std::shared_ptr<SSUtils::XML::Node> node, const XSDFrontend::Attribute::IAttributeInterface::eParentType parentType = XSDFrontend::Attribute::Attribute::eParentType::tNonParent, const std::string &parentName = std::string(""));
		std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> scanAttributeGroup(const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		std::shared_ptr<XSDFrontend::Attribute::Attribute> loadAttribute(const std::shared_ptr<SSUtils::XML::Node> node);
		std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> loadAttributeGroup(const std::shared_ptr<SSUtils::XML::Node> node);
		std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> loadAttributeGroup(const std::shared_ptr<SSUtils::XML::Node> node, const std::string &groupName, const bool anonymous = false);

		const bool isAttributeNodeValid(const std::shared_ptr<SSUtils::XML::Node> node) const;

	private:
		std::shared_ptr<XSDFrontend::SimpleTypeModel> m_simpleTypeModel;
		std::shared_ptr<XSDFrontend::AttributeModel> m_attributeModel;
		std::reference_wrapper<SimpleTypeAnalyzer> ref_simpleTypeAnalyzer;
	};
};
