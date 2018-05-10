#pragma once

#include "AttributeNormalizer.h"
#include "ComplexTypeModel.h"

namespace XSDNormalizer
{
	class ComplexTypeNormalizer
	{
	public:
		ComplexTypeNormalizer(const std::shared_ptr<XSDFrontend::SimpleTypeModel> &simpleTypeModel, const std::shared_ptr<XSDFrontend::AttributeModel> &attributeModel, const std::shared_ptr<XSDFrontend::ComplexTypeModel> &complexTypeModel, const std::reference_wrapper<SimpleTypeNormalizer> &simpleTypeNormalizer, const std::reference_wrapper<AttributeNormalizer> &attributeNormalizer);
		ComplexTypeNormalizer(const ComplexTypeNormalizer &ano) = delete;
		ComplexTypeNormalizer(ComplexTypeNormalizer &&ano) = delete;
		ComplexTypeNormalizer &operator=(const ComplexTypeNormalizer &rhs) = delete;
		ComplexTypeNormalizer &operator=(ComplexTypeNormalizer &&rhs) = delete;
		~ComplexTypeNormalizer(void) = default;

		std::shared_ptr<SSUtils::XML::Node> normalizeElement(const std::shared_ptr<XSDFrontend::ComplexType::Element> &element);
		std::shared_ptr<SSUtils::XML::Node> normalizeElementGroup(const std::shared_ptr<XSDFrontend::ComplexType::ElementGroup> &group);
		std::shared_ptr<SSUtils::XML::Node> normalizeComplexType(const XSDFrontend::ComplexType::IComplexTypeInterface *type);

	private:
		std::shared_ptr<XSDFrontend::SimpleTypeModel> m_simpleTypeModel;
		std::shared_ptr<XSDFrontend::AttributeModel> m_attributeModel;
		std::shared_ptr<XSDFrontend::ComplexTypeModel> m_complexTypeModel;
		std::reference_wrapper<SimpleTypeNormalizer> ref_simpleTypeNormalizer;
		std::reference_wrapper<AttributeNormalizer> ref_attributeNormalizer;
	};
};
