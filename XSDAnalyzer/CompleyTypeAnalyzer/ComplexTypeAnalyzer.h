#pragma once

#include "ComplexTypeModel.h"
#include "AttributeAnalyzer.h"

namespace XSDAnalyzer
{
	class ComplexTypeAnalyzer
	{
	public:
		ComplexTypeAnalyzer(const std::shared_ptr<XSDFrontend::SimpleTypeModel> &simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel> &attributeModel, const std::shared_ptr<XSDFrontend::ComplexTypeModel> &complexTypeModel, const std::reference_wrapper<SimpleTypeAnalyzer> &simpleTypeAnalyzer, const std::reference_wrapper<AttributeAnalyzer> &attributeAnalyzer);
		ComplexTypeAnalyzer(const ComplexTypeAnalyzer &ano) = delete;
		ComplexTypeAnalyzer(ComplexTypeAnalyzer &&ano) = delete;
		ComplexTypeAnalyzer &operator=(const ComplexTypeAnalyzer &rhs) = delete;
		ComplexTypeAnalyzer &operator=(ComplexTypeAnalyzer &&rhs) = delete;
		~ComplexTypeAnalyzer(void) = default;

		std::shared_ptr<XSDFrontend::ComplexType::Element> scanElement(const XMLUtils::XMLNode &node, const XSDFrontend::Attribute::IAttributeInterface::eParentType parentType = XSDFrontend::Attribute::Attribute::eParentType::tNonParent, const std::string &parentName = std::string(""));
		std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> scanElementGroup(const XMLUtils::XMLNode &node);
		const std::string scanComplexType(const XMLUtils::XMLNode &node);

	private:
		std::shared_ptr<XSDFrontend::ComplexType::Element> loadElement(const XMLUtils::XMLNode &node);
		std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> loadElementGroup(const XMLUtils::XMLNode &node);
		std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> loadElementGroup(const XMLUtils::XMLNode &node, const std::string &groupName);

		std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> scanComplexContent(const XMLUtils::XMLNode &node);
		std::shared_ptr<XSDFrontend::ComplexType::SimpleContent> scanSimpleContent(const XMLUtils::XMLNode &node);
		const bool loadComplexType(XSDFrontend::ComplexType::IComplexTypeInterface *type, const XMLUtils::XMLNode
			&node);
		const bool loadDerivedComplexType(XSDFrontend::ComplexType::IComplexTypeInterface *type, const XMLUtils::XMLNode
			&node);
		const bool loadComplexContent(std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> type, const XMLUtils::XMLNode &node);
		const bool loadSimpleContent(std::shared_ptr<XSDFrontend::ComplexType::SimpleContent> type, const XMLUtils::XMLNode &node);

	private:
		const bool isElementNodeValid(const XMLUtils::XMLNode &node) const;
		const bool isDerivedComplexContentValid(std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> type);
		const bool isDerivedSimpleContentValid(std::shared_ptr<XSDFrontend::ComplexType::SimpleContent> type);

	private:
		std::shared_ptr<XSDFrontend::SimpleTypeModel> m_simpleTypeModel;
		std::shared_ptr<XSDFrontend::AttributeModel> m_attributeModel;
		std::shared_ptr<XSDFrontend::ComplexTypeModel> m_complexTypeModel;

		std::reference_wrapper<SimpleTypeAnalyzer> ref_simpleTypeAnalyzer;
		std::reference_wrapper<AttributeAnalyzer> ref_attributeAnalyzer;
	};
};
