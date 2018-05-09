#pragma once

#include "XSDModel.h"

namespace XSDNormalizer
{
	class XSDNormalizer
	{
	public:
		XSDNormalizer(void) = default;
		XSDNormalizer(const XSDNormalizer &ano) = delete;
		XSDNormalizer(XSDNormalizer &&ano) = delete;
		XSDNormalizer &operator=(const XSDNormalizer &rhs) = delete;
		XSDNormalizer &operator=(XSDNormalizer &&rhs) = delete;
		~XSDNormalizer(void) = default;

		const bool normalize(const std::shared_ptr<XSDFrontend::XSDModel> model);

		inline const SSUtils::XML::Document &getDocument(void) const { return m_xmlDoc; }

	private:
		std::shared_ptr<XSDFrontend::XSDModel> m_xsdModel;
		SSUtils::XML::Document m_xmlDoc;
	};
};
