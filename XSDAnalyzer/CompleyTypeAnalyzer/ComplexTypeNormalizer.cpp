#include "ComplexTypeNormalizer.h"

namespace XSDNormalizer
{
	ComplexTypeNormalizer::ComplexTypeNormalizer(const std::shared_ptr<XSDFrontend::SimpleTypeModel>& simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel>& attributeModel, const std::shared_ptr<XSDFrontend::ComplexTypeModel>& complexTypeModel, const std::reference_wrapper<SimpleTypeNormalizer>& simpleTypeNormalizer, const std::reference_wrapper<AttributeNormalizer>& attributeNormalizer)
		: m_simpleTypeModel(simpleTypeModel), m_attributeModel(attributeModel), m_complexTypeModel(complexTypeModel), 
		ref_simpleTypeNormalizer(simpleTypeNormalizer), ref_attributeNormalizer(attributeNormalizer)
	{
	}

	std::shared_ptr<SSUtils::XML::Node> ComplexTypeNormalizer::normalizeElement(const std::shared_ptr<XSDFrontend::ComplexType::Element>& element)
	{
		if (element->getAnonymous())
		{
			return nullptr;
		}

		auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::ElementTag));
		if (element->hasRef())
		{
			node->setAttr(XSDFrontend::Token::ReferenceAttr, element->getRefName());
		}
		else
		{
			node->setAttr(XSDFrontend::Token::NameAttr, element->getName());

			const std::string &typeName(element->getType());
			if (m_simpleTypeModel->isBaseType(typeName))
			{
				node->addAttr(XSDFrontend::Token::TypeAttr, typeName);
			}
			else if (m_simpleTypeModel->isSimpleType(typeName))
			{
				auto type(m_simpleTypeModel->getSimpleType(typeName));

				if (!type->getAnonymous())
				{
					node->addAttr(XSDFrontend::Token::TypeAttr, typeName);
				}
				else
				{
					auto child(ref_simpleTypeNormalizer.get().normalizeSimpleType(type));
					if (child == nullptr)
					{
						return nullptr;
					}
					node->addChild(child);
				}
			}
			else
			{
				auto type(m_complexTypeModel->getComplexType(typeName));
				if (type == nullptr)
				{
					return nullptr;
				}

				if (!type->getAnonymous())
				{
					node->addAttr(XSDFrontend::Token::TypeAttr, typeName);
				}
				else
				{
					auto child(normalizeComplexType(type));
					if (child == nullptr)
					{
						return nullptr;
					}
					node->addChild(child);
				}
			}
		}

		return node;
	}

	std::shared_ptr<SSUtils::XML::Node> ComplexTypeNormalizer::normalizeElementGroup(const std::shared_ptr<XSDFrontend::ComplexType::ElementGroup>& group)
	{
		if (group->hasRef())
		{
			auto node = SSUtils::XML::Node::generate(XSDFrontend::Token::GroupTag);
			node->setAttr(XSDFrontend::Token::ReferenceAttr, group->getRefName());
			return node;
		}
		else
		{
			auto node = SSUtils::XML::Node::generate(XSDFrontend::ComplexType::ElementGroup::Tag2Type.right.find(group->getElementGroupType())->second);
			decltype(node) ret;
			if (!group->getAnonymous())
			{
				ret = SSUtils::XML::Node::generate(XSDFrontend::Token::GroupTag);
				ret->setAttr(XSDFrontend::Token::NameAttr, group->getName());
				ret->addChild(node);
			}
			else
			{
				ret = node;
			}

			for (const auto &value : group->getValues())
			{
				decltype(node) child = value.isElement() ? normalizeElement(value.element)
					: value.isAnyElement() ? normalizeAnyElement(value.anyElement)
					: value.isElementGroup() ? normalizeElementGroup(value.elementGroup)
					: nullptr;

				if (child == nullptr)
				{
					return nullptr;
				}
				node->addChild(child);
			}

			return ret;
		}
	}

	std::shared_ptr<SSUtils::XML::Node> ComplexTypeNormalizer::normalizeComplexType(const XSDFrontend::ComplexType::IComplexTypeInterface * type)
	{
		auto ret = SSUtils::XML::Node::generate(XSDFrontend::Token::ComplexTypeTag);
		decltype(ret) root, node;
		if (!type->getAnonymous())
		{
			ret->addAttr(XSDFrontend::Token::NameAttr, type->getName());
		}
		if (type->getDeriveType() == XSDFrontend::ComplexType::IComplexTypeInterface::eDerivedType::tNone)
		{
			node = root = ret;
		}
		else
		{
			root = SSUtils::XML::Node::generate(XSDFrontend::ComplexType::IComplexTypeInterface::Tag2ComplexType.right.find(type->getComplexType())->second);
			node = SSUtils::XML::Node::generate(XSDFrontend::ComplexType::IComplexTypeInterface::Tag2DerivedType.right.find(type->getDeriveType())->second);
			node->setAttr(XSDFrontend::Token::BaseTypeAttr, type->getBaseTypeName());
			root->addChild(node);
			ret->addChild(root);
		}

		if (type->getComplexType() == XSDFrontend::ComplexType::eComplexType::tComplexContent)
		{
			if (normalizeComplexContent(node, dynamic_cast<const XSDFrontend::ComplexType::ComplexContent *>(type)) == nullptr)
			{
				return nullptr;
			}
		}
		else if (type->getComplexType() == XSDFrontend::ComplexType::eComplexType::tSimpleContent)
		{
			if (normalizeSimpleContent(node, dynamic_cast<const XSDFrontend::ComplexType::SimpleContent *>(type)) == nullptr)
			{
				return nullptr;
			}
		}

		if (!type->getAttributeGroupName().empty())
		{
			auto attributeGroup(m_attributeModel->getAttributeGroup(type->getAttributeGroupName()));
			if (attributeGroup == nullptr)
			{
				return nullptr;
			}

			if (!attributeGroup->empty())
			{
				auto group(ref_attributeNormalizer.get().normalizeAttributeGroup(attributeGroup));
				if (group == nullptr)
				{
					return nullptr;
				}

				if (!attributeGroup->getAnonymous())
				{
					node->addChild(group);
				}
				else
				{
					for (const auto &child : group->getChildren())
					{
						if (child->getTag() != XSDFrontend::Token::AnnotationTag)
						{
							node->addChild(child);
						}
					}
				}
			}
		}

		return ret;
	}

	std::shared_ptr<SSUtils::XML::Node> ComplexTypeNormalizer::normalizeAnyElement(const std::shared_ptr<XSDFrontend::ComplexType::AnyElement>& element)
	{
		auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::AnyTag));
		return node;
	}

	std::shared_ptr<SSUtils::XML::Node> ComplexTypeNormalizer::normalizeSimpleContent(const std::shared_ptr<SSUtils::XML::Node> node, const XSDFrontend::ComplexType::SimpleContent *type)
	{
		return node;
	}

	std::shared_ptr<SSUtils::XML::Node> ComplexTypeNormalizer::normalizeComplexContent(const std::shared_ptr<SSUtils::XML::Node> node, const XSDFrontend::ComplexType::ComplexContent *type)
	{
		if (!type->getElementGroupName().empty())
		{
			auto elementGroup(m_complexTypeModel->getElementGroup(type->getElementGroupName()));
			if (elementGroup == nullptr)
			{
				return nullptr;
			}

			if (!elementGroup->empty())
			{
				auto group(normalizeElementGroup(elementGroup));
				if (group == nullptr)
				{
					return nullptr;
				}

				node->addChild(group);
			}
		}

		return node;
	}
};
