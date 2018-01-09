#include "ComplexTypeAnalyzer.h"
#include "XSDToken.h"

#include <iostream>

namespace XSDAnalyzer
{
	ComplexTypeAnalyzer::ComplexTypeAnalyzer(const std::shared_ptr<XSDFrontend::SimpleTypeModel>& simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel>& attributeModel, const std::shared_ptr<XSDFrontend::ComplexTypeModel>& complexTypeModel, const std::reference_wrapper<SimpleTypeAnalyzer>& simpleTypeAnalyzer, const std::reference_wrapper<AttributeAnalyzer>& attributeAnalyzer)
		: m_simpleTypeModel(simpleTypeModel), m_attributeModel(attributeModel), m_complexTypeModel(complexTypeModel), ref_simpleTypeAnalyzer(simpleTypeAnalyzer), ref_attributeAnalyzer(attributeAnalyzer)
	{
	}

	ComplexTypeAnalyzer::~ComplexTypeAnalyzer(void)
	{
	}

	std::shared_ptr<XSDFrontend::ComplexType::Element> ComplexTypeAnalyzer::scanElement(const XMLUtils::XMLNode & node, const XSDFrontend::Attribute::IAttributeInterface::eParentType parentType, const std::string & parentName)
	{
		if (parentType == XSDFrontend::Attribute::IAttributeInterface::eParentType::tNonParent)
		{
			if (node.hasAttr(XSDFrontend::Token::ReferenceAttr))
			{
				std::cerr << "在全局定义的元素不应引用别的属性。" << std::endl;
				return nullptr;
			}

			auto element(loadElement(node));
			if (element != nullptr)
			{
				element->setParent(parentType, parentName);
				m_complexTypeModel->getGlobalElements().insert(std::make_pair(element->getName(), element));
			}
			return element;
		}
		else
		{
			auto element(loadElement(node));
			if (element != nullptr)
			{
				element->setParent(parentType, parentName);
			}
			return element;
		}
	}

	std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> ComplexTypeAnalyzer::scanElementGroup(const XMLUtils::XMLNode & node)
	{
		return std::shared_ptr<XSDFrontend::ComplexType::ElementGroup>();
	}

	const std::string ComplexTypeAnalyzer::scanComplexType(const XMLUtils::XMLNode & node)
	{
		if (node.hasChild(XSDFrontend::Token::AllTag) || node.hasChild(XSDFrontend::Token::SequenceTag) || node.hasChild(XSDFrontend::Token::AllTag))
		{
			scanComplexType(node);
		}
		else if (node.hasChild(XSDFrontend::Token::ComplexContentTag))
		{
			scanDerivedComplexContent(node);
		}
		else if (node.hasChild(XSDFrontend::Token::SimpleContentTag))
		{
			scanDerivedSimpleContent(node);
		}
	}

	std::shared_ptr<XSDFrontend::ComplexType::Element> ComplexTypeAnalyzer::loadElement(const XMLUtils::XMLNode & node)
	{
		if (isElementNodeValid(node))
		{
			return nullptr;
		}
		return std::shared_ptr<XSDFrontend::ComplexType::Element>();
	}

	std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> ComplexTypeAnalyzer::scanComplexContent(const XMLUtils::XMLNode & node)
	{
		return std::shared_ptr<XSDFrontend::ComplexType::ComplexContent>();
	}

	std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> ComplexTypeAnalyzer::scanDerivedComplexContent(const XMLUtils::XMLNode & node)
	{
		return std::shared_ptr<XSDFrontend::ComplexType::ComplexContent>();
	}

	std::shared_ptr<XSDFrontend::ComplexType::SimpleContent> ComplexTypeAnalyzer::scanDerivedSimpleContent(const XMLUtils::XMLNode & node)
	{
		return std::shared_ptr<XSDFrontend::ComplexType::SimpleContent>();
	}

	bool ComplexTypeAnalyzer::isElementNodeValid(const XMLUtils::XMLNode & node)
	{
		int counter(0);
		counter += node.hasChild(XSDFrontend::Token::CompleyTypeTag) ? 1 : 0;
		counter += node.hasAttr(XSDFrontend::Token::ReferenceAttr) ? 1 : 0;

		if (counter == 2)
		{
			std::cerr << "元素内不能同时存在引用和匿名复合类型声明" << std::endl;
			return false;
		}
		else if (counter == 0)
		{
			std::cerr << "元素内不能同时没有引用和匿名符合类型声明" << std::endl;
			return false;
		}

		if (!node.hasAttr(XSDFrontend::Token::ReferenceAttr) && !node.hasAttr(XSDFrontend::Token::NameAttr))
		{
			std::cerr << "元素内不能同时没有引用和名称声明" << std::endl;
			return false;
		}

		return true;
	}
};
