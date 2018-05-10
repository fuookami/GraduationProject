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
		std::shared_ptr<SSUtils::XML::Node> normalizeContainerType(const XSDFrontend::SimpleType::ContainerType *type);
		std::shared_ptr<SSUtils::XML::Node> normalizeNotContainerType(const XSDFrontend::SimpleType::ISimpleTypeInterface *type);

		static std::shared_ptr<SSUtils::XML::Node> generateNotContainerTypeNode(const XSDFrontend::SimpleType::ISimpleTypeInterface *type);
		using NotContainerTypeNormalizer = std::mem_fun1_t<std::shared_ptr<SSUtils::XML::Node>, SimpleTypeNormalizer, const XSDFrontend::SimpleType::ISimpleTypeInterface *>;
		static const std::map<XSDFrontend::SimpleType::eSimpleType, NotContainerTypeNormalizer> Type2Normalizer;
		std::shared_ptr<SSUtils::XML::Node> normalizeDataType(const XSDFrontend::SimpleType::ISimpleTypeInterface *type);
		std::shared_ptr<SSUtils::XML::Node> normalizeDatetimeType(const XSDFrontend::SimpleType::ISimpleTypeInterface *type);
		std::shared_ptr<SSUtils::XML::Node> normalizeNumberType(const XSDFrontend::SimpleType::ISimpleTypeInterface *type);
		std::shared_ptr<SSUtils::XML::Node> normalizeStringType(const XSDFrontend::SimpleType::ISimpleTypeInterface *type);

	private:
		std::shared_ptr<XSDFrontend::SimpleTypeModel> m_simpleTypeModel;
	};
};
