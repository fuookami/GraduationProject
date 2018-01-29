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
				std::cerr << "��ȫ�ֶ����Ԫ�ز�Ӧ���ñ�����ԡ�" << std::endl;
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
		static const std::string EmptyString("");
		if (node.hasChild(XSDFrontend::Token::AllTag) || node.hasChild(XSDFrontend::Token::SequenceTag) || node.hasChild(XSDFrontend::Token::ChoiceTag))
		{
			// ����ᵼ�����޵�������һ���ǲ��ǵ��ô���
			// return scanComplexType(node);
			return EmptyString;
		}
		else if (node.hasChild(XSDFrontend::Token::ComplexContentTag))
		{
			auto ptr = scanDerivedComplexContent(node);
			return ptr == nullptr ? EmptyString : ptr->getName();
		}
		else if (node.hasChild(XSDFrontend::Token::SimpleContentTag))
		{
			auto ptr = scanDerivedSimpleContent(node);
			return ptr == nullptr ? EmptyString : ptr->getName();
		}

		return EmptyString;
	}

	std::shared_ptr<XSDFrontend::ComplexType::Element> ComplexTypeAnalyzer::loadElement(const XMLUtils::XMLNode & node)
	{
		if (isElementNodeValid(node))
		{
			return nullptr;
		}

		if (node.hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			std::string refName(node.getAttr(XSDFrontend::Token::ReferenceAttr));
		}
		else
		{

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

	bool ComplexTypeAnalyzer::isElementNodeValid(const XMLUtils::XMLNode & node) const
	{
		if (node.hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			if (node.hasChild(XSDFrontend::Token::CompleyTypeTag) || node.hasChild(XSDFrontend::Token::SimpleTypeTag))
			{
				std::cerr << "��������������Ԫ���ڲ�����������������" << std::endl;
				return false;
			}
			else if (node.hasAttr(XSDFrontend::Token::NameAttr))
			{
				std::cerr << "��������������Ԫ���ڲ�������������" << std::endl;
				return false;
			}
			else if (node.hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::cerr << "��������������Ԫ���ڲ�������������" << std::endl;
				return false;
			}
		}
		else if (node.hasAttr(XSDFrontend::Token::NameAttr))
		{
			if ((node.hasChild(XSDFrontend::Token::CompleyTypeTag) || node.hasChild(XSDFrontend::Token::SimpleTypeTag))
				&& node.hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::cerr << "��������������Ԫ���ڲ���ͬʱ�������ͺ�������������" << std::endl;
				return false;
			}
			else if (!(node.hasChild(XSDFrontend::Token::CompleyTypeTag) || node.hasChild(XSDFrontend::Token::SimpleTypeTag))
				&& !node.hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::cerr << "��������������Ԫ���ڲ���û�����ͺ�������������" << std::endl;
				return false;
			}
			else if (node.hasChild(XSDFrontend::Token::CompleyTypeTag) && !m_simpleTypeModel->isSimpleType(node.getAttr(XSDFrontend::Token::TypeAttr)))
			{
				if (node.hasAttr(XSDFrontend::Token::DefaultAttr) || node.hasAttr(XSDFrontend::Token::FixedAttr))
				{
					std::cerr << "���и�������������������������������Ԫ���ڲ����й̶�ֵ��Ĭ��ֵ" << std::endl;
					return false;
				}
			}
			else if (node.hasChild(XSDFrontend::Token::SimpleTypeTag) || m_simpleTypeModel->isSimpleType(node.getAttr(XSDFrontend::Token::TypeAttr)))
			{
				if (node.hasAttr(XSDFrontend::Token::DefaultAttr) && node.hasAttr(XSDFrontend::Token::FixedAttr))
				{
					std::cerr << "���м���������������������������Ԫ���ڲ���ͬʱ�й̶�ֵ��Ĭ��ֵ" << std::endl;
					return false;
				}
			}
		}
		else
		{
			std::cerr << "Ԫ���ڲ���ͬʱû�����ú���������" << std::endl;
			return false;
		}

		return true;
	}
};
