#include "test.h"
#include "XMLUtils.h"
#include "MathUtils.h"
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
	std::cout << xsdAnalyzer.scan(SSUtils::File::InitailPath + "\\SCL.xsd", SSUtils::CharType::UTF8) << std::endl;
	auto model = xsdAnalyzer.getModel();

	model->setDescription(std::string("������"));

	XSDNormalizer::XSDNormalizer xsdNormalizer(model);
	std::cout << xsdNormalizer.normalize() << std::endl;
	std::cout << xsdNormalizer.getDocument().toFile(SSUtils::File::InitailPath + "\\test.xsd", SSUtils::CharType::UTF8) << std::endl;

	return;
}

void testXSDAnalyzerAndNormalizer(void)
{
	XSDAnalyzer::XSDAnalyzer xsdAnalyzer;
	std::cout << xsdAnalyzer.scan(SSUtils::File::InitailPath + "\\test.xsd", SSUtils::CharType::UTF8) << std::endl;
	auto model = xsdAnalyzer.getModel();

	model->setDescription(std::string("������"));

	XSDNormalizer::XSDNormalizer xsdNormalizer(model);
	std::cout << xsdNormalizer.normalize() << std::endl;
	std::cout << xsdNormalizer.getDocument().toFile(SSUtils::File::InitailPath + "\\test1.xsd", SSUtils::CharType::UTF8) << std::endl;

	return;
}

void testPaper(void)
{
	auto model = XSDFrontend::XSDModel::generateNewXSDModel();
	auto stModel = model->getSimpleTypeModel();
	auto ctModel = model->getComplexTypeModel();
	
	auto st1 = std::shared_ptr<XSDFrontend::SimpleType::NumberType>(new XSDFrontend::SimpleType::NumberType(std::string("b�缫����")));
	st1->setIsEnum(true);
	st1->setBaseType(XSDFrontend::SimpleType::NumberType::eBaseType::tInteger);
	st1->addEnumValue(1);
	st1->addEnumValue(2);
	st1->addEnumValue(3);
	stModel->getNumberTypes().insert(std::make_pair(st1->getName(), st1));
	auto ct1 = std::shared_ptr<XSDFrontend::ComplexType::SimpleContent>(new XSDFrontend::ComplexType::SimpleContent(std::string("�缫����")));
	ct1->setBaseType(XSDFrontend::ComplexType::IComplexTypeInterface::eDerivedType::tExtension, st1->getName());
	ct1->setExAttr(std::make_pair(std::string("experimental_factor_type"), std::string("ExperimentalFactor")));
	ctModel->getSimpleContents().insert(std::make_pair(ct1->getName(), ct1));

	auto st2 = std::shared_ptr<XSDFrontend::SimpleType::NumberType>(new XSDFrontend::SimpleType::NumberType(std::string("b�¶�")));
	st2->setIsEnum(true);
	st2->setBaseType(XSDFrontend::SimpleType::NumberType::eBaseType::tDecimal);
	st2->addEnumValue(15.0f);
	st2->addEnumValue(75.0f);
	st2->addEnumValue(125.0f);
	stModel->getNumberTypes().insert(std::make_pair(st2->getName(), st2));
	auto ct2 = std::shared_ptr<XSDFrontend::ComplexType::SimpleContent>(new XSDFrontend::ComplexType::SimpleContent(std::string("�¶�")));
	ct2->setBaseType(XSDFrontend::ComplexType::IComplexTypeInterface::eDerivedType::tExtension, st2->getName());
	ct2->setExAttr(std::make_pair(std::string("experimental_factor_type"), std::string("ExperimentalFactor")));
	ct2->setExAttr(std::make_pair(std::string("unit"), std::string("��F")));
	ctModel->getSimpleContents().insert(std::make_pair(ct2->getName(), ct2));

	auto st3 = std::shared_ptr<XSDFrontend::SimpleType::NumberType>(new XSDFrontend::SimpleType::NumberType(std::string("b�����Ч����")));
	st3->setBaseType(XSDFrontend::SimpleType::NumberType::eBaseType::tDecimal);
	stModel->getNumberTypes().insert(std::make_pair(st3->getName(), st3));
	auto ct3 = std::shared_ptr<XSDFrontend::ComplexType::SimpleContent>(new XSDFrontend::ComplexType::SimpleContent(std::string("�����Ч����")));
	ct3->setBaseType(XSDFrontend::ComplexType::IComplexTypeInterface::eDerivedType::tExtension, st3->getName());
	ct3->setExAttr(std::make_pair(std::string("experimental_factor_type"), std::string("EvaluateFactor")));
	ct3->setExAttr(std::make_pair(std::string("unit"), std::string("h")));
	ctModel->getSimpleContents().insert(std::make_pair(ct3->getName(), ct3));

	XSDNormalizer::XSDNormalizer xsdNormalizer(model);
	xsdNormalizer.normalize();
	xsdNormalizer.getDocument().toFile(SSUtils::File::InitailPath + "\\������.xsd", SSUtils::CharType::UTF8);

	return;
}

