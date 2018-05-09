#include "AttributeAnalyzer.h"
#include "XSDToken.h"

#include <iostream>

namespace XSDAnalyzer
{
	AttributeAnalyzer::AttributeAnalyzer(const std::shared_ptr<XSDFrontend::SimpleTypeModel>& simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel>& attributeModel, const std::reference_wrapper<SimpleTypeAnalyzer> &simpleTypeAnalyzer)
		: m_simpleTypeModel(simpleTypeModel), m_attributeModel(attributeModel), ref_simpleTypeAnalyzer(simpleTypeAnalyzer)
	{
	}

	std::shared_ptr<XSDFrontend::Attribute::Attribute> AttributeAnalyzer::scanAttribute(const std::shared_ptr<SSUtils::XML::Node> node, const XSDFrontend::Attribute::IAttributeInterface::eParentType parentType, const std::string & parentName)
	{
		if (parentType == XSDFrontend::Attribute::IAttributeInterface::eParentType::tNonParent)
		{
			if (node->hasAttr(XSDFrontend::Token::ReferenceAttr))
			{
				std::cerr << "在全局定义的属性不应引用别的属性。" << std::endl;
				return nullptr;
			}
			
			auto attribute(loadAttribute(node));
			if (attribute != nullptr)
			{
				attribute->setParent(parentType, parentName);
				m_attributeModel->getGlobalAttributes().insert(std::make_pair(attribute->getName(), attribute));
			}
			return attribute;
		}
		else
		{
			auto attribute(loadAttribute(node));
			if (attribute != nullptr)
			{
				attribute->setParent(parentType, parentName);
			}
			return attribute;
		}
	}

	std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> AttributeAnalyzer::scanAttributeGroup(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		auto attributeGroup(node->getTag() == XSDFrontend::Token::AttributeGroupTag 
			? loadAttributeGroup(node) 
			: loadAttributeGroup(node, m_attributeModel->getNewDefaultAttributeGroupName()));
		if (attributeGroup == nullptr || attributeGroup->hasRef())
		{
			return attributeGroup;
		}
		else
		{
			m_attributeModel->getAttributeGroups().insert(std::make_pair(attributeGroup->getName(), attributeGroup));
			return attributeGroup;
		}
	}

	std::shared_ptr<XSDFrontend::Attribute::Attribute> AttributeAnalyzer::loadAttribute(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (!isAttributeNodeValid(node))
		{
			return nullptr;
		}

		std::shared_ptr<XSDFrontend::Attribute::Attribute> attribute(nullptr);

		if (node->hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			std::string refName(node->getAttr(XSDFrontend::Token::ReferenceAttr));

			auto it(m_attributeModel->getGlobalAttributes().find(refName));
			if (it == m_attributeModel->getGlobalAttributes().cend())
			{
				std::cerr << "在全局属性中找不到要引用的属性'" << refName << "'。" << std::endl;
				return nullptr;
			}

			attribute.reset(new XSDFrontend::Attribute::Attribute());
			attribute->setRef(std::move(refName), it->second);
		}
		else if (node->hasAttr(XSDFrontend::Token::NameAttr))
		{
			std::string attrName(node->getAttr(XSDFrontend::Token::NameAttr));

			if (node->hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::string typeName(node->getAttr(XSDFrontend::Token::TypeAttr));

				if (m_simpleTypeModel->isBaseType(typeName) || m_simpleTypeModel->isSimpleType(typeName))
				{
					attribute.reset(new XSDFrontend::Attribute::Attribute(std::move(attrName), std::move(typeName)));
				}
				else
				{
					std::cerr << "未定义的基础类型或简单类型：" << typeName << std::endl;
					return nullptr;
				}
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

					attribute.reset(new XSDFrontend::Attribute::Attribute(std::move(attrName), std::move(typeName)));
				}
			}

			attribute->loadValueStatement(node);
		}
		else
		{
			return nullptr;
		}

		if (node->hasAttr(XSDFrontend::Token::FormAttr))
		{
			attribute->setForm(XSDFrontend::Attribute::Attribute::String2Form.find(node->getAttr(XSDFrontend::Token::FormAttr))->second);
		}
		if (node->hasAttr(XSDFrontend::Token::UseAttr))
		{
			attribute->setUse(XSDFrontend::Attribute::Attribute::String2Use.find(node->getAttr(XSDFrontend::Token::UseAttr))->second);
		}

		return attribute;
	}

	std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> AttributeAnalyzer::loadAttributeGroup(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			std::string refName(node->getAttr(XSDFrontend::Token::ReferenceAttr));
			if (node->hasAttr(XSDFrontend::Token::NameAttr) || node->hasAnyChild())
			{
				std::cerr << "引用属性组'" << refName << "'的同时，不能有name属性或任何子标签。" << std::endl;
				return nullptr;
			}

			auto it(m_attributeModel->getAttributeGroups().find(refName));
			if (it == m_attributeModel->getAttributeGroups().cend())
			{
				std::cerr << "在全局属性中找不到要引用的属性组'" << refName << "'。" << std::endl;
				return nullptr;
			}

			std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> group(new XSDFrontend::Attribute::AttributeGroup());
			group->setRef(refName, it->second);

			return group;
		}
		else if (node->hasAttr(XSDFrontend::Token::NameAttr))
		{
			return loadAttributeGroup(node, node->getAttr(XSDFrontend::Token::NameAttr));
		}
		else
		{
			std::cerr << "非匿名属性组的定义应有且仅有name或ref属性的其中一个。" << std::endl;
			return nullptr;
		}
	}
	std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> AttributeAnalyzer::loadAttributeGroup(const std::shared_ptr<SSUtils::XML::Node> node, const std::string & groupName)
	{
		std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> group(new XSDFrontend::Attribute::AttributeGroup(groupName));

		for (const auto &child : node->getChildren())
		{
			if (child != nullptr)
			{
				if (child->getTag() == XSDFrontend::Token::AnyAttributeTag)
				{
					std::shared_ptr<XSDFrontend::Attribute::AnyAttribute> anyAttribute(new XSDFrontend::Attribute::AnyAttribute());
					if (child->hasAttr(XSDFrontend::Token::NamesapceAttr))
					{
						anyAttribute->setNamespaceValidator(XSDFrontend::Attribute::AnyAttribute::String2NamespaceValidator.find(child->getAttr(XSDFrontend::Token::NamesapceAttr))->second);
					}
					if (child->hasAttr(XSDFrontend::Token::ProcessContentsAttr))
					{
						anyAttribute->setProcessContents(XSDFrontend::Attribute::AnyAttribute::String2ProcessContents.find(child->getAttr(XSDFrontend::Token::ProcessContentsAttr))->second);
					}
					anyAttribute->setParent(XSDFrontend::XSDElementUtils::IXSDParentedElementInterface::eParentType::tAttributeGroup, groupName);

					group->setAnyAttribute(anyAttribute);
				}
				else if (child->getTag() == XSDFrontend::Token::AttributeTag)
				{
					auto childAttribute(scanAttribute(child, XSDFrontend::XSDElementUtils::IXSDParentedElementInterface::eParentType::tAttributeGroup, groupName));
					if (childAttribute != nullptr)
					{
						group->setOrAddAttribute(childAttribute);
					}
				}
				else if (child->getTag() == XSDFrontend::Token::AttributeGroupTag)
				{
					auto childGroup(scanAttributeGroup(child));
					if (childGroup != nullptr)
					{
						group->addAttributeGroup(childGroup);
					}
				}
			}
		}

		return group->empty() ? nullptr : group;
	}

	const bool AttributeAnalyzer::isAttributeNodeValid(const std::shared_ptr<SSUtils::XML::Node> node) const
	{
		if (node->hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			std::string refName(node->getAttr(XSDFrontend::Token::ReferenceAttr));

			if (node->hasAttr(XSDFrontend::Token::NameAttr) || node->hasAttr(XSDFrontend::Token::TypeAttr) || node->hasAttr(XSDFrontend::Token::DefaultAttr) || node->hasAttr(XSDFrontend::Token::FixedAttr) || node->hasChild(XSDFrontend::Token::SimpleTypeTag) || node->hasAnyChild())
			{
				std::cerr << "引用属性'" << refName << "'的同时，不能有除了form或use以外的属性或任何子标签。" << std::endl;
				return false;
			}
		}
		else if (node->hasAttr(XSDFrontend::Token::NameAttr))
		{
			std::string attrName(node->getAttr(XSDFrontend::Token::NameAttr));

			if (node->hasAttr(XSDFrontend::Token::DefaultAttr) && node->hasAttr(XSDFrontend::Token::FixedAttr))
			{
				std::cerr << "在属性'" << attrName << "'中同时出现了default和fixed属性。" << std::endl;
				return false;
			}

			if (!node->hasAttr(XSDFrontend::Token::TypeAttr) && !node->hasChild(XSDFrontend::Token::SimpleTypeTag))
			{
				std::cerr << "应有且仅有type属性或simpleType子标签的其中一个来定义'" << attrName << "'的类型。" << std::endl;
				return false;
			}

			if (node->hasAttr(XSDFrontend::Token::TypeAttr) && node->hasChild(XSDFrontend::Token::SimpleTypeTag))
			{
				std::cerr << "在属性'" << attrName << "'中同时出现了type属性和simpleType子标签。" << std::endl;
				return false;
			}

			if (m_attributeModel->getGlobalAttributes().find(attrName) != m_attributeModel->getGlobalAttributes().cend())
			{
				std::cerr << "全局属性'" << attrName << "'已被定义。" << std::endl;
				return false;
			}
		}
		else
		{
			std::cerr << "属性的定义应有且仅有name或ref属性的其中一个。" << std::endl;
			return false;
		}

		return true;
	}
};
