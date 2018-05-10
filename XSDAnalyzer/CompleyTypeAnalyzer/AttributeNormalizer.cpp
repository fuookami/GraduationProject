#include "AttributeNormalizer.h"

namespace XSDNormalizer
{
	AttributeNormalizer::AttributeNormalizer(const std::shared_ptr<XSDFrontend::SimpleTypeModel>& simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel>& attributeModel, const std::reference_wrapper<SimpleTypeNormalizer>& simpleTypeNormalizer)
		: m_simpleTypeModel(simpleTypeModel), m_attributeModel(attributeModel), ref_simpleTypeNormalizer(simpleTypeNormalizer)
	{
	}

	std::shared_ptr<SSUtils::XML::Node> AttributeNormalizer::normalizeAttribute(const std::shared_ptr<XSDFrontend::Attribute::Attribute>& attr)
	{
		return std::shared_ptr<SSUtils::XML::Node>();
	}

	std::shared_ptr<SSUtils::XML::Node> AttributeNormalizer::normalizeAttributeGroup(const std::shared_ptr<XSDFrontend::Attribute::AttributeGroup>& group)
	{
		return std::shared_ptr<SSUtils::XML::Node>();
	}
};
