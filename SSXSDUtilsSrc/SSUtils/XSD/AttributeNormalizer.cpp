#include "stdafx.h"
#include "AttributeNormalizer.h"

namespace XSDNormalizer
{
	AttributeNormalizer::AttributeNormalizer(const std::shared_ptr<XSDFrontend::SimpleTypeModel>& simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel>& attributeModel, const std::reference_wrapper<SimpleTypeNormalizer>& simpleTypeNormalizer)
		: m_simpleTypeModel(simpleTypeModel), m_attributeModel(attributeModel), ref_simpleTypeNormalizer(simpleTypeNormalizer)
	{
	}

	std::shared_ptr<SSUtils::XML::Node> AttributeNormalizer::normalizeAttribute(const std::shared_ptr<XSDFrontend::Attribute::Attribute>& attr)
	{
		if (attr->getAnonymous())
		{
			return nullptr;
		}

		auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::AttributeTag()));
		if (attr->hasRef())
		{
			node->setAttr(XSDFrontend::Token::ReferenceAttr(), attr->getRefName());
		}
		else
		{
			node->setAttr(XSDFrontend::Token::NameAttr(), attr->getName());

			if (attr->getForm() != XSDFrontend::Attribute::Attribute::DefaultForm)
			{
				node->setAttr(XSDFrontend::Token::FormAttr(), XSDFrontend::Attribute::Attribute::String2Form.right.find(attr->getForm())->second);
			}
			if (attr->getUse() != XSDFrontend::Attribute::Attribute::DefaultUse)
			{
				node->setAttr(XSDFrontend::Token::UseAttr(), XSDFrontend::Attribute::Attribute::String2Use.right.find(attr->getUse())->second);
			}

			const std::string &typeName(attr->getType());
			if (m_simpleTypeModel->isBaseType(typeName))
			{
				node->addAttr(XSDFrontend::Token::TypeAttr(), typeName);
			}
			else
			{
				auto type(m_simpleTypeModel->getSimpleType(typeName));
				if (type == nullptr)
				{
					return nullptr;
				}

				if (!type->getAnonymous())
				{
					node->addAttr(XSDFrontend::Token::TypeAttr(), typeName);
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

			node = attr->saveValueStatement(node);
		}
		attr->saveExAttr(node);
		return node;
	}

	std::shared_ptr<SSUtils::XML::Node> AttributeNormalizer::normalizeAttributeGroup(const std::shared_ptr<XSDFrontend::Attribute::AttributeGroup>& group)
	{
		auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::AttributeGroupTag()));
		if (group->hasRef())
		{
			node->setAttr(XSDFrontend::Token::ReferenceAttr(), group->getRefName());
		}
		else if (!group->getAnonymous())
		{
			node->setAttr(XSDFrontend::Token::NameAttr(), group->getName());
		}

		if (!group->getDescription().empty())
		{
			auto annotation(SSUtils::XML::Node::generate(XSDFrontend::Token::AnnotationTag()));
			auto documentation(SSUtils::XML::Node::generate(XSDFrontend::Token::DocumentationTag()));

			documentation->addAttr(XSDFrontend::Token::LangAttr(), group->getDescriptionLang());
			documentation->setContent(group->getDescription());
			annotation->addChild(documentation);
			node->addChild(annotation);
		}

		for (const auto &pair : group->getAttributes())
		{
			auto child(normalizeAttribute(pair.second));
			if (child == nullptr)
			{
				return nullptr;
			}
			node->addChild(child);
		}

		for (const auto &pair : group->getAttributeGroups())
		{
			auto child(normalizeAttributeGroup(pair.second));
			if (child == nullptr)
			{
				return nullptr;
			}
			node->addChild(child);
		}

		if (group->hasAnyAttribute())
		{
			auto child(normalizeAnyAttribute(group->getAnyAttribute()));
			if (child == nullptr)
			{
				return nullptr;
			}
			node->addChild(child);
		}

		group->saveExAttr(node);
		return node;
	}

	std::shared_ptr<SSUtils::XML::Node> AttributeNormalizer::normalizeAnyAttribute(const std::shared_ptr<const XSDFrontend::Attribute::AnyAttribute>& attr)
	{
		auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::AnyAttributeTag()));
		if (attr->getNamesapceValidator() != XSDFrontend::Attribute::AnyAttribute::DefaultNamespaceValidator)
		{
			node->setAttr(XSDFrontend::Token::NamesapceAttr(), XSDFrontend::Attribute::AnyAttribute::String2NamespaceValidator.right.find(attr->getNamesapceValidator())->second);
		}
		if (attr->getProcessContents() != XSDFrontend::Attribute::AnyAttribute::DefaultProcessContents)
		{
			node->setAttr(XSDFrontend::Token::ProcessContentsAttr(), XSDFrontend::Attribute::AnyAttribute::String2ProcessContents.right.find(attr->getProcessContents())->second);
		}

		return node;
	}
};
