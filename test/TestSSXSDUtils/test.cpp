#include "test.h"
#include "XMLUtils.h"
#include "MathUtils.h"
#include "FileUtils.h"
#include "XSDAnalyzer.h"
#include "XSDNormalizer.h"

#include <iostream>
#include <algorithm>

static const std::vector<int> orders = 
	[]()
{
	std::vector<int> orders;
	for (int i(0), j(36); i != j; ++i)
	{
		orders.push_back(i);
	}
	std::random_shuffle(orders.begin(), orders.end());
	return orders;
}();

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
	std::cout << xsdAnalyzer.scan(SSUtils::File::InitailPath() + "\\SCL.xsd", SSUtils::CharType::UTF8) << std::endl;
	auto model = xsdAnalyzer.getModel();

	model->setDescription(std::string("测试用"));

	XSDNormalizer::XSDNormalizer xsdNormalizer(model);
	std::cout << xsdNormalizer.normalize() << std::endl;
	std::cout << xsdNormalizer.getDocument().toFile(SSUtils::File::InitailPath() + "\\test.xsd", SSUtils::CharType::UTF8) << std::endl;

	return;
}

void testXSDAnalyzerAndNormalizer(void)
{
	XSDAnalyzer::XSDAnalyzer xsdAnalyzer;
	std::cout << xsdAnalyzer.scan(SSUtils::File::InitailPath() + "\\test.xsd", SSUtils::CharType::UTF8) << std::endl;
	auto model = xsdAnalyzer.getModel();

	model->setDescription(std::string("测试用"));

	XSDNormalizer::XSDNormalizer xsdNormalizer(model);
	std::cout << xsdNormalizer.normalize() << std::endl;
	std::cout << xsdNormalizer.getDocument().toFile(SSUtils::File::InitailPath() + "\\test1.xsd", SSUtils::CharType::UTF8) << std::endl;

	return;
}

void testPaper(void)
{
	auto model = XSDFrontend::XSDModel::generateNewXSDModel();
	auto stModel = model->getSimpleTypeModel();
	auto attrModel = model->getAttributeModel();
	auto ctModel = model->getComplexTypeModel();
	
	{
		auto st = std::shared_ptr<XSDFrontend::SimpleType::NumberType>(new XSDFrontend::SimpleType::NumberType(std::string("b电极材料")));
		st->setIsEnum(true);
		st->setBaseType(XSDFrontend::SimpleType::NumberType::eBaseType::tInteger);
		st->addEnumValue(1);
		st->addEnumValue(2);
		st->addEnumValue(3);
		stModel->getNumberTypes().insert(std::make_pair(st->getName(), st));
		auto ct = std::shared_ptr<XSDFrontend::ComplexType::SimpleContent>(new XSDFrontend::ComplexType::SimpleContent(std::string("电极材料")));
		ct->setBaseType(XSDFrontend::ComplexType::IComplexTypeInterface::eDerivedType::tExtension, st->getName());
		ct->setExAttr(std::make_pair(std::string("experimental_factor_type"), std::string("ExperimentalFactor")));
		ctModel->getSimpleContents().insert(std::make_pair(ct->getName(), ct));
	}

	{
		auto st = std::shared_ptr<XSDFrontend::SimpleType::NumberType>(new XSDFrontend::SimpleType::NumberType(std::string("b温度")));
		st->setIsEnum(true);
		st->setBaseType(XSDFrontend::SimpleType::NumberType::eBaseType::tDecimal);
		st->addEnumValue(15.0f);
		st->addEnumValue(70.0f);
		st->addEnumValue(125.0f);
		stModel->getNumberTypes().insert(std::make_pair(st->getName(), st));
		auto ag = std::shared_ptr<XSDFrontend::Attribute::AttributeGroup>(new XSDFrontend::Attribute::AttributeGroup(attrModel->getNewDefaultAttributeGroupName()));
		ag->setAnonymous(true);
		auto at1 = std::shared_ptr<XSDFrontend::Attribute::Attribute>(new XSDFrontend::Attribute::Attribute(std::string("unit"), std::string("xs:string")));
		at1->setFixed(std::string("°F"));
		ag->setOrAddAttribute(at1);
		auto at2 = std::shared_ptr<XSDFrontend::Attribute::Attribute>(new XSDFrontend::Attribute::Attribute(std::string("digits"), std::string("xs:string")));
		at2->setFixed(std::string("3"));
		ag->setOrAddAttribute(at2);
		attrModel->getAttributeGroups().insert(std::make_pair(ag->getName(), ag));
		auto ct = std::shared_ptr<XSDFrontend::ComplexType::SimpleContent>(new XSDFrontend::ComplexType::SimpleContent(std::string("温度")));
		ct->setBaseType(XSDFrontend::ComplexType::IComplexTypeInterface::eDerivedType::tExtension, st->getName());
		ct->setExAttr(std::make_pair(std::string("experimental_factor_type"), std::string("ExperimentalFactor")));
		ct->setExAttr(std::make_pair(std::string("unit"), std::string("°F")));
		ct->setExAttr(std::make_pair(std::string("digits"), std::string("3")));
		ct->setAttributeGroupName(ag->getName());
		ctModel->getSimpleContents().insert(std::make_pair(ct->getName(), ct));
	}
	
	{
		auto st = std::shared_ptr<XSDFrontend::SimpleType::NumberType>(new XSDFrontend::SimpleType::NumberType(std::string("b电池有效寿命")));
		st->setBaseType(XSDFrontend::SimpleType::NumberType::eBaseType::tDecimal);
		stModel->getNumberTypes().insert(std::make_pair(st->getName(), st));
		auto ag = std::shared_ptr<XSDFrontend::Attribute::AttributeGroup>(new XSDFrontend::Attribute::AttributeGroup(attrModel->getNewDefaultAttributeGroupName()));
		ag->setAnonymous(true);
		auto at1 = std::shared_ptr<XSDFrontend::Attribute::Attribute>(new XSDFrontend::Attribute::Attribute(std::string("unit"), std::string("xs:string")));
		at1->setFixed(std::string("h"));
		ag->setOrAddAttribute(at1);
		auto at2 = std::shared_ptr<XSDFrontend::Attribute::Attribute>(new XSDFrontend::Attribute::Attribute(std::string("digits"), std::string("xs:string")));
		at2->setFixed(std::string("3"));
		ag->setOrAddAttribute(at2);
		attrModel->getAttributeGroups().insert(std::make_pair(ag->getName(), ag));
		auto ct = std::shared_ptr<XSDFrontend::ComplexType::SimpleContent>(new XSDFrontend::ComplexType::SimpleContent(std::string("电池有效寿命")));
		ct->setBaseType(XSDFrontend::ComplexType::IComplexTypeInterface::eDerivedType::tExtension, st->getName());
		ct->setExAttr(std::make_pair(std::string("experimental_factor_type"), std::string("EvaluateFactor")));
		ct->setExAttr(std::make_pair(std::string("unit"), std::string("h")));
		ct->setExAttr(std::make_pair(std::string("digits"), std::string("3")));
		ct->setAttributeGroupName(ag->getName());
		ctModel->getSimpleContents().insert(std::make_pair(ct->getName(), ct));
	}

	XSDNormalizer::XSDNormalizer xsdNormalizer(model);
	xsdNormalizer.normalize();
	xsdNormalizer.getDocument().toFile(SSUtils::File::InitailPath() + "\\论文用1.xsd", SSUtils::CharType::UTF8);

	return;
}

void testPaper2(void)
{
	std::vector<int> data1s = { 1,2,3 };
	std::vector<std::string> data2s = { std::string("15.000"), std::string("70.000"), std::string("125.000") };
	std::vector<std::pair<int, std::string>> datas;
	for (const int data1 : data1s)
	{
		for (const std::string &data2 : data2s)
		{
			datas.push_back(std::make_pair(data1, data2));
			datas.push_back(std::make_pair(data1, data2));
			datas.push_back(std::make_pair(data1, data2));
			datas.push_back(std::make_pair(data1, data2));
		}
	}

	auto root(SSUtils::XML::Node::generate(std::string("experimental_design_table")));
	for (int i(0), j(orders.size()); i != j; ++i)
	{
		auto line(SSUtils::XML::Node::generate(std::string("batch")));
		
		auto node1(SSUtils::XML::Node::generate(std::string("电极材料")));
		node1->setContent(std::to_string(datas[orders[i]].first));
		line->addChild(node1);
		
		auto node2(SSUtils::XML::Node::generate(std::string("温度")));
		node2->setContent(datas[orders[i]].second);
		node2->setAttr(std::string("unit"), std::string("°F"));
		line->addChild(node2);

		auto node3(SSUtils::XML::Node::generate(std::string("电池有效寿命")));
		node3->setAttr(std::string("unit"), std::string("h"));
		line->addChild(node3);

		root->addChild(line);
	}

	SSUtils::XML::Document doc;
	doc.getRoots().push_back(root);
	doc.toFile(SSUtils::File::InitailPath() + "\\论文用2.xml", SSUtils::CharType::UTF8);
}

void testPaper3(void)
{
	std::vector<int> data1s = { 1,2,3 };
	std::vector<std::string> data2s = { std::string("15.000"), std::string("70.000"), std::string("125.000") };
	std::vector<std::pair<int, std::string>> datas;
	for (const int data1 : data1s)
	{
		for (const std::string &data2 : data2s)
		{
			datas.push_back(std::make_pair(data1, data2));
			datas.push_back(std::make_pair(data1, data2));
			datas.push_back(std::make_pair(data1, data2));
			datas.push_back(std::make_pair(data1, data2));
		}
	}

	auto root(SSUtils::XML::Node::generate(std::string("tbody")));
	for (int i(0), j(orders.size()); i != j; ++i)
	{
		auto line(SSUtils::XML::Node::generate(std::string("tr")));

		auto node(SSUtils::XML::Node::generate(std::string("td")));
		node->setContent(std::to_string(i + 1));
		line->addChild(node);

		auto node1(SSUtils::XML::Node::generate(std::string("td")));
		node1->setContent(std::to_string(datas[orders[i]].first));
		line->addChild(node1);

		auto node2(SSUtils::XML::Node::generate(std::string("td")));
		node2->setContent(datas[orders[i]].second + std::string("°F"));
		line->addChild(node2);

		auto node3(SSUtils::XML::Node::generate(std::string("td")));
		node3->setContent(std::string("h"));
		line->addChild(node3);

		root->addChild(line);
	}

	SSUtils::XML::Document doc;
	doc.getRoots().push_back(root);
	doc.toFile(SSUtils::File::InitailPath() + "\\论文用3.xml", SSUtils::CharType::UTF8);
}
