#include "XSDNormalizer.h"

namespace XSDNormalizer
{
	XSDNormalizer::XSDNormalizer(const std::shared_ptr<XSDFrontend::XSDModel> model)
		: m_xsdModel(model), m_simpleTypeNormalizer(model->getSimpleTypeModel()), 
		m_attributeNormalizer(model->getSimpleTypeModel(), model->getAttributeModel(), m_simpleTypeNormalizer), 
		m_complexTypeNormalizer(model->getSimpleTypeModel(), model->getAttributeModel(), model->getComplexTypeModel(), m_simpleTypeNormalizer, m_attributeNormalizer)
	{
	}

	const bool XSDNormalizer::XSDNormalizer::normalize(void)
	{
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
		for (const auto order : orders)
		{
			auto node(m_simpleTypeNormalizer.normalizeSimpleType(simpleTypes[order]));
			if (node == nullptr)
			{
				return false;
			}
			root->addChild(node);
		}
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
