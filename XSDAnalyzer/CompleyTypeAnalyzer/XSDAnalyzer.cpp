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
		: m_scanedFiles(), m_xsdModel(XSDFrontend::XSDModel::generateNewXSDModel()), 
		m_simpleTypeAnalyzer(m_xsdModel->getSimpleTypeModel()), 
		m_attributeAnalyzer(m_xsdModel->getSimpleTypeModel(), m_xsdModel->getAttributeTypeModel(), m_simpleTypeAnalyzer), 
		m_complexTypeAnalyzer(m_xsdModel->getSimpleTypeModel(), m_xsdModel->getAttributeTypeModel(), m_xsdModel->getComplexTypeModel(), m_simpleTypeAnalyzer, m_attributeAnalyzer)
	{
	}

	XSDAnalyzer::~XSDAnalyzer(void)
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

		auto xml(XMLUtils::scanXMLFile(fileUrl));

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
			else if (childNode.getTag() == XSDFrontend::Token::SimpleTypeTag)
			{
				m_simpleTypeAnalyzer.scan(childNode);
			}
			else if (childNode.getTag() == XSDFrontend::Token::AttributeTag)
			{
				m_attributeAnalyzer.scanAttribute(childNode);
			}
			else if (childNode.getTag() == XSDFrontend::Token::AttributeGroupTag)
			{
				m_attributeAnalyzer.scanAttributeGroup(childNode);
			}
			else if (childNode.getTag() == XSDFrontend::Token::GroupTag)
			{

			}
			else if (childNode.getTag() == XSDFrontend::Token::CompleyTypeTag)
			{

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
};
