#include "test.h"
#include "XMLUtils.h"
#include "FileUtils.h"
#include "XSDAnalyzer.h"
#include "XSDNormalizer.h"

#include <iostream>

void testXMLUtils(void)
{
	using namespace boost::property_tree;

	std::string fileUrl("SCL_Enums.xsd");

	// auto nodes(XMLUtils::scanXMLFile<StringConvertUtils::CharType::UTF8>(fileUrl));

	return;
}

void testNewXSDAnalyzer(void)
{
	XSDAnalyzer::XSDAnalyzer xsdAnalyzer;
	xsdAnalyzer.scan(SSUtils::File::InitailPath + "\\SCL.xsd", SSUtils::CharType::UTF8);
	auto model = xsdAnalyzer.getModel();

	model->setDescription(std::string("≤‚ ‘”√"));

	XSDNormalizer::XSDNormalizer xsdNormalizer;
	xsdNormalizer.normalize(model);
	xsdNormalizer.getDocument().toFile(SSUtils::File::InitailPath + "\\test.xsd", SSUtils::CharType::UTF8);

	return;
}

void testXSDAnalyzerAndNormalizer(void)
{
	XSDAnalyzer::XSDAnalyzer xsdAnalyzer;
	xsdAnalyzer.scan(SSUtils::File::InitailPath + "\\test.xsd", SSUtils::CharType::UTF8);
	auto model = xsdAnalyzer.getModel();

	XSDNormalizer::XSDNormalizer xsdNormalizer;
	xsdNormalizer.normalize(model);
	xsdNormalizer.getDocument().toFile(SSUtils::File::InitailPath + "\\test1.xsd", SSUtils::CharType::UTF8);

	return;
}
