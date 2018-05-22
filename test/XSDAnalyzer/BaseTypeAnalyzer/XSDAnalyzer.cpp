#include "XSDAnalyzer.h"
#include "XSDToken.h"
#include "FileUtils.h"
#include "StringConvertUtils.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <iostream>

namespace XSDAnalyzer
{
	XSDAnalyzer::XSDAnalyzer(void)
		: m_scanedFiles(), m_simpleTypeAnalyzer()
	{
	}

	XSDAnalyzer::~XSDAnalyzer(void)
	{
	}

	const bool XSDAnalyzer::scan(const std::string &fileUrl)
	{
		using namespace boost::property_tree;
		std::string filePath(FileUtils::getPathOfUrl(fileUrl));
		std::string fileName(FileUtils::getFileNameOfUrl(fileUrl));

		ptree pt;
		xml_parser::read_xml(fileUrl, pt);

		try
		{
			for (const auto &root : pt)
			{
				if (root.first == Token::SchemaTag)
				{
					for (const auto &schemaRoot : root.second)
					{
						if (schemaRoot.first == Token::IncludeTag)
						{
							static const std::string EmptyString("");

							const auto &includeTag(schemaRoot.second);
							const auto &includeTagAttrs(schemaRoot.second.get_child(Token::AttrTag));
							std::string targetFileName(StringConvertUtils::toLocal<StringConvertUtils::StringCodeId::UTF8>(includeTagAttrs.get<std::string>(Token::SchemaLocationAttr, EmptyString)));

							if (targetFileName != EmptyString)
							{
								std::string targetFileUrl(filePath + '\\' + targetFileName);
								if (FileUtils::checkFileExist(targetFileUrl))
								{
									if (m_scanedFiles.find(targetFileUrl) == m_scanedFiles.cend()
										&& scan(targetFileUrl))
									{
										m_scanedFiles.insert(targetFileUrl);
									}
									else
									{
										std::cerr << "XSD文件'" << targetFileUrl << "'不符合XSD语法，解析失败" << std::endl;
										return false;
									}
								}
								else
								{
									std::cerr << "找不到文件'" << targetFileUrl << "'" << std::endl;
									return false;
								}
							}
							else
							{
								std::cerr << "在文件'" << fileName << "'出现非法的include tag" << std::endl;
								return false;
							}
						}
						else if (schemaRoot.first == Token::SimpleTypeTag)
						{
							m_simpleTypeAnalyzer.scan(schemaRoot.second);
						}
					}
				}
			}

			return true;
		}
		catch (std::exception e)
		{
			std::cerr << e.what() << std::endl;
			return false;
		}

		return true;
	}
};
