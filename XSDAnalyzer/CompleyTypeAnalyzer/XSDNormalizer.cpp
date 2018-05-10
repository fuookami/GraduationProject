#include "XSDNormalizer.h"

namespace XSDNormalizer
{
	const bool XSDNormalizer::XSDNormalizer::normalize(const std::shared_ptr<XSDFrontend::XSDModel> model)
	{
		m_xsdModel = model;
		auto root = m_xsdModel->generateXSDRoot();
		if (normalizeSimpleType(root) && normalizeAttribute(root) && normalizeComplexType(root))
		{
			m_xmlDoc.push_back(root);
			return true;
		}
		else
		{
			return false;
		}
	}

	const bool XSDNormalizer::normalizeSimpleType(std::shared_ptr<SSUtils::XML::Node> root)
	{
		const auto simpleTypeModel = m_xsdModel->getSimpleTypeModel();
		std::vector<XSDFrontend::SimpleType::ISimpleTypeInterface *> simpleTypes;
		for (const auto &pair : simpleTypeModel->getSimpleTypes())
		{
			if (!pair.second->getAnonymous())
			{
				simpleTypes.push_back(pair.second);
			}
		}

		auto orders(topologicalSort(simpleTypes));
		
		return true;
	}

	const bool XSDNormalizer::normalizeAttribute(std::shared_ptr<SSUtils::XML::Node> root)
	{
		return true;
	}

	const bool XSDNormalizer::normalizeComplexType(std::shared_ptr<SSUtils::XML::Node> root)
	{
		return true;
	}
};
