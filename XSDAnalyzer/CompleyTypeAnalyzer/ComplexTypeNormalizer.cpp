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
		return std::shared_ptr<SSUtils::XML::Node>();
	}

	std::shared_ptr<SSUtils::XML::Node> ComplexTypeNormalizer::normalizeComplexType(const XSDFrontend::ComplexType::IComplexTypeInterface * type)
	{
		return std::shared_ptr<SSUtils::XML::Node>();
	}
};
