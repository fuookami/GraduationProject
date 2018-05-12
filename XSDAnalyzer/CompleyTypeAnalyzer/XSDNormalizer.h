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
		std::vector<int> topologicalSort(const std::vector<T> &items)
		{
			std::vector<std::pair<std::set<std::string>, std::set<std::string>>> tokens;
			for (const T item : items)
			{
				tokens.push_back(std::make_pair(item->suppliedTokens(), item->neededTokens()));
			}

			return _topologicalSort(tokens);
		}

		template<typename T, typename U>
		std::vector<std::pair<int, int>> topologicalSort(const std::vector<T> &itemAs, const std::vector<U> &itemBs)
		{
			std::vector<std::pair<std::set<std::string>, std::set<std::string>>> tokens;
			for (const T item : itemAs)
			{
				tokens.push_back(std::make_pair(item->suppliedTokens(), item->neededTokens()));
			}
			for (const T item : itemBs)
			{
				tokens.push_back(std::make_pair(item->suppliedTokens(), item->neededTokens()));
			}

			auto orders(_topologicalSort(tokens));
			std::vector<std::pair<int, int>> ret;
			for (const auto &order : orders)
			{
				ret.push_back(order < itemAs.size() ? std::make_pair(0, order) : std::make_pair(1, order - itemAs.size()));
			}
			return ret;
		}

		template<typename T, typename U, typename S>
		std::vector<std::pair<int, int>> topologicalSort(const std::vector<T> &itemAs, const std::vector<U> &itemBs, const std::vector<S> &itemCs)
		{
			std::vector<std::pair<std::set<std::string>, std::set<std::string>>> tokens;
			for (const T item : itemAs)
			{
				tokens.push_back(std::make_pair(item->suppliedTokens(), item->neededTokens()));
			}
			for (const T item : itemBs)
			{
				tokens.push_back(std::make_pair(item->suppliedTokens(), item->neededTokens()));
			}
			for (const T item : itemCs)
			{
				tokens.push_back(std::make_pair(item->suppliedTokens(), item->neededTokens()));
			}

			auto orders(_topologicalSort(tokens));
			const int offset_c = itemAs.size() + itemBs.size();
			std::vector<std::pair<int, int>> ret;
			for (const auto &order : orders)
			{
				ret.push_back(order < itemAs.size() ? std::make_pair(0, order)
					: order < offset_c ? std::make_pair(1, order - itemAs.size())
					: std::make_pair(2, order - offset_c));
			}
			return ret;
		}

	private:
		std::vector<int> _topologicalSort(const std::vector<std::pair<std::set<std::string>, std::set<std::string>>> &tokens);

	private:
		std::shared_ptr<XSDFrontend::XSDModel> m_xsdModel;
		SSUtils::XML::Document m_xmlDoc;

		SimpleTypeNormalizer m_simpleTypeNormalizer;
		AttributeNormalizer m_attributeNormalizer;
		ComplexTypeNormalizer m_complexTypeNormalizer;
	};
};
