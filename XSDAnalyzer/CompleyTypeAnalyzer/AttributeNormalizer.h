#pragma once

#include "AttributeModel.h"

namespace XSDNormalizer
{
	class AttributeNormalizer
	{
	public:
		AttributeNormalizer(const std::shared_ptr<XSDFrontend::AttributeModel> &attributeModel);
		AttributeNormalizer(const AttributeNormalizer &ano) = delete;
		AttributeNormalizer(AttributeNormalizer &&ano) = delete;
		AttributeNormalizer &operator=(const AttributeNormalizer &rhs) = delete;
		AttributeNormalizer &operator=(AttributeNormalizer &&rhs) = delete;
		~AttributeNormalizer(void) = default;

		std::shared_ptr<SSUtils::XML::Node> normalizeAttribute(const XSDFrontend::Attribute::IAttributeInterface *type);

	private:
		std::shared_ptr<XSDFrontend::AttributeModel> m_attributeModel;
	};
};
