#include "ComplexTypeAnalyzer.h"
#include "XSDToken.h"

#include <iostream>

namespace XSDAnalyzer
{
	ComplexTypeAnalyzer::ComplexTypeAnalyzer(const std::shared_ptr<XSDFrontend::SimpleTypeModel>& simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel>& attributeModel, const std::shared_ptr<XSDFrontend::ComplexTypeModel>& complexTypeModel, const std::reference_wrapper<SimpleTypeAnalyzer>& simpleTypeAnalyzer, const std::reference_wrapper<AttributeAnalyzer>& attributeAnalyzer)
		: m_simpleTypeModel(simpleTypeModel), m_attributeModel(attributeModel), m_complexTypeModel(complexTypeModel), ref_simpleTypeAnalyzer(simpleTypeAnalyzer), ref_attributeAnalyzer(attributeAnalyzer)
	{
	}

	std::shared_ptr<XSDFrontend::ComplexType::Element> ComplexTypeAnalyzer::scanElement(const std::shared_ptr<SSUtils::XML::Node> node, const XSDFrontend::Attribute::IAttributeInterface::eParentType parentType, const std::string & parentName)
	{
		if (parentType == XSDFrontend::Attribute::IAttributeInterface::eParentType::tNonParent)
		{
			if (node->hasAttr(XSDFrontend::Token::ReferenceAttr))
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

	std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> ComplexTypeAnalyzer::scanElementGroup(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		auto elementGroup(node->getTag() == XSDFrontend::Token::GroupTag
			? loadElementGroup(node)
			: loadElementGroup(node, m_complexTypeModel->getNewDefaultElementGroupName(), true));
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

	const std::string ComplexTypeAnalyzer::scanComplexType(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		static const std::string EmptyString("");
		if (node->hasChild(XSDFrontend::Token::AllTag) || node->hasChild(XSDFrontend::Token::SequenceTag) || node->hasChild(XSDFrontend::Token::ChoiceTag) 
			|| node->hasChild(XSDFrontend::Token::ComplexContentTag))
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
		else
		{
			auto ptr = scanSimpleContent(node);
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

	std::shared_ptr<XSDFrontend::ComplexType::Element> ComplexTypeAnalyzer::loadElement(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		static const std::string TrueString("true"), FlaseString("false");

		if (!isElementNodeValid(node))
		{
			return nullptr;
		}
		
		std::shared_ptr<XSDFrontend::ComplexType::Element> element(nullptr);
		if (node->hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			std::string refName(node->getAttr(XSDFrontend::Token::ReferenceAttr));

			auto it(m_complexTypeModel->getGlobalElements().find(refName));
			if (it == m_complexTypeModel->getGlobalElements().cend())
			{
				std::cerr << "在全局元素中找不到要引用的元素'" << refName << "'。" << std::endl;
				return nullptr;
			}

			element.reset(new XSDFrontend::ComplexType::Element(it->second->getCategory()));
			element->setRef(std::move(refName), it->second);
		}
		else if (node->hasAttr(XSDFrontend::Token::NameAttr))
		{
			std::string name(node->getAttr(XSDFrontend::Token::NameAttr));

			if (node->hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::string typeName(node->getAttr(XSDFrontend::Token::TypeAttr));
				
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
					element.reset(new XSDFrontend::ComplexType::Element(std::move(name)));
				}

				element->setType(std::move(typeName));
			}
			else if (node->hasChild(XSDFrontend::Token::SimpleTypeTag))
			{
				auto child(node->getChildren()[node->findChild(XSDFrontend::Token::SimpleTypeTag)]);
				if (child != nullptr)
				{
					std::string typeName(ref_simpleTypeAnalyzer.get().scanSimpleType(child));
					if (typeName.empty())
					{
						return nullptr;
					}

					element.reset(new XSDFrontend::ComplexType::Element(name, XSDFrontend::ComplexType::Element::eCategory::tSimpleType));
					element->setType(typeName);
				}
				else
				{
					return nullptr;
				}
			}
			else if (node->hasChild(XSDFrontend::Token::ComplexTypeTag))
			{
				auto child(node->getChildren()[node->findChild(XSDFrontend::Token::ComplexTypeTag)]);
				if (child != nullptr)
				{
					std::string typeName(scanComplexType(child));
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
				else
				{
					return nullptr;
				}
			}
		}
		else
		{
			return nullptr;
		}

		if (element != nullptr && element->loadNumberLimitation(node) && element->loadValueStatement(node))
		{
			if (node->hasAttr(XSDFrontend::Token::FormAttr))
			{
				element->setForm(XSDFrontend::ComplexType::Element::String2Form.left.find(node->getAttr(XSDFrontend::Token::FormAttr))->second);
			}
			if (node->hasAttr(XSDFrontend::Token::NillableAttr))
			{
				element->setNillable(XSDFrontend::ComplexType::Element::String2Nillable.left.find(node->getAttr(XSDFrontend::Token::NillableAttr))->second);
			}
			if (node->hasAttr(XSDFrontend::Token::AbstractAttr))
			{
				element->setAbstract(XSDFrontend::ComplexType::Element::String2Abstract.left.find(node->getAttr(XSDFrontend::Token::AbstractAttr))->second);
			}
			if (node->hasAttr(XSDFrontend::Token::BlockAttr))
			{
				element->setBlock(XSDFrontend::ComplexType::Element::String2Block.left.find(node->getAttr(XSDFrontend::Token::BlockAttr))->second);
			}
			if (node->hasAttr(XSDFrontend::Token::FinalAttr))
			{
				element->setFinal(XSDFrontend::ComplexType::Element::String2Final.left.find(node->getAttr(XSDFrontend::Token::FinalAttr))->second);
			}
			if (node->hasAttr(XSDFrontend::Token::SubstitutionGroupAttr))
			{
				element->setSubstitutionGroup(node->getAttr(XSDFrontend::Token::SubstitutionGroupAttr));
			}

			element->loadExAttr(node, XSDFrontend::ComplexType::Element::BaseAttrs);
		}
		else
		{
			return nullptr;
		}

		return element;
	}

	std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> ComplexTypeAnalyzer::loadElementGroup(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			std::string refName(node->getAttr(XSDFrontend::Token::ReferenceAttr));
			if (node->hasAttr(XSDFrontend::Token::NameAttr) || node->hasAnyChild())
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
			group->loadExAttr(node, XSDFrontend::ComplexType::ElementGroup::BaseAttrs);
			group->loadNumberLimitation(node);

			return group;
		}
		else if (node->hasAttr(XSDFrontend::Token::NameAttr))
		{
			return loadElementGroup(node, node->getAttr(XSDFrontend::Token::NameAttr));
		}
		else
		{
			std::cerr << "非匿名元素组的定义应有且仅有name或ref属性的其中一个。" << std::endl;
			return nullptr;
		}
	}

	std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> ComplexTypeAnalyzer::loadElementGroup(const std::shared_ptr<SSUtils::XML::Node> node, const std::string & groupName, const bool anonymous)
	{
		int order(0), counter(0);
		for (const auto &elementBodyTagPair : XSDFrontend::ComplexType::ElementGroup::Tag2Type.left)
		{
			auto thisOrder(node->findChild(elementBodyTagPair.first));
			if (thisOrder != SSUtils::XML::Node::npos)
			{
				order = thisOrder;
				++counter;
			}
		}

		if (counter > 1)
		{
			std::cerr << "不能在同一个节点下定义复数个elementGroup" << std::endl;
			return nullptr;
		}
		else if (counter == 0)
		{
			return nullptr;
		}

		const auto groupBody(node->getChildren()[order]);
		if (groupBody != nullptr)
		{
			const auto groupTypeIt(XSDFrontend::ComplexType::ElementGroup::Tag2Type.left.find(groupBody->getTag()));
			if (groupTypeIt == XSDFrontend::ComplexType::ElementGroup::Tag2Type.left.end())
			{
				std::cerr << "不存在的elementGroup类型tag" << std::endl;
				return nullptr;
			}

			std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> group(new XSDFrontend::ComplexType::ElementGroup());
			group->setName(groupName);
			group->setAnonymous(anonymous);
			group->setElementGroupType(groupTypeIt->second);
			group->loadNumberLimitation(node);
			group->loadNumberLimitation(groupBody);
			group->loadExAttr(node, XSDFrontend::ComplexType::ElementGroup::BaseAttrs);

			for (const auto child : groupBody->getChildren())
			{
				if (child != nullptr)
				{
					if (child->getTag() == XSDFrontend::Token::AnyTag)
					{
						std::shared_ptr<XSDFrontend::ComplexType::AnyElement> anyElement(new XSDFrontend::ComplexType::AnyElement());
						if (child->hasAttr(XSDFrontend::Token::NamesapceAttr))
						{
							anyElement->setNamespaceValidator(XSDFrontend::ComplexType::AnyElement::String2NamespaceValidator.left.find(child->getAttr(XSDFrontend::Token::NamesapceAttr))->second);
						}
						if (child->hasAttr(XSDFrontend::Token::ProcessContentsAttr))
						{
							anyElement->setProcessContents(XSDFrontend::ComplexType::AnyElement::String2ProcessContents.left.find(child->getAttr(XSDFrontend::Token::ProcessContentsAttr))->second);
						}
						anyElement->setParent(XSDFrontend::ComplexType::IElementInterface::eParentType::tElementGroup, groupName);
						anyElement->loadNumberLimitation(child);

						group->pushBack(XSDFrontend::ComplexType::ElementGroup::ValueType(anyElement));
					}
					else if (child->getTag() == XSDFrontend::Token::ElementTag)
					{
						auto childElement(scanElement(child, XSDFrontend::XSDElementUtils::IXSDParentedElementInterface::eParentType::tElementGroup, groupName));
						if (childElement != nullptr)
						{
							group->pushBack(XSDFrontend::ComplexType::ElementGroup::ValueType(childElement));
						}
					}
					else if (child->getTag() == XSDFrontend::Token::GroupTag)
					{
						auto childGroup(scanElementGroup(child));
						if (childGroup != nullptr)
						{
							group->pushBack(XSDFrontend::ComplexType::ElementGroup::ValueType(childGroup));
						}
					}
				}
			}

			return group->empty() ? nullptr : group;
		}
		else
		{
			return nullptr;
		}
	}

	std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> ComplexTypeAnalyzer::scanComplexContent(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		auto parent(node->getParent().lock());
		if (parent != nullptr && parent->getTag() == XSDFrontend::Token::SchemaTag && !node->hasAttr(XSDFrontend::Token::NameAttr))
		{
			std::cerr << "定义全局类型时应当有声明名字。" << std::endl;
			return nullptr;
		}

		std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> ret(new XSDFrontend::ComplexType::ComplexContent());

		if (!loadComplexType(dynamic_cast<XSDFrontend::ComplexType::IComplexTypeInterface *>(ret.get()), node))
		{
			return nullptr;
		}

		if (node->hasChild(XSDFrontend::Token::ComplexContentTag))
		{
			if (node->getChildren().size() != 1)
			{
				std::cerr << "在复合内容的派生复合类型声明中，应当只有一个complexContent子节点" << std::endl;
				return false;
			}

			auto child(node->getChildren()[node->findChild(XSDFrontend::Token::ComplexContentTag)]);
			if (child != nullptr)
			{
				if (!loadDerivedComplexType(dynamic_cast<XSDFrontend::ComplexType::IComplexTypeInterface *>(ret.get()), child))
				{
					return nullptr;
				}

				if (child->getChildren().size() >= 1)
				{
					auto complexContentNode(child->getChildren().front());
					if (complexContentNode != nullptr)
					{
						loadComplexContent(ret, complexContentNode);

						if (!isDerivedComplexContentValid(ret))
						{
							return nullptr;
						}
					}
					else
					{
						return nullptr;
					}
				}
				else
				{
					return nullptr;
				}
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			loadComplexContent(ret, node);
		}

		return ret;
	}

	std::shared_ptr<XSDFrontend::ComplexType::SimpleContent> ComplexTypeAnalyzer::scanSimpleContent(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		auto parent(node->getParent().lock());
		if (parent != nullptr && parent->getTag() == XSDFrontend::Token::SchemaTag && !node->hasAttr(XSDFrontend::Token::NameAttr))
		{
			std::cerr << "定义全局类型时应当有声明名字。" << std::endl;
			return nullptr;
		}

		std::shared_ptr<XSDFrontend::ComplexType::SimpleContent> ret(new XSDFrontend::ComplexType::SimpleContent());

		if (!loadComplexType(dynamic_cast<XSDFrontend::ComplexType::IComplexTypeInterface *>(ret.get()), node))
		{
			return nullptr;
		}

		if (node->hasChild(XSDFrontend::Token::SimpleContentTag))
		{
			if (node->getChildren().size() != 1)
			{
				std::cerr << "在简单内容的派生复合类型声明中，应当只有一个simpleContent子节点" << std::endl;
				return false;
			}

			auto child(node->getChildren()[node->findChild(XSDFrontend::Token::SimpleContentTag)]);
			if (child != nullptr)
			{
				if (!loadDerivedComplexType(dynamic_cast<XSDFrontend::ComplexType::IComplexTypeInterface *>(ret.get()), child))
				{
					return nullptr;
				}

				if (child->getChildren().size() >= 1)
				{
					auto simpleContentNode(child->getChildren().front());
					if (simpleContentNode != nullptr)
					{
						loadSimpleContent(ret, simpleContentNode);

						if (!isDerivedSimpleContentValid(ret))
						{
							return nullptr;
						}
					}
					else
					{
						return nullptr;
					}
				}
				else
				{
					return nullptr;
				}
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			loadSimpleContent(ret, node);
		}

		return ret;
	}

	const bool ComplexTypeAnalyzer::loadComplexType(XSDFrontend::ComplexType::IComplexTypeInterface * type, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		std::string typeName(node->hasAttr(XSDFrontend::Token::NameAttr)
			? node->getAttr(XSDFrontend::Token::NameAttr)
			: m_complexTypeModel->getNewDefaultComplexTypeName());
		if (m_complexTypeModel->isComplexTypeExist(typeName))
		{
			return false;
		}
		type->setName(typeName);
		type->setAnonymous(!node->hasAttr(XSDFrontend::Token::NameAttr));
		type->loadExAttr(node, XSDFrontend::ComplexType::IComplexTypeInterface::BaseAttrs);

		if (node->hasAttr(XSDFrontend::Token::AbstractAttr))
		{
			type->setAbstract(XSDFrontend::ComplexType::IComplexTypeInterface::String2Abstract.left.find(node->getAttr(XSDFrontend::Token::AbstractAttr))->second);
		}
		if (node->hasAttr(XSDFrontend::Token::MixedAttr))
		{
			type->setMixed(XSDFrontend::ComplexType::IComplexTypeInterface::String2Mixed.left.find(node->getAttr(XSDFrontend::Token::MixedAttr))->second);
		}
		if (node->hasAttr(XSDFrontend::Token::BlockAttr))
		{
			type->setBlock(XSDFrontend::ComplexType::IComplexTypeInterface::String2Block.left.find(node->getAttr(XSDFrontend::Token::BlockAttr))->second);
		}
		if (node->hasAttr(XSDFrontend::Token::FinalAttr))
		{
			type->setFinal(XSDFrontend::ComplexType::IComplexTypeInterface::String2Final.left.find(node->getAttr(XSDFrontend::Token::FinalAttr))->second);
		}

		return true;
	}

	const bool ComplexTypeAnalyzer::loadDerivedComplexType(XSDFrontend::ComplexType::IComplexTypeInterface * type, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->getChildren().size() != 1)
		{
			std::cerr << "在派生复合类型声明中，应当有且只有extension子节点或restriction子节点" << std::endl;
			return false;
		}
		auto derivedNode(node->getChildren().front());
		if (derivedNode == nullptr || (derivedNode->getTag() != XSDFrontend::Token::ExtensionTag && derivedNode->getTag() != XSDFrontend::Token::RestrictionTag))
		{
			std::cerr << "在派生复合类型声明中，应当有且只有extension子节点或restriction子节点" << std::endl;
			return false;
		}

		if (!derivedNode->hasAttr(XSDFrontend::Token::BaseTypeAttr))
		{
			std::cerr << "在派生复合类型声明中，extension子节点或restriction子节点应当要声明基类型" << std::endl;
			return false;
		}

		const std::string &baseTypeName(derivedNode->getAttr(XSDFrontend::Token::BaseTypeAttr));
		if (type->getComplexType() == XSDFrontend::ComplexType::eComplexType::tSimpleContent)
		{
			if (!m_simpleTypeModel->isTypeExist(baseTypeName) && !m_complexTypeModel->isSimpleContent(baseTypeName))
			{
				std::cerr << baseTypeName << "既不是基础类型或简单类型，也不是简单内容的复合类型，不能作为派生简单内容的复合类型的基类型" << std::endl;
				return false;
			}
		}
		else // if (type->getComplexType() == XSDFrontend::ComplexType::eComplexType::tComplexContent)
		{
			if (!m_complexTypeModel->isSimpleContent(baseTypeName) && !m_complexTypeModel->isComplexContent(baseTypeName))
			{
				std::cerr << baseTypeName << "不是简单内容或复杂内容的复合类型，不能作为派生复杂内容的复合类型的基类型" << std::endl;
				return false;
			}
		}

		type->setBaseType(derivedNode->getTag() == XSDFrontend::Token::ExtensionTag
			? XSDFrontend::ComplexType::IComplexTypeInterface::eDerivedType::tExtension
			: XSDFrontend::ComplexType::IComplexTypeInterface::eDerivedType::tRestriction
			, baseTypeName);

		auto attributeGroup(ref_attributeAnalyzer.get().scanAttributeGroup(node));
		if (attributeGroup != nullptr)
		{
			type->setAttributeGroupName(attributeGroup->getName());
		}
		return true;
	}

	const bool ComplexTypeAnalyzer::loadComplexContent(std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> type, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		type->setComplexType(XSDFrontend::ComplexType::eComplexType::tComplexContent);
		auto attributeGroup(ref_attributeAnalyzer.get().scanAttributeGroup(node));
		if (attributeGroup != nullptr)
		{
			type->setAttributeGroupName(attributeGroup->getName());
		}

		auto elementGroup(scanElementGroup(node));
		if (elementGroup != nullptr)
		{
			type->setElementGroupName(elementGroup->hasRef() ? elementGroup->getRefName() : elementGroup->getName());
		}

		return true;
	}

	const bool ComplexTypeAnalyzer::loadSimpleContent(std::shared_ptr<XSDFrontend::ComplexType::SimpleContent> type, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		type->setComplexType(XSDFrontend::ComplexType::eComplexType::tSimpleContent);
		auto attributeGroup(ref_attributeAnalyzer.get().scanAttributeGroup(node));
		if (attributeGroup != nullptr)
		{
			type->setAttributeGroupName(attributeGroup->getName());
		}

		return true;
	}

	const bool ComplexTypeAnalyzer::isElementNodeValid(const std::shared_ptr<SSUtils::XML::Node> node) const
	{
		if (node->hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			if (node->hasChild(XSDFrontend::Token::ComplexTypeTag) || node->hasChild(XSDFrontend::Token::SimpleTypeTag))
			{
				std::cerr << "带有引用声明的元素内不能有匿名类型声明" << std::endl;
				return false;
			}
			if (node->hasAttr(XSDFrontend::Token::NameAttr))
			{
				std::cerr << "带有引用声明的元素内不能有名称声明" << std::endl;
				return false;
			}
			if (node->hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::cerr << "带有引用声明的元素内不能有类型声明" << std::endl;
				return false;
			}
		}
		else if (node->hasAttr(XSDFrontend::Token::NameAttr))
		{
			if ((node->hasChild(XSDFrontend::Token::ComplexTypeTag) || node->hasChild(XSDFrontend::Token::SimpleTypeTag))
				&& node->hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::cerr << "带有名称声明的元素内不能同时存在类型和匿名类型声明" << std::endl;
				return false;
			}
			if (!(node->hasChild(XSDFrontend::Token::ComplexTypeTag) || node->hasChild(XSDFrontend::Token::SimpleTypeTag))
				&& !node->hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::cerr << "带有名称声明的元素内不能没有类型和匿名类型声明" << std::endl;
				return false;
			}
			if (node->hasChild(XSDFrontend::Token::ComplexTypeTag))
			{
				const auto &complexTypeNode(node->getChildren()[node->findChild(XSDFrontend::Token::ComplexTypeTag)]);
				if (node->hasChild(XSDFrontend::Token::AllTag) || node->hasChild(XSDFrontend::Token::SequenceTag) || node->hasChild(XSDFrontend::Token::ChoiceTag)
					|| node->hasChild(XSDFrontend::Token::ComplexContentTag))
				{
					if (node->hasAttr(XSDFrontend::Token::DefaultAttr) || node->hasAttr(XSDFrontend::Token::FixedAttr))
					{
						std::cerr << "带有派生复杂内容的复合类型声明的元素内不能有固定值或默认值" << std::endl;
						return false;
					}
				}
			}
			if (node->hasAttr(XSDFrontend::Token::TypeAttr))
			{
				if (!m_simpleTypeModel->isTypeExist(node->getAttr(XSDFrontend::Token::TypeAttr))
					&& !m_complexTypeModel->isSimpleContent(node->getAttr(XSDFrontend::Token::TypeAttr)))
				{
					if (node->hasAttr(XSDFrontend::Token::DefaultAttr) || node->hasAttr(XSDFrontend::Token::FixedAttr))
					{
						std::cerr << "只有类型为基础类型、简单类型和派生简单内容的复合类型的元素内才能有固定值或默认值" << std::endl;
						return false;
					}
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

	const bool ComplexTypeAnalyzer::isDerivedComplexContentValid(std::shared_ptr<XSDFrontend::ComplexType::ComplexContent> type)
	{
		return true;
	}

	const bool ComplexTypeAnalyzer::isDerivedSimpleContentValid(std::shared_ptr<XSDFrontend::ComplexType::SimpleContent> type)
	{
		return true;
	}
};
