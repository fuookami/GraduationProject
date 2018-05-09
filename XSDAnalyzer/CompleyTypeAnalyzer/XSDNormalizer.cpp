#include "XSDNormalizer.h"

namespace XSDNormalizer
{
	const bool XSDNormalizer::XSDNormalizer::normalize(const std::shared_ptr<XSDFrontend::XSDModel> model)
	{
		m_xsdModel = model;

		return true;
	}
};
