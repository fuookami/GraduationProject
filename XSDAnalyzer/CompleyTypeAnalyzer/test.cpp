#include "test.h"
#include "XMLUtils.h"
#include "FileUtils.h"
#include "XSDAnalyzer.h"

#include <iostream>

void testXMLUtils(void)
{
	using namespace boost::property_tree;

	std::string fileUrl("SCL_Enums.xsd");

	/*
	ptree pt;
	xml_parser::read_xml(fileUrl, pt);

	std::vector<XMLUtils::XMLNode> nodes;
	for (const auto &root : pt)
	{
		auto node(XMLUtils::getTree(root));
		std::cout << node.tag() << std::endl;

		nodes.push_back(std::move(node));
		nodes.back().tidyStruct();
	}
	*/

	auto nodes(XMLUtils::scanXMLFile(fileUrl));

	return;
}

void testNewXSDAnalyzer(void)
{
	XSDAnalyzer::XSDAnalyzer xsdAnalyzer;

	xsdAnalyzer.scan(FileUtils::initailPath() + "\\SCL.xsd");

	return;
}
