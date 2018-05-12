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

			return ret;
		}
	}

	std::shared_ptr<SSUtils::XML::Node> ComplexTypeNormalizer::normalizeComplexType(const XSDFrontend::ComplexType::IComplexTypeInterface * type)
	{
		auto ret = SSUtils::XML::Node::generate(XSDFrontend::Token::ComplexTypeTag);
		auto root = SSUtils::XML::Node::generate(XSDFrontend::ComplexType::IComplexTypeInterface::Tag2ComplexType.right.find(type->getComplexType())->second);
		decltype(root) node;
		if (!type->getAnonymous())
		{
			ret->addAttr(XSDFrontend::Token::NameAttr, type->getName());
		}
		if (type->getDeriveType() == XSDFrontend::ComplexType::IComplexTypeInterface::eDerivedType::tNone)
		{
			node = root;
		}
		else
		{
			node = SSUtils::XML::Node::generate(XSDFrontend::ComplexType::IComplexTypeInterface::Tag2DerivedType.right.find(type->getDeriveType())->second);
			root->addChild(node);
		}

		ret->addChild(root);
		return ret;
	}
};
