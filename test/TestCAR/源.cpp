#include "CARSDK/ExperimentalDesignMethodModule.h"
#include "CARSDK/ExperimentalAnalyzerModule.h"

#include "SSUtils/FileUtils.h"
#include "SSUtils/XSD/XSDNormalizer.h"
#include <iostream>

void testSharedLibrary(void);
void testModeling(void);

int main(void)
{
	// testSharedLibrary();
	testModeling();

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
			std::cout << '\t' << _pair.first << ' ' << _pair.second->displayName() << std::endl;
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

	{
		CARSDK::DataModelingModule::Info info;
		info.name.assign("电池有效寿命");
		info.type.assign("xs:decimal");
		info.experimentalFactorType.assign(CARSDK::ExperimentalFactorType2String().left.find(CARSDK::ExperimentalFactorType::EvaluateFactor)->second);
		info.attributes.insert(std::make_pair(std::string("unit"), std::string("h")));
		info.attributes.insert(std::make_pair(std::string("digits"), std::string("2")));
		infos.push_back(std::move(info));
	}

	auto instance(CARSDK::DataModelingModule::instance());
	auto model(instance->normalize(infos));
	XSDNormalizer::XSDNormalizer normalizer(model);
	if (normalizer.normalize())
	{
		normalizer.getDocument().toFile(SSUtils::File::InitailPath() + "\\testModeling.xsd", SSUtils::CharType::UTF8);
		std::cout << "normalize model well." << std::endl;
	}
	else
	{
		std::cout << "normalize model fail." << std::endl;
	}
}
