#include "SimpleTypeNormalizer.h"

namespace XSDNormalizer
{
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
		return std::shared_ptr<SSUtils::XML::Node>();
	}

	std::shared_ptr<SSUtils::XML::Node> SimpleTypeNormalizer::normalizeNotContainerType(const XSDFrontend::SimpleType::ISimpleTypeInterface * type)
	{
		return std::shared_ptr<SSUtils::XML::Node>();
	}
};
