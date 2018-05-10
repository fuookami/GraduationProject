#pragma once

#include "SimpleTypeModel.h"

namespace XSDNormalizer
{
	class SimpleTypeNormalizer
	{
	public:
		SimpleTypeNormalizer(const std::shared_ptr<XSDFrontend::SimpleTypeModel> &simpleTypeModel);
		SimpleTypeNormalizer(const SimpleTypeNormalizer &ano) = delete;
		SimpleTypeNormalizer(SimpleTypeNormalizer &&ano) = delete;
		SimpleTypeNormalizer &operator=(const SimpleTypeNormalizer &rhs) = delete;
		SimpleTypeNormalizer &operator=(SimpleTypeNormalizer &&rhs) = delete;
		~SimpleTypeNormalizer(void) = default;

		std::shared_ptr<SSUtils::XML::Node> normalizeSimpleType(const XSDFrontend::SimpleType::ISimpleTypeInterface *type);

	private:
		std::shared_ptr<XSDFrontend::SimpleTypeModel> m_simpleTypeModel;
	};
};
