#pragma once

#include "SimpleTypeNormalizer.h"
#include "AttributeNormalizer.h"
#include "ComplexTypeNormalizer.h"
#include "XSDModel.h"

namespace XSDNormalizer
{
	class XSDNormalizer
	{
	public:
		XSDNormalizer(const std::shared_ptr<XSDFrontend::XSDModel> model);
		XSDNormalizer(const XSDNormalizer &ano) = delete;
		XSDNormalizer(XSDNormalizer &&ano) = delete;
		XSDNormalizer &operator=(const XSDNormalizer &rhs) = delete;
		XSDNormalizer &operator=(XSDNormalizer &&rhs) = delete;
		~XSDNormalizer(void) = default;

		const bool normalize(void);

		inline const SSUtils::XML::Document &getDocument(void) const { return m_xmlDoc; }

	private:
		std::pair<bool, std::vector<std::shared_ptr<SSUtils::XML::Node>>> normalizeSimpleType(void);
		std::pair<bool, std::vector<std::shared_ptr<SSUtils::XML::Node>>> normalizeAttribute(void);
		std::pair<bool, std::vector<std::shared_ptr<SSUtils::XML::Node>>> normalizeComplexType(void);

		template<typename T>
		std::vector<int> topologicalSort(const std::vector<T *> items)
		{
			std::vector<std::pair<std::set<std::string>, std::set<std::string>>> tokens;
			for (const T *item : items)
			{
				tokens.push_back(std::make_pair(item->suppliedTokens(), item->neededTokens()));
			}

			std::vector<std::set<int>> topologicTable(items.size());
			for (int i(0), k(items.size()); i != k; ++i)
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

	private:
		std::shared_ptr<XSDFrontend::XSDModel> m_xsdModel;
		SSUtils::XML::Document m_xmlDoc;

		SimpleTypeNormalizer m_simpleTypeNormalizer;
		AttributeNormalizer m_attributeNormalizer;
		ComplexTypeNormalizer m_complexTypeNormalizer;
	};
};
