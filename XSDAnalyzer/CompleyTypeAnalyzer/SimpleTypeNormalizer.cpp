#include "SimpleTypeNormalizer.h"

namespace XSDNormalizer
{
	const std::map<XSDFrontend::SimpleType::eSimpleType, SimpleTypeNormalizer::NotContainerTypeNormalizer> SimpleTypeNormalizer::Type2Normalizer = 
	{
		std::make_pair(XSDFrontend::SimpleType::eSimpleType::tDataType, SimpleTypeNormalizer::NotContainerTypeNormalizer(&SimpleTypeNormalizer::normalizeDataType)),
		std::make_pair(XSDFrontend::SimpleType::eSimpleType::tDatetimeType, SimpleTypeNormalizer::NotContainerTypeNormalizer(&SimpleTypeNormalizer::normalizeDatetimeType)),
		std::make_pair(XSDFrontend::SimpleType::eSimpleType::tNumberType, SimpleTypeNormalizer::NotContainerTypeNormalizer(&SimpleTypeNormalizer::normalizeNumberType)),
		std::make_pair(XSDFrontend::SimpleType::eSimpleType::tStringType, SimpleTypeNormalizer::NotContainerTypeNormalizer(&SimpleTypeNormalizer::normalizeStringType))
	};

	SimpleTypeNormalizer::SimpleTypeNormalizer(const std::shared_ptr<XSDFrontend::SimpleTypeModel>& simpleTypeModel)
		: m_simpleTypeModel(simpleTypeModel)
	{
	}

	std::shared_ptr<SSUtils::XML::Node> SimpleTypeNormalizer::normalizeSimpleType(const XSDFrontend::SimpleType::ISimpleTypeInterface * type)
	{
		if (type->getAnonymous())
		{
			return nullptr;
		}

		auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::SimpleTypeTag));
		node->setAttr(XSDFrontend::Token::NameAttr, type->getName());

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
		auto it(Type2Normalizer.find(type->getSimpleType()));
		return it == Type2Normalizer.cend() ? nullptr : it->second(this, type);
	}

	std::shared_ptr<SSUtils::XML::Node> SimpleTypeNormalizer::generateNotContainerTypeNode(const XSDFrontend::SimpleType::ISimpleTypeInterface *type)
	{
		auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::RestrictionTag));
		if (!type->getBaseTypeName().empty())
		{
			node->setAttr(XSDFrontend::Token::BaseTypeAttr, type->getBaseTypeName());
		}
		return node;
	}

	std::shared_ptr<SSUtils::XML::Node> SimpleTypeNormalizer::normalizeDataType(const XSDFrontend::SimpleType::ISimpleTypeInterface * type)
	{
		auto node(generateNotContainerTypeNode(type));
		return node;
	}

	std::shared_ptr<SSUtils::XML::Node> SimpleTypeNormalizer::normalizeDatetimeType(const XSDFrontend::SimpleType::ISimpleTypeInterface * type)
	{
		auto node(generateNotContainerTypeNode(type));
		return node;
	}

	std::shared_ptr<SSUtils::XML::Node> SimpleTypeNormalizer::normalizeNumberType(const XSDFrontend::SimpleType::ISimpleTypeInterface * type)
	{
		auto node(generateNotContainerTypeNode(type));
		return node;
	}

	std::shared_ptr<SSUtils::XML::Node> SimpleTypeNormalizer::normalizeStringType(const XSDFrontend::SimpleType::ISimpleTypeInterface * type)
	{
		auto node(generateNotContainerTypeNode(type));
		return node;
	}
};
