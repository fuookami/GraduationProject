#include "test.h"
#include "XSDAnalyzer.h"
#include "XSDToken.h"
#include "NumberVariant.h"
#include "FileUtils.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <iostream>
#include <exception>

void testSimpleType(void)
{
	using namespace boost::property_tree;

	const std::string fileUrl("SCL_BaseSimpleTypes.xsd");

	ptree pt;
	xml_parser::read_xml(fileUrl, pt);

	XSDAnalyzer::SimpleTypeAnalyzer simpleTypeAnalyzer;
	try
	{
		for (const auto &root : pt)
		{
			if (root.first == XSDAnalyzer::Token::SchemaTag)
			{
				for (const auto &schemaRoot : root.second)
				{
					if (schemaRoot.first == XSDAnalyzer::Token::SimpleTypeTag)
					{
						std::cout << simpleTypeAnalyzer.scan(schemaRoot.second) << std::endl;
					}
				}
			}
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	return;
}

void testXSDAnalyzer(void)
{
	XSDAnalyzer::XSDAnalyzer xsdAnalyzer;

	xsdAnalyzer.scan(FileUtils::initailPath() + "\\SCL_Enums.xsd");

	return;
}

void testNumberVariant(void)
{
	NumberVariant number;
	number.set(true);

	std::cout << (int)number.type() << ' ' << number.toString() << ' ' << number.get<bool>() << ' ' << number.getBool() << std::endl;

	number.set(false);
	std::cout << (int)number.type() << ' ' << number.toString() << ' ' << number.get<bool>() << ' ' << number.getBool() << std::endl;

	number.set(1.0f);
	std::cout << (int)number.type() << ' ' << number.toString() << ' ' << number.get<float>() << ' ' << number.getFloat() << ' ' << number.getDouble() << std::endl;

	number.set(3.43f);
	std::cout << (int)number.type() << ' ' << number.toString() << ' ' << number.get<float>() << ' ' << number.getFloat() << ' ' << number.getDouble() << std::endl;

	DataUtils::Data data = number.toData();

	NumberVariant number2(data);

	std::cout << (int)number2.type() << ' ' << number2.toString() << ' ' << number2.get<float>() << ' ' << number2.getFloat() << ' ' << number2.getDouble() << std::endl;
}

void testHexString(void)
{
	DataUtils::Data bytes = { 0x12, 0x13, 0xf1, 0xf2 };

	std::string hexString(DataUtils::toHexString(bytes, " "));
	std::cout << hexString << std::endl;

	DataUtils::Data bytes2(DataUtils::fromHexString(hexString, " "));
}

void testBase64(void)
{
	DataUtils::Data bytes = { 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };

	std::string base64String(DataUtils::toBase64String(bytes));
	std::cout << base64String << std::endl;

	DataUtils::Data bytes2(DataUtils::fromBase64String(base64String));
}
