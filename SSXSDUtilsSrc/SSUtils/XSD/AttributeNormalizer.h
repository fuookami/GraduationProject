#pragma once

#include "SimpleTypeNormalizer.h"
#include "AttributeModel.h"

namespace XSDNormalizer
{
	class SSXSDUtils_API_DECLSPEC AttributeNormalizer
	{
	public:
		AttributeNormalizer(const std::shared_ptr<XSDFrontend::SimpleTypeModel> &simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel> &attributeModel, const std::reference_wrapper<SimpleTypeNormalizer> &simpleTypeNormalizer);
		AttributeNormalizer(const AttributeNormalizer &ano) = delete;
		AttributeNormalizer(AttributeNormalizer &&ano) = delete;
		AttributeNormalizer &operator=(const AttributeNormalizer &rhs) = delete;
		AttributeNormalizer &operator=(AttributeNormalizer &&rhs) = delete;
		~AttributeNormalizer(void) = default;

		std::shared_ptr<SSUtils::XML::Node> normalizeAttribute(const std::shared_ptr<XSDFrontend::Attribute::Attribute> &attr);
		std::shared_ptr<SSUtils::XML::Node> normalizeAttributeGroup(const std::shared_ptr<XSDFrontend::Attribute::AttributeGroup> &group);

	private:
		std::shared_ptr<SSUtils::XML::Node> normalizeAnyAttribute(const std::shared_ptr<const XSDFrontend::Attribute::AnyAttribute> &attr);

	private:
		std::shared_ptr<XSDFrontend::SimpleTypeModel> m_simpleTypeModel;
		std::shared_ptr<XSDFrontend::AttributeModel> m_attributeModel;
		std::reference_wrapper<SimpleTypeNormalizer> ref_simpleTypeNormalizer;
	};
};
