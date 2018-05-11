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
		const auto attributeModel = m_xsdModel->getAttributeModel();
		std::vector<std::shared_ptr<SSUtils::XML::Node>> nodes;

		for (const auto &pair : attributeModel->getGlobalAttributes())
		{
			auto node(m_attributeNormalizer.normalizeAttribute(pair.second));
			if (node == nullptr)
			{
				return std::make_pair(false, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
			}
			nodes.push_back(node);
		}

		std::vector<std::shared_ptr<XSDFrontend::Attribute::AttributeGroup>> groups;
		for (const auto &pair : attributeModel->getAttributeGroups())
		{
			if (!pair.second->getAnonymous())
			{
				groups.push_back(pair.second);
			}
		}
		
		auto orders(topologicalSort(groups));
		for (const auto order : orders)
		{
			auto node(m_attributeNormalizer.normalizeAttributeGroup(groups[order]));
			if (node == nullptr)
			{
				return std::make_pair(false, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
			}
			nodes.push_back(node);
		}

		return std::make_pair(true, std::move(nodes));
	}

	std::pair<bool, std::vector<std::shared_ptr<SSUtils::XML::Node>>> XSDNormalizer::normalizeComplexType(void)
	{
		const auto complexTypeModel = m_xsdModel->getComplexTypeModel();
		std::vector<XSDFrontend::ComplexType::IComplexTypeInterface *> complexTypes;
		for (const auto &pair : complexTypeModel->getComplexTypes())
		{
			if (!pair.second->getAnonymous())
			{
				complexTypes.push_back(pair.second);
			}
		}

		std::vector<std::shared_ptr<SSUtils::XML::Node>> nodes;
		auto orders(topologicalSort(complexTypes));
		for (const auto order : orders)
		{
			auto node(m_complexTypeNormalizer.normalizeComplexType(complexTypes[order]));
			if (node == nullptr)
			{
				// return std::make_pair(false, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
			}
			nodes.push_back(node);
		}

		for (const auto &pair : complexTypeModel->getGlobalElements())
		{
			auto node(m_complexTypeNormalizer.normalizeElement(pair.second));
			if (node == nullptr)
			{
				// return std::make_pair(false, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
			}
			nodes.push_back(node);
		}

		for (const auto &pair : complexTypeModel->getElementGroups())
		{
			if (!pair.second->getAnonymous())
			{
				auto node(m_complexTypeNormalizer.normalizeElementGroup(pair.second));
				if (node == nullptr)
				{
					// return std::make_pair(false, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
				}
				nodes.push_back(node);
			}
		}
		return std::make_pair(true, std::move(nodes));
	}
};
