#include "stdafx.h"
#include "ExperimentalDesignMethodInterface.h"

namespace CARSDK
{
	const std::map<std::string, std::string> IExperimentalDesignMethodInterface::DefaultFactorAttributes =
	{
		std::make_pair(UnitAttr(), std::string("��λ")),
		std::make_pair(DigitAttr(), std::string("С�����λ��"))
	};

	ExperimentalDesignTable::Cell IExperimentalDesignMethodInterface::generateCell(const FactorType & info, const std::string & value)
	{
		ExperimentalDesignTable::Cell cell;
		cell.content.assign(value);

		auto it(info.attributes.find(UnitAttr()));
		if (it != info.attributes.end())
		{
			cell.attrs.insert(*it);
		}
		return cell;
	}
};
