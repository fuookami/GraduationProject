#include "CARSDK/ExperimentalDesignMethodModule.h"
#include "CARSDK/ExperimentalAnalyzerModule.h"

#include "SSUtils/FileUtils.h"
#include <iostream>

int main(void)
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
	system("pause");
	return 0;
}
