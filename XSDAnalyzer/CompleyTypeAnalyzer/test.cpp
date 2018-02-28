#include "test.h"
#include "XMLUtils.h"
#include "FileUtils.h"
#include "XSDAnalyzer.h"

#include <iostream>

void testXMLUtils(void)
{
	using namespace boost::property_tree;

	std::string fileUrl("SCL_Enums.xsd");

	auto nodes(XMLUtils::scanXMLFile<StringConvertUtils::CharType::UTF8>(fileUrl));

	return;
}

void testNewXSDAnalyzer(void)
{
	XSDAnalyzer::XSDAnalyzer xsdAnalyzer;

	xsdAnalyzer.scan(FileUtils::initailPath() + "\\SCL.xsd");

	return;
}
