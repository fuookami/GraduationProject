#pragma once

#include "ComplexTypeModel.h"

namespace XSDNormalizer
{
	class ComplexTypeNormalizer
	{
	public:
		ComplexTypeNormalizer(const std::shared_ptr<XSDFrontend::ComplexTypeModel> &complexTypeModel);
		ComplexTypeNormalizer(const ComplexTypeNormalizer &ano) = delete;
		ComplexTypeNormalizer(ComplexTypeNormalizer &&ano) = delete;
		ComplexTypeNormalizer &operator=(const ComplexTypeNormalizer &rhs) = delete;
		ComplexTypeNormalizer &operator=(ComplexTypeNormalizer &&rhs) = delete;
		~ComplexTypeNormalizer(void) = default;

		std::shared_ptr<SSUtils::XML::Node> normalizeComplexType(const XSDFrontend::ComplexType::IComplexTypeInterface *type);

	private:
		std::shared_ptr<XSDFrontend::ComplexTypeModel> m_complexTypeModel;
	};
};
