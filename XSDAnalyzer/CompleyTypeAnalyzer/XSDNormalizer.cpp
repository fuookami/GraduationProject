#include "XSDNormalizer.h"
#include "ThreadUtils.h"

namespace XSDNormalizer
{
	XSDNormalizer::XSDNormalizer(const std::shared_ptr<XSDFrontend::XSDModel> model)
		: m_xsdModel(model), m_simpleTypeNormalizer(model->getSimpleTypeModel()), 
		m_attributeNormalizer(model->getSimpleTypeModel(), model->getAttributeModel(), m_simpleTypeNormalizer), 
		m_complexTypeNormalizer(model->getSimpleTypeModel(), model->getAttributeModel(), model->getComplexTypeModel(), m_simpleTypeNormalizer, m_attributeNormalizer)
	{
	}

	const bool XSDNormalizer::normalize(void)
	{
		auto root = m_xsdModel->generateXSDRoot();

		std::vector<decltype(SSUtils::Thread::sharedRun(std::bind(&XSDNormalizer::normalizeSimpleType, this)))> futures = 
		{
			SSUtils::Thread::run(std::bind(&XSDNormalizer::normalizeSimpleType, this)),
			SSUtils::Thread::run(std::bind(&XSDNormalizer::normalizeAttribute, this)),
			SSUtils::Thread::run(std::bind(&XSDNormalizer::normalizeComplexType, this))
		};

		for (auto &future : futures)
		{
			future.wait();
			auto result(future.get());
			if (!result.first)
			{
				return false;
			}
			
			std::move(result.second.begin(), result.second.end(), std::back_inserter(root->getChildren()));
		}

		m_xmlDoc.push_back(root);
		return true;
	}

	std::pair<bool, std::vector<std::shared_ptr<SSUtils::XML::Node>>> XSDNormalizer::normalizeSimpleType(void)
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

		std::vector<std::shared_ptr<SSUtils::XML::Node>> nodes;
		auto orders(topologicalSort(simpleTypes));
		for (const auto order : orders)
		{
			auto node(m_simpleTypeNormalizer.normalizeSimpleType(simpleTypes[order]));
			if (node == nullptr)
			{
				return std::make_pair(false, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
			}
			nodes.push_back(node);
		}
		return std::make_pair(true, std::move(nodes));
	}

	std::pair<bool, std::vector<std::shared_ptr<SSUtils::XML::Node>>> XSDNormalizer::normalizeAttribute(void)
	{
		return std::make_pair(true, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
	}

	std::pair<bool, std::vector<std::shared_ptr<SSUtils::XML::Node>>> XSDNormalizer::normalizeComplexType(void)
	{
		return std::make_pair(true, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
	}
};
