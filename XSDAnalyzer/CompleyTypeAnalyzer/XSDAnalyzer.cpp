#include "XSDAnalyzer.h"
#include "XSDToken.h"
#include "FileUtils.h"
#include "StringConvertUtils.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <iostream>
#include <deque>

namespace XSDAnalyzer
{
	XSDAnalyzer::XSDAnalyzer(void)
		: m_scanedFiles(), m_xsdModel(XSDFrontend::XSDModel::generateNewXSDModel()), 
		m_simpleTypeAnalyzer(m_xsdModel->getSimpleTypeModel()), 
		m_attributeAnalyzer(m_xsdModel->getSimpleTypeModel(), m_xsdModel->getAttributeTypeModel(), m_simpleTypeAnalyzer), 
		m_complexTypeAnalyzer(m_xsdModel->getSimpleTypeModel(), m_xsdModel->getAttributeTypeModel(), m_xsdModel->getComplexTypeModel(), m_simpleTypeAnalyzer, m_attributeAnalyzer)
	{
	}

	const bool XSDAnalyzer::scan(const std::string &fileUrl)
	{
		std::string filePath(FileUtils::getPathOfUrl(fileUrl));
		std::string fileName(FileUtils::getFileNameOfUrl(fileUrl));

		if (!FileUtils::checkFileExist(fileUrl))
		{
			std::cerr << "找不到文件'" << fileUrl << "'" << std::endl;
			return false;
		}

		auto xml(XMLUtils::scanXMLFile<StringConvertUtils::StringCodeId::UTF8>(fileUrl));
		
		if (!(xml.size() == 1) || !(xml.front().getTag() == XSDFrontend::Token::SchemaTag))
		{
			std::cerr << "文件'" << fileUrl << "'不是xsd文件" << std::endl;
			return false;
		}

		for (const auto &childNode : xml.front().getChildren())
		{
			if (childNode.getTag() == XSDFrontend::Token::IncludeTag)
			{
				if (!scanIncludeTag(fileName, filePath, childNode))
				{
					return false;
				}
			}
		}

		const auto topologicalOrder(topologicalSort(generateTopologicalTable(xml.front())));
		const auto childrens(xml.front().getChildren());
		for (const auto order : topologicalOrder)
		{
			const auto &childNode(childrens[order]);

			if (childNode.getTag() == XSDFrontend::Token::SimpleTypeTag)
			{
				m_simpleTypeAnalyzer.scanSimpleType(childNode);
			}
			else if (childNode.getTag() == XSDFrontend::Token::AttributeTag)
			{
				m_attributeAnalyzer.scanAttribute(childNode);
			}
			else if (childNode.getTag() == XSDFrontend::Token::AttributeGroupTag)
			{
				m_attributeAnalyzer.scanAttributeGroup(childNode);
			}
			else if (childNode.getTag() == XSDFrontend::Token::ElementTag)
			{
				m_complexTypeAnalyzer.scanElement(childNode);
			}
			else if (childNode.getTag() == XSDFrontend::Token::GroupTag)
			{
				m_complexTypeAnalyzer.scanElementGroup(childNode);
			}
			else if (childNode.getTag() == XSDFrontend::Token::ComplexTypeTag)
			{
				m_complexTypeAnalyzer.scanComplexType(childNode);
			}
		}

		m_scanedFiles.insert(fileUrl);
		return true;
	}

	const bool XSDAnalyzer::scanIncludeTag(const std::string &fileName, const std::string &filePath, const XMLUtils::XMLNode & node)
	{
		if (node.getTag() == XSDFrontend::Token::IncludeTag)
		{
			static const std::string EmptyString("");

			std::string targetFileName(node.getAttr(XSDFrontend::Token::SchemaLocationAttr));
			if (targetFileName == EmptyString)
			{
				std::cerr << "在文件'" << targetFileName << "'中存在非法的include tag" << std::endl;
				return false;
			}
			
			std::string targetFileUrl(filePath + FileUtils::PathSeperator + targetFileName);
			if (m_scanedFiles.find(targetFileUrl) == m_scanedFiles.cend())
			{
				return scan(targetFileUrl);
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}

	std::vector<std::set<int>> XSDAnalyzer::generateTopologicalTable(const XMLUtils::XMLNode & root)
	{
		static const std::set<std::string> ProvideTokenAttrs = 
		{
			XSDFrontend::Token::NameAttr
		};

		static const std::set<std::string> NeedTokenAttrs = 
		{
			XSDFrontend::Token::TypeAttr, XSDFrontend::Token::ReferenceAttr, XSDFrontend::Token::BaseTypeAttr
		};

		std::vector<std::pair<std::set<std::string>, std::set<std::string>>> tokens;

		for (const auto &node : root.getChildren())
		{
			decltype(tokens)::value_type thisTokens;
			std::deque<std::reference_wrapper<const XMLUtils::XMLNode>> nextNodes;
			nextNodes.push_back(node);

			while (!nextNodes.empty())
			{
				const auto &node(nextNodes.front().get());
				nextNodes.pop_front();

				for (const auto &attr : ProvideTokenAttrs)
				{
					if (node.hasAttr(attr))
					{
						thisTokens.first.insert(node.getAttr(attr));
					}
				}

				for (const auto &attr : NeedTokenAttrs)
				{
					if (node.hasAttr(attr))
					{
						thisTokens.second.insert(node.getAttr(attr));
					}
				}

				std::copy(node.getChildren().cbegin(), node.getChildren().cend(), std::back_inserter(nextNodes));
			}

			tokens.emplace_back(std::move(thisTokens));
		}

		std::vector<std::set<int>> ret(root.getChildren().size());
		for (int i(0), k(root.getChildren().size()); i != k; ++i)
		{
			for (int j(0); j != k; ++j)
			{
				if (i != j)
				{
					for (const auto &needToken : tokens[i].second)
					{
						if (tokens[j].first.find(needToken) != tokens[j].first.cend())
						{
							ret[i].insert(j);
						}
					}
				}
			}

// 			for (const auto &needToken : tokens[i].second)
// 			{
// 				if (m_xsdModel->hasToken(needToken))
// 				{
// 					ret[i].insert(-1);
// 					break;
// 				}
// 			}
		}

		return ret;
	}

	std::vector<int> XSDAnalyzer::topologicalSort(const std::vector<std::set<int>>& table)
	{
		std::vector<int> inDegrees;
		std::transform(table.cbegin(), table.cend(), std::back_inserter(inDegrees),
			[](const std::set<int> &item) -> int
		{
			return item.size();
		});

		std::deque<int> items;
		for (int i(0), j(inDegrees.size()); i != j; ++i)
		{
			if (inDegrees[i] == 0 || (inDegrees[i] == 1 && *table[i].cbegin() == -1))
			{
				items.push_back(i);
			}
		}

		std::vector<int> ret;
		while (!items.empty())
		{
			int item(items.front());
			items.pop_front();

			for (int i(0), j(table.size()); i != j; ++i)
			{
				if (table[i].find(item) != table[i].cend())
				{
					--inDegrees[i];

					if (inDegrees[i] == 0)
					{
						items.push_back(i);
					}
				}
			}

			ret.push_back(item);
		}

		return ret;
	}
};
