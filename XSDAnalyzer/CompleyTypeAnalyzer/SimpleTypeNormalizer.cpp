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

		return node;
	}
};
