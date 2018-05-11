#include "SimpleTypeNormalizer.h"

namespace XSDNormalizer
{
	SimpleTypeNormalizer::SimpleTypeNormalizer(const std::shared_ptr<XSDFrontend::SimpleTypeModel>& simpleTypeModel)
		: m_simpleTypeModel(simpleTypeModel)
	{
	}

	std::shared_ptr<SSUtils::XML::Node> SimpleTypeNormalizer::normalizeSimpleType(const XSDFrontend::SimpleType::ISimpleTypeInterface * type)
	{
		auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::SimpleTypeTag));
		if (!type->getAnonymous())
		{
			node->setAttr(XSDFrontend::Token::NameAttr, type->getName());
		}

		if (!type->getDescription().empty())
		{
			auto annotation(SSUtils::XML::Node::generate(XSDFrontend::Token::AnnotationTag));
			auto documentation(SSUtils::XML::Node::generate(XSDFrontend::Token::DocumentationTag));

			documentation->addAttr(XSDFrontend::Token::LangAttr, type->getDescriptionLang());
			documentation->setContent(type->getDescription());
			annotation->addChild(documentation);
			node->addChild(annotation);
		}

		auto child(type->getSimpleType() == XSDFrontend::SimpleType::eSimpleType::tContainerType
			? normalizeContainerType(dynamic_cast<const XSDFrontend::SimpleType::ContainerType *>(type))
			: normalizeNotContainerType(type));
		if (child == nullptr)
		{
			return nullptr;
		}
		node->addChild(child);

		return node;
	}

	std::shared_ptr<SSUtils::XML::Node> SimpleTypeNormalizer::normalizeContainerType(const XSDFrontend::SimpleType::ContainerType * type)
	{
		auto node(SSUtils::XML::Node::generate(type->getBaseType() == XSDFrontend::SimpleType::ContainerType::eBaseType::tList 
			? XSDFrontend::Token::ListTag : XSDFrontend::Token::UnionTag));
		node->addAttr(XSDFrontend::SimpleType::ContainerType::String2ItemType.right.find(type->getBaseType())->second, SSUtils::String::join(type->getBaseTypes(), std::string(" ")));
		return node;
	}

	std::shared_ptr<SSUtils::XML::Node> SimpleTypeNormalizer::normalizeNotContainerType(const XSDFrontend::SimpleType::ISimpleTypeInterface * type)
	{
		auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::RestrictionTag));
		return type->saveValidator(node);
	}
};
