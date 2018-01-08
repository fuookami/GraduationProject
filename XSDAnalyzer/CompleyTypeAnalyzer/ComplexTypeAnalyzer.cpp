#include "ComplexTypeAnalyzer.h"

namespace XSDAnalyzer
{
	ComplexTypeAnalyzer::ComplexTypeAnalyzer(const std::shared_ptr<XSDFrontend::SimpleTypeModel>& simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel>& attributeModel, const std::shared_ptr<XSDFrontend::ComplexTypeModel>& complexTypeModel, const std::reference_wrapper<SimpleTypeAnalyzer>& simpleTypeAnalyzer, const std::reference_wrapper<AttributeAnalyzer>& attributeAnalyzer)
		: m_simpleTypeModel(simpleTypeModel), m_attributeModel(attributeModel), m_complexTypeModel(complexTypeModel), ref_simpleTypeAnalyzer(simpleTypeAnalyzer), ref_attributeAnalyzer(attributeAnalyzer)
	{
	}

	ComplexTypeAnalyzer::~ComplexTypeAnalyzer(void)
	{
	}

	std::shared_ptr<XSDFrontend::ComplexType::Element> ComplexTypeAnalyzer::scanElement(const XMLUtils::XMLNode & node)
	{
		return std::shared_ptr<XSDFrontend::ComplexType::Element>();
	}

	std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> ComplexTypeAnalyzer::scanElementGroup(const XMLUtils::XMLNode & node)
	{
		return std::shared_ptr<XSDFrontend::ComplexType::ElementGroup>();
	}

	const std::string ComplexTypeAnalyzer::scanComplexType(const XMLUtils::XMLNode & node)
	{
		return std::string();
	}
};
