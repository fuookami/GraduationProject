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

		std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> scanComplexContent(const XMLUtils::XMLNode &node);
		std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> scanDerivedComplexContent(const XMLUtils::XMLNode &node);
		std::shared_ptr<XSDFrontend::ComplexType::SimpleContent> scanDerivedSimpleContent(const XMLUtils::XMLNode &node);

	private:
		bool isElementNodeValid(const XMLUtils::XMLNode &node) const;

	private:
		std::shared_ptr<XSDFrontend::SimpleTypeModel> m_simpleTypeModel;
		std::shared_ptr<XSDFrontend::AttributeModel> m_attributeModel;
		std::shared_ptr<XSDFrontend::ComplexTypeModel> m_complexTypeModel;

		std::reference_wrapper<SimpleTypeAnalyzer> ref_simpleTypeAnalyzer;
		std::reference_wrapper<AttributeAnalyzer> ref_attributeAnalyzer;
	};
};
