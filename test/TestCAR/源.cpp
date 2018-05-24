#include "CARSDK/ExperimentalDesignMethodModule.h"

#include "SSUtils/FileUtils.h"
#include <iostream>

int main(void)
{
	auto EDMMod(CARSDK::ExperimentalDesignMethodModule::instance(std::string("D:\\project\\GraduationProject\\GraduationProject\\x64\\Debug\\plugins")));
	std::cout << EDMMod->utils().size() << std::endl;
	system("pause");
	return 0;
}