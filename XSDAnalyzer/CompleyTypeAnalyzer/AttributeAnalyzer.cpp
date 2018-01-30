#include "AttributeAnalyzer.h"
#include "XSDToken.h"

#include <iostream>

namespace XSDAnalyzer
{
	AttributeAnalyzer::AttributeAnalyzer(const std::shared_ptr<XSDFrontend::SimpleTypeModel>& simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel>& attributeModel, const std::reference_wrapper<SimpleTypeAnalyzer> &simpleTypeAnalyzer)
		: m_simpleTypeModel(simpleTypeModel), m_attributeModel(attributeModel), ref_simpleTypeAnalyzer(simpleTypeAnalyzer)
	{
	}

	std::shared_ptr<XSDFrontend::Attribute::Attribute> AttributeAnalyzer::scanAttribute(const XMLUtils::XMLNode & node, const XSDFrontend::Attribute::IAttributeInterface::eParentType parentType, const std::string & parentName)
	{
		if (parentType == XSDFrontend::Attribute::IAttributeInterface::eParentType::tNonParent)
		{
			if (node.hasAttr(XSDFrontend::Token::ReferenceAttr))
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

	std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> AttributeAnalyzer::scanAttributeGroup(const XMLUtils::XMLNode & node)
	{
		auto attributeGroup(loadAttributeGroup(node));
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

	std::shared_ptr<XSDFrontend::Attribute::Attribute> AttributeAnalyzer::loadAttribute(const XMLUtils::XMLNode & node)
	{
		if (node.hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			std::string refName(node.getAttr(XSDFrontend::Token::ReferenceAttr));
			if (node.hasAttr(XSDFrontend::Token::NameAttr) || node.hasAttr(XSDFrontend::Token::TypeAttr) || node.hasAttr(XSDFrontend::Token::DefaultAttr) || node.hasAttr(XSDFrontend::Token::FixedAttr) || node.hasChild(XSDFrontend::Token::SimpleTypeTag) || node.hasAnyChild())
			{
				std::cerr << "引用属性'" << refName << "'的同时，不能有除了form或use以外的属性或任何子标签。" << std::endl;
				return nullptr;
			}

			auto it(m_attributeModel->getGlobalAttributes().find(refName));
			if (it == m_attributeModel->getGlobalAttributes().cend())
			{
				std::cerr << "在全局属性中找不到要引用的属性'" << refName << "'。" << std::endl;
				return nullptr;
			}

			std::shared_ptr<XSDFrontend::Attribute::Attribute> attribute(new XSDFrontend::Attribute::Attribute());
			attribute->setRef(std::move(refName), it->second);

			if (node.hasAttr(XSDFrontend::Token::FormAttr))
			{
				attribute->setForm(XSDFrontend::Attribute::FormString2Form.find(node.getAttr(XSDFrontend::Token::FormAttr))->second);
			}
			if (node.hasAttr(XSDFrontend::Token::UseAttr))
			{
				attribute->setUse(XSDFrontend::Attribute::UseString2Use.find(node.getAttr(XSDFrontend::Token::UseAttr))->second);
			}
			return attribute;
		}
		else if (node.hasAttr(XSDFrontend::Token::NameAttr))
		{
			std::string attrName(node.getAttr(XSDFrontend::Token::NameAttr));

			if (node.hasAttr(XSDFrontend::Token::DefaultAttr) && node.hasAttr(XSDFrontend::Token::FixedAttr))
			{
				std::cerr << "在属性'" << attrName << "'中同时出现了default和fixed属性。" << std::endl;
				return nullptr;
			}

			if (!node.hasAttr(XSDFrontend::Token::TypeAttr) && !node.hasChild(XSDFrontend::Token::SimpleTypeTag))
			{
				std::cerr << "应有且仅有type属性或simpleType子标签的其中一个来定义'" << attrName << "'的类型。" << std::endl;
				return nullptr;
			}

			if (node.hasAttr(XSDFrontend::Token::TypeAttr) && node.hasChild(XSDFrontend::Token::SimpleTypeTag))
			{
				std::cerr << "在属性'" << attrName << "'中同时出现了type属性和simpleType子标签。" << std::endl;
				return nullptr;
			}

			if (m_attributeModel->getGlobalAttributes().find(attrName) != m_attributeModel->getGlobalAttributes().cend())
			{
				std::cerr << "全局属性'" << attrName << "'已被定义。" << std::endl;
				return nullptr;
			}

			std::shared_ptr<XSDFrontend::Attribute::Attribute> attribute(nullptr);
			if (node.hasAttr(XSDFrontend::Token::TypeAttr))
			{
				std::string typeName(node.getAttr(XSDFrontend::Token::TypeAttr));

				if (XSDFrontend::Token::isInXSDNameSpace(typeName) && !XSDFrontend::SimpleTypeModel::isBaseType(typeName))
				{
					std::cerr << "未定义的基础类型：" << typeName << std::endl;
					return nullptr;
				}

				attribute.reset(new XSDFrontend::Attribute::Attribute(std::move(attrName), std::move(typeName)));
			}
			else if (node.hasChild(XSDFrontend::Token::SimpleTypeTag))
			{
				std::string typeName(ref_simpleTypeAnalyzer.get().scan(node.getChildren()[node.findChild(XSDFrontend::Token::SimpleTypeTag)]));

				if (typeName.empty())
				{
					return nullptr;
				}

				attribute.reset(new XSDFrontend::Attribute::Attribute(std::move(attrName), std::move(typeName)));
			}

			if (node.hasAttr(XSDFrontend::Token::DefaultAttr))
			{
				attribute->setDefault(node.getAttr(XSDFrontend::Token::DefaultAttr));
			}
			if (node.hasAttr(XSDFrontend::Token::FixedAttr))
			{
				attribute->setFixed(node.getAttr(XSDFrontend::Token::FixedAttr));
			}
			if (node.hasAttr(XSDFrontend::Token::FormAttr))
			{
				attribute->setForm(XSDFrontend::Attribute::FormString2Form.find(node.getAttr(XSDFrontend::Token::FormAttr))->second);
			}
			if (node.hasAttr(XSDFrontend::Token::UseAttr))
			{
				attribute->setUse(XSDFrontend::Attribute::UseString2Use.find(node.getAttr(XSDFrontend::Token::UseAttr))->second);
			}

			return attribute;
		}
		else
		{
			std::cerr << "属性的定义应有且仅有name或ref属性的其中一个。" << std::endl;
			return nullptr;
		}
	}

	std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> AttributeAnalyzer::loadAttributeGroup(const XMLUtils::XMLNode & node)
	{
		if (node.hasAttr(XSDFrontend::Token::ReferenceAttr))
		{
			std::string refName(node.getAttr(XSDFrontend::Token::ReferenceAttr));
			if (node.hasAttr(XSDFrontend::Token::NameAttr) || node.hasAnyChild())
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
		else if (node.hasAttr(XSDFrontend::Token::NameAttr))
		{
			std::string groupName(node.getAttr(XSDFrontend::Token::NameAttr));

			std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> group(new XSDFrontend::Attribute::AttributeGroup(groupName));
			for (const auto &chileNode : node.getChildren())
			{
				if (chileNode.getTag() == XSDFrontend::Token::AnyAttributeTag)
				{
					XSDFrontend::Attribute::AnyAttribute anyAttribute;
					if (chileNode.hasChild(XSDFrontend::Token::NamesapceAttr))
					{
						anyAttribute.setNamespaceValidator(XSDFrontend::Attribute::NamespaceValidatorString2Validator.find(chileNode.getAttr(XSDFrontend::Token::NamesapceAttr))->second);
					}
					if (chileNode.hasChild(XSDFrontend::Token::ProcessContentsAttr))
					{
						anyAttribute.setProcessContents(XSDFrontend::Attribute::ProcessContentsString2ProcessContents.find(chileNode.getAttr(XSDFrontend::Token::ProcessContentsAttr))->second);
					}
					anyAttribute.setParent(XSDFrontend::Attribute::IAttributeInterface::eParentType::tAttributeGroup, groupName);

					group->setAnyAttribute(std::move(anyAttribute));
				}
				else if (chileNode.getTag() == XSDFrontend::Token::AttributeTag)
				{
					auto childAttribute(scanAttribute(chileNode, XSDFrontend::Attribute::IAttributeInterface::eParentType::tAttributeGroup, groupName));
					if (childAttribute != nullptr)
					{
						group->setOrAddAttribute(childAttribute);
					}
				}
				else if (chileNode.getTag() == XSDFrontend::Token::AttributeGroupTag)
				{
					auto childGroup(scanAttributeGroup(chileNode));
					if (childGroup != nullptr)
					{
						group->addAttributeGroup(childGroup);
					}
				}
			}

			return group;
		}
		else
		{
			std::cerr << "属性的定义应有且仅有name或ref属性的其中一个。" << std::endl;
			return nullptr;
		}
	}
};
