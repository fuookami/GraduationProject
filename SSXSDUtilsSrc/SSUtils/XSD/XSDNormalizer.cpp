#include "stdafx.h"
#include "XSDNormalizer.h"
#include "SSUtils\ThreadUtils.h"

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
		try
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
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			return false;
		}
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
		const auto simpleTypeModel = m_xsdModel->getSimpleTypeModel();
		const auto complexTypeModel = m_xsdModel->getComplexTypeModel();
		std::vector<std::shared_ptr<SSUtils::XML::Node>> nodes;
		for (const auto &pair : complexTypeModel->getGlobalElements())
		{
			if (pair.second->getCategory() == XSDFrontend::ComplexType::Element::eCategory::tBaseType 
				|| pair.second->getCategory() == XSDFrontend::ComplexType::Element::eCategory::tSimpleType)
			{
				auto node(m_complexTypeNormalizer.normalizeElement(pair.second));
				if (node == nullptr)
				{
					return std::make_pair(false, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
				}
				nodes.push_back(node);
			}
		}

		std::vector<XSDFrontend::ComplexType::IComplexTypeInterface *> complexTypes;
		for (const auto &pair : complexTypeModel->getComplexTypes())
		{
			complexTypes.push_back(pair.second);
		}

		std::vector<std::shared_ptr<XSDFrontend::ComplexType::Element>> elements;
		for (const auto &pair : complexTypeModel->getGlobalElements())
		{
			if (pair.second->getCategory() == XSDFrontend::ComplexType::Element::eCategory::tSimpleContent
				|| pair.second->getCategory() == XSDFrontend::ComplexType::Element::eCategory::tComplexContent)
			{
				elements.push_back(pair.second);
			}
		}

		std::vector<std::shared_ptr<XSDFrontend::ComplexType::ElementGroup>> elementGroups;
		for (const auto &pair : complexTypeModel->getElementGroups())
		{
			elementGroups.push_back(pair.second);
		}

		auto orders = topologicalSort(complexTypes, elements, elementGroups);
		for (const auto order : orders)
		{
			switch (order.first)
			{
			case 0:
			{
				if (!complexTypes[order.second]->getAnonymous())
				{
					auto node = m_complexTypeNormalizer.normalizeComplexType(complexTypes[order.second]);
					if (node == nullptr)
					{
						return std::make_pair(false, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
					}
					nodes.push_back(node);
				}
			}
				break;
			case 1:
			{
				auto node = m_complexTypeNormalizer.normalizeElement(elements[order.second]);
				if (node == nullptr)
				{
					return std::make_pair(false, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
				}
				nodes.push_back(node);
			}
				break;
			case 2:
			{
				if (!elementGroups[order.second]->getAnonymous())
				{
					auto node = m_complexTypeNormalizer.normalizeElementGroup(elementGroups[order.second]);
					if (node == nullptr)
					{
						return std::make_pair(false, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
					}
					nodes.push_back(node);
				}
			}
				break;
			default:
				return std::make_pair(false, std::vector<std::shared_ptr<SSUtils::XML::Node>>());
			}
		}

		return std::make_pair(true, std::move(nodes));
	}

	std::vector<int> XSDNormalizer::_topologicalSort(const std::vector<std::pair<std::set<std::string>, std::set<std::string>>> &tokens)
	{
		std::vector<std::set<int>> topologicTable(tokens.size());
		for (int i(0), k(tokens.size()); i != k; ++i)
		{
			for (int j(0); j != k; ++j)
			{
				if (i != j)
				{
					for (const auto &needToken : tokens[i].second)
					{
						if (tokens[j].first.find(needToken) != tokens[j].first.cend())
						{
							topologicTable[i].insert(j);
						}
					}
				}
			}
		}

		return SSUtils::Math::TopologicalSort(topologicTable);
	}
};
