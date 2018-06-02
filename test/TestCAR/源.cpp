#include "CARSDK/ExperimentalDesignMethodModule.h"
#include "CARSDK/ExperimentalAnalyzerModule.h"

#include "SSUtils/FileUtils.h"
#include "SSUtils/XSD/XSDNormalizer.h"
#include <iostream>

void testSharedLibrary(void);
void testModeling(void);

int main(void)
{
	testSharedLibrary();
	// testModeling();

	system("pause");
	return 0;
}

void testSharedLibrary(void)
{
	auto EDMMod(CARSDK::ExperimentalDesignMethodModule::instance(std::string("D:\\project\\GraduationProject\\GraduationProject\\x64\\Debug\\plugins")));
	auto EAMod(CARSDK::ExperimentalAnalyzerModule::instance());
	std::cout << EDMMod->utils().size() << std::endl;
	for (const auto &pair : EDMMod->utils())
	{
		std::cout << pair.first << ' ' << pair.second->displayName() << std::endl;
		for (const auto &_pair : pair.second->methods())
		{
			std::cout << '\t' << _pair.first << ' ' << _pair.second->displayName() << ' ' << _pair.second->valid(std::map<std::string, std::string>()) << ' ' << _pair.second->lastError() << std::endl;
		}
	}
	std::cout << std::endl;
	for (const auto &pair : EAMod->utils())
	{
		std::cout << pair.first << ' ' << std::endl;
		for (const auto &_pair : pair.second->analyzerGroups())
		{
			std::cout << '\t' << pair.first << ' ' << std::endl;
			for (const auto &__pair : _pair.second->analyzers())
			{
				std::cout << "\t\t" << __pair.first << ' ' << std::endl;
			}
		}
	}

}

void testModeling(void)
{
	std::vector<CARSDK::DataModelingModule::Info> infos;

	{
		CARSDK::DataModelingModule::Info info;
		info.name.assign("电极材料");
		info.type.assign("xs:integer");
		info.experimentalFactorType.assign(CARSDK::ExperimentalFactorType2String().left.find(CARSDK::ExperimentalFactorType::ExperimentalFactor)->second);
		info.validators.insert(std::make_pair(XSDFrontend::Token::EnumValidatorTag(), boost::any(std::vector<SSUtils::Math::Real>({1, 2, 3}))));
		infos.push_back(std::move(info));
	}

	{
		CARSDK::DataModelingModule::Info info;
		info.name.assign("温度");
		info.type.assign("xs:decimal");
		info.experimentalFactorType.assign(CARSDK::ExperimentalFactorType2String().left.find(CARSDK::ExperimentalFactorType::ExperimentalFactor)->second);
		info.attributes.insert(std::make_pair(std::string("unit"), std::string("°F")));
		info.attributes.insert(std::make_pair(std::string("digits"), std::string("2")));
		infos.push_back(std::move(info));
	}

	auto instance(CARSDK::DataModelingModule::instance());

	auto model(instance->normalize(infos));
	XSDNormalizer::XSDNormalizer normalizer1(model);
	if (normalizer1.normalize())
	{
		normalizer1.getDocument().toFile(SSUtils::File::InitailPath() + "\\testModeling1.xsd", SSUtils::CharType::UTF8);
		std::cout << "normalize model1 well." << std::endl;
	}
	else
	{
		std::cout << "normalize model1 fail." << std::endl;
	}

	infos.clear();

	{
		CARSDK::DataModelingModule::Info info;
		info.name.assign("温度");
		info.type.assign("xs:decimal");
		info.experimentalFactorType.assign(CARSDK::ExperimentalFactorType2String().left.find(CARSDK::ExperimentalFactorType::ExperimentalFactor)->second);
		info.validators.insert(std::make_pair(XSDFrontend::Token::EnumValidatorTag(), boost::any(std::vector<SSUtils::Math::Real>({ 15.f, 70.f, 125.f }))));
		info.attributes.insert(std::make_pair(std::string("unit"), std::string("°F")));
		info.attributes.insert(std::make_pair(std::string("digits"), std::string("2")));
		infos.push_back(std::move(info));
	}

	{
		CARSDK::DataModelingModule::Info info;
		info.name.assign("电池有效寿命");
		info.type.assign("xs:decimal");
		info.experimentalFactorType.assign(CARSDK::ExperimentalFactorType2String().left.find(CARSDK::ExperimentalFactorType::EvaluateFactor)->second);
		info.attributes.insert(std::make_pair(std::string("unit"), std::string("h")));
		info.attributes.insert(std::make_pair(std::string("digits"), std::string("2")));
		infos.push_back(std::move(info));
	}

	model = instance->normalize(infos, model);
	XSDNormalizer::XSDNormalizer normalizer2(model);
	if (normalizer2.normalize())
	{
		normalizer2.getDocument().toFile(SSUtils::File::InitailPath() + "\\testModeling2.xsd", SSUtils::CharType::UTF8);
		std::cout << "normalize model2 well." << std::endl;
	}
	else
	{
		std::cout << "normalize model2 fail." << std::endl;
	}

	auto _infos = instance->analyze(model);
	std::cout << "analyze model well." << std::endl;
}
