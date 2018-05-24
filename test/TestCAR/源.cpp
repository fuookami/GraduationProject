#include "CARSDK/ExperimentalDesignMethodModule.h"

#include "SSUtils/FileUtils.h"
#include <iostream>

int main(void)
{
	auto EDMMod(CARSDK::ExperimentalDesignMethodModule::instance(std::string("D:\\project\\GraduationProject\\GraduationProject\\x64\\Debug\\plugins")));
	std::cout << EDMMod->utils().size() << std::endl;
	for (const auto &pair : EDMMod->utils())
	{
		try
		{
			std::cout << pair.first << ' ' << pair.second->displayName() << std::endl;
			for (const auto &pair : pair.second->methods())
			{
				std::cout << '\t' << pair.first << ' ' << pair.second->displayName() << std::endl;
			}
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	system("pause");
	return 0;
}
