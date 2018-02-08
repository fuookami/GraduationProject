#include "ComplexTypeAnalyzer.h"
#include "XSDToken.h"

#include <iostream>

namespace XSDAnalyzer
{
	ComplexTypeAnalyzer::ComplexTypeAnalyzer(const std::shared_ptr<XSDFrontend::SimpleTypeModel>& simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel>& attributeModel, const std::shared_ptr<XSDFrontend::ComplexTypeModel>& complexTypeModel, const std::reference_wrapper<SimpleTypeAnalyzer>& simpleTypeAnalyzer, const std::reference_wrapper<AttributeAnalyzer>& attributeAnalyzer)
		: m_simpleTypeModel(simpleTypeModel), m_attributeModel(attributeModel), m_complexTypeModel(complexTypeModel), ref_simpleTypeAnalyzer(simpleTypeAnalyzer), ref_attributeAnalyzer(attributeAnalyzer)
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
		auto elementGroup(node.getTag() == XSDFrontend::Token::GroupTag
			? loadElementGroup(node)
			: loadElementGroup(node, m_complexTypeModel->getNewDefaultElementGroupName()));
		if (elementGroup == nullptr || elementGroup->hasRef())
		{
			return elementGroup;
		}
		else
		{
			m_complexTypeModel->getElementGroups().insert(std::make_pair(elementGroup->getName(), elementGroup));
			return elementGroup;
		}
	}

	const std::string ComplexTypeAnalyzer::scanComplexType(const XMLUtils::XMLNode & node)
	{
		static const std::string EmptyString("");
		if (node.hasChild(XSDFrontend::Token::AllTag) || node.hasChild(XSDFrontend::Token::SequenceTag) || node.hasChild(XSDFrontend::Token::ChoiceTag))
		{
			auto ptr = scanComplexContent(node);
			if (ptr == nullptr)
			{
				return EmptyString;
			}
			else
			{
				m_complexTypeModel->getComplexContents().insert(std::make_pair(ptr->getName(), ptr));
				return ptr->getName();
			}
		}
		else if (node.hasChild(XSDFrontend::Token::ComplexContentTag))
		{
			auto ptr = scanDerivedComplexContent(node);
			if (ptr == nullptr)
			{
				return EmptyString;
			}
			else
			{
				m_complexTypeModel->getComplexContents().insert(std::make_pair(ptr->getName(), ptr));
				return ptr->getName();
			}
		}
		else if (node.hasChild(XSDFrontend::Token::SimpleContentTag))
		{
			auto ptr = scanDerivedSimpleContent(node);
			if (ptr == nullptr)
			{
				return EmptyString;
			}
			else
			{
				m_complexTypeModel->getSimpleContents().insert(std::make_pair(ptr->getName(), ptr));
				return ptr->getName();
			}
		}

		return EmptyString;
	}

	std::shared_ptr<XSDFrontend::ComplexType::Element> ComplexTypeAnalyzer::loadElement(const XMLUtils::XMLNode & node)
	{
		static const std::string TrueString("true"), FlaseString("false");

		if (!isElementNodeValid(node))
		{
			return nullptr;
		}

		std::shared_ptr<XSDFrontend::ComplexType::Element> element(nullptr);
		if (node.hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			std::string refName(node.getAttr(XSDFrontend::Token::ReferenceAttr));

			auto it(m_complexTypeModel->getGlobalElements().find(refName));
			if (it == m_complexTypeModel->getGlobalElements().cend())
			{
				std::cerr << "在全局元素中找不到要引用的元素'" << refName << "'。" << std::endl;
				return nullptr;
			}

			element.reset(new XSDFrontend::ComplexType::Element(it->second->getCategory()));
			element->setRef(std::move(refName), it->second);
		}
		else if (node.hasAttr(XSDFrontend::Token::NameAttr))
		{
			std::string name(node.getAttr(XSDFrontend::Token::NameAttr));

			if (node.hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::string typeName(node.getAttr(XSDFrontend::Token::TypeAttr));
				
				if (XSDFrontend::SimpleTypeModel::isBaseType(typeName))
				{
					element.reset(new XSDFrontend::ComplexType::Element(std::move(name), XSDFrontend::ComplexType::Element::eCategory::tBaseType));
				}
				else if (m_simpleTypeModel->isSimpleType(typeName))
				{
					element.reset(new XSDFrontend::ComplexType::Element(std::move(name), XSDFrontend::ComplexType::Element::eCategory::tSimpleType));
				}
				else if (m_complexTypeModel->isSimpleContent(typeName))
				{
					element.reset(new XSDFrontend::ComplexType::Element(std::move(name), XSDFrontend::ComplexType::Element::eCategory::tSimpleContent));
				}
				else if (m_complexTypeModel->isComplexContent(typeName))
				{
					element.reset(new XSDFrontend::ComplexType::Element(std::move(name), XSDFrontend::ComplexType::Element::eCategory::tComplexContent));
				}
				else
				{
					std::cerr << "未定义的基础类型、简单类型或复合类型：" << typeName << std::endl;
					return nullptr;
				}

				element->setType(std::move(typeName));
			}
			else if (node.hasChild(XSDFrontend::Token::SimpleTypeTag))
			{
				std::string typeName(ref_simpleTypeAnalyzer.get().scanSimpleType(node.getChildren()[node.findChild(XSDFrontend::Token::SimpleTypeTag)]));
				if (typeName.empty())
				{
					return nullptr;
				}

				element.reset(new XSDFrontend::ComplexType::Element(name, XSDFrontend::ComplexType::Element::eCategory::tSimpleType));
				element->setType(typeName);
			}
			else if (node.hasChild(XSDFrontend::Token::CompleyTypeTag))
			{
				std::string typeName(scanComplexType(node.getChildren()[node.findChild(XSDFrontend::Token::CompleyTypeTag)]));
				if (typeName.empty())
				{
					return nullptr;
				}

				auto *complexType(m_complexTypeModel->getComplexType(typeName));
				switch (complexType->getComplexType())
				{
				case XSDFrontend::ComplexType::eComplexType::tSimpleContent:
					element.reset(new XSDFrontend::ComplexType::Element(name, XSDFrontend::ComplexType::Element::eCategory::tSimpleContent));
					break;
				case XSDFrontend::ComplexType::eComplexType::tComplexContent:
					element.reset(new XSDFrontend::ComplexType::Element(name, XSDFrontend::ComplexType::Element::eCategory::tComplexContent));
					break;
				default:
					break;
				}

				if (element == nullptr)
				{
					return nullptr;
				}
				element->setType(typeName);
			}
		}
		else
		{
			return nullptr;
		}

		return element;
	}

	std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> ComplexTypeAnalyzer::loadElementGroup(const XMLUtils::XMLNode & node)
	{
		if (node.hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			std::string refName(node.getAttr(XSDFrontend::Token::ReferenceAttr));
			if (node.hasAttr(XSDFrontend::Token::NameAttr) || node.hasAnyChild())
			{
				std::cerr << "引用元素组'" << refName << "'的同时，不能有name属性或任何子标签。" << std::endl;
				return nullptr;
			}

			auto it(m_complexTypeModel->getElementGroups().find(refName));
			if (it == m_complexTypeModel->getElementGroups().cend())
			{
				std::cerr << "在全局元素中找不到要引用的属性组'" << refName << "'。" << std::endl;
				return nullptr;
			}

			std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> group(new XSDFrontend::ComplexType::ElementGroup());
			group->setRef(refName, it->second);

			group->loadNumberLimitation(node);

			return group;
		}
		else if (node.hasAttr(XSDFrontend::Token::NameAttr))
		{
			return loadElementGroup(node, node.getAttr(XSDFrontend::Token::NameAttr));
		}
		else
		{
			std::cerr << "非匿名元素组的定义应有且仅有name或ref属性的其中一个。" << std::endl;
			return nullptr;
		}
	}

	std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> ComplexTypeAnalyzer::loadElementGroup(const XMLUtils::XMLNode & node, const std::string & groupName)
	{
		int order(0), counter(0);
		for (const auto &elementBodyTagPair : XSDFrontend::ComplexType::ElementGroupTag2Type)
		{
			auto thisOrder(node.findChild(elementBodyTagPair.first));
			if (thisOrder != XMLUtils::XMLNode::NoChild)
			{
				order = thisOrder;
				++counter;
			}
		}

		if (counter != 1)
		{
			std::cerr << std::endl;
			return nullptr;
		}

		const auto &groupBody(node.getChildren()[order]);
		const auto groupTypeIt(XSDFrontend::ComplexType::ElementGroupTag2Type.find(groupBody.getTag()));
		if (groupTypeIt == XSDFrontend::ComplexType::ElementGroupTag2Type.cend())
		{
			std::cerr << std::endl;
			return nullptr;
		}

		std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> group(new XSDFrontend::ComplexType::ElementGroup());
		group->setName(groupName);
		group->loadNumberLimitation(node);

		for (const auto &childNode : groupBody.getChildren())
		{
			if (childNode.getTag() == XSDFrontend::Token::AnyTag)
			{
				std::shared_ptr<XSDFrontend::ComplexType::AnyElement> anyElement(new XSDFrontend::ComplexType::AnyElement());
				if (childNode.hasAttr(XSDFrontend::Token::NamesapceAttr))
				{
					anyElement->setNamespaceValidator(XSDFrontend::ComplexType::NamespaceValidatorString2Validator.find(childNode.getAttr(XSDFrontend::Token::NamesapceAttr))->second);
				}
				if (childNode.hasAttr(XSDFrontend::Token::ProcessContentsAttr))
				{
					anyElement->setProcessContents(XSDFrontend::ComplexType::ProcessContentsString2ProcessContents.find(childNode.getAttr(XSDFrontend::Token::ProcessContentsAttr))->second);
				}
				anyElement->setParent(XSDFrontend::ComplexType::IElementInterface::eParentType::tElementGroup, groupName);
				anyElement->loadNumberLimitation(childNode);

				group->pushBack(XSDFrontend::ComplexType::ElementGroup::ValueType(anyElement));
			}
			else if (childNode.getTag() == XSDFrontend::Token::ElementTag)
			{
				auto childElement(scanElement(childNode, XSDFrontend::XSDElementUtils::IXSDParentedElementInterface::eParentType::tElementGroup, groupName));
				if (childElement != nullptr)
				{
					group->pushBack(XSDFrontend::ComplexType::ElementGroup::ValueType(childElement));
				}
			}
			else if (childNode.getTag() == XSDFrontend::Token::GroupTag)
			{
				auto childGroup(scanElementGroup(childNode));
				if (childGroup != nullptr)
				{
					group->pushBack(XSDFrontend::ComplexType::ElementGroup::ValueType(childGroup));
				}
			}
		}

		return group->empty() ? nullptr : group;
	}

	std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> ComplexTypeAnalyzer::scanComplexContent(const XMLUtils::XMLNode & node)
	{
		std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> ret(new XSDFrontend::ComplexType::ComplexContent());
		
		if (!node.hasAttr(XSDFrontend::Token::NameAttr))
		{
			std::cerr << std::endl;
			return nullptr;
		}
		ret->setName(node.getAttr(XSDFrontend::Token::NameAttr));

		auto attributeGroup(ref_attributeAnalyzer.get().scanAttributeGroup(node));
		if (attributeGroup != nullptr)
		{
			ret->setAttributeGroupName(attributeGroup->getName());
		}

		auto elementGroup(scanElementGroup(node));
		if (elementGroup != nullptr)
		{
			ret->setElementGroupName(elementGroup->hasRef() ? elementGroup->getRefName() : elementGroup->getName());
		}

		return ret;
	}

	std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> ComplexTypeAnalyzer::scanDerivedComplexContent(const XMLUtils::XMLNode & node)
	{
		return nullptr;
	}

	std::shared_ptr<XSDFrontend::ComplexType::SimpleContent> ComplexTypeAnalyzer::scanDerivedSimpleContent(const XMLUtils::XMLNode & node)
	{
		return nullptr;
	}

	const bool ComplexTypeAnalyzer::isElementNodeValid(const XMLUtils::XMLNode & node) const
	{
		if (node.hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			if (node.hasChild(XSDFrontend::Token::CompleyTypeTag) || node.hasChild(XSDFrontend::Token::SimpleTypeTag))
			{
				std::cerr << "带有引用声明的元素内不能有匿名类型声明" << std::endl;
				return false;
			}
			else if (node.hasAttr(XSDFrontend::Token::NameAttr))
			{
				std::cerr << "带有引用声明的元素内不能有名称声明" << std::endl;
				return false;
			}
			else if (node.hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::cerr << "带有引用声明的元素内不能有类型声明" << std::endl;
				return false;
			}
		}
		else if (node.hasAttr(XSDFrontend::Token::NameAttr))
		{
			if ((node.hasChild(XSDFrontend::Token::CompleyTypeTag) || node.hasChild(XSDFrontend::Token::SimpleTypeTag))
				&& node.hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::cerr << "带有名称声明的元素内不能同时存在类型和匿名类型声明" << std::endl;
				return false;
			}
			else if (!(node.hasChild(XSDFrontend::Token::CompleyTypeTag) || node.hasChild(XSDFrontend::Token::SimpleTypeTag))
				&& !node.hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::cerr << "带有名称声明的元素内不能没有类型和匿名类型声明" << std::endl;
				return false;
			}
			else if (node.hasChild(XSDFrontend::Token::CompleyTypeTag) && !m_simpleTypeModel->isSimpleType(node.getAttr(XSDFrontend::Token::TypeAttr)))
			{
				if (node.hasAttr(XSDFrontend::Token::DefaultAttr) || node.hasAttr(XSDFrontend::Token::FixedAttr))
				{
					std::cerr << "带有复合类型声明或匿名复合类型声明的元素内不能有固定值或默认值" << std::endl;
					return false;
				}
			}
			else if (node.hasChild(XSDFrontend::Token::SimpleTypeTag) || m_simpleTypeModel->isSimpleType(node.getAttr(XSDFrontend::Token::TypeAttr)))
			{
				if (node.hasAttr(XSDFrontend::Token::DefaultAttr) && node.hasAttr(XSDFrontend::Token::FixedAttr))
				{
					std::cerr << "带有简单类型声明或匿名简单类型声明的元素内不能同时有固定值和默认值" << std::endl;
					return false;
				}
			}
		}
		else
		{
			std::cerr << "元素内不能同时没有引用和名称声明" << std::endl;
			return false;
		}

		return true;
	}
};
