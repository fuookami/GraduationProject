#include "stdafx.h"
#include "ExperimentalDesignMethodInterface.h"

namespace CARSDK
{
	const std::map<std::string, std::string> IExperimentalDesignMethodInterface::DefaultFactorAttributes =
	{
		std::make_pair(UnitAttr(), std::string("单位")),
		std::make_pair(DigitAttr(), std::string("小数点后位数"))
	};

	ExperimentalDesignTable::Cell IExperimentalDesignMethodInterface::generateCell(const DataModelingModule::FactorType & info, const std::string & value)
	{
		return ExperimentalDesignTable::Cell();
	}
};
