#include "stdafx.h"
#include "ExperimentalDesignTable.h"

namespace CARSDK
{
	ExperimentalDesignTable::ExperimentalDesignTable(const std::shared_ptr<SSUtils::XML::Node> node)
		: ExperimentalDesignTable(fromXML(node))
	{
	}

	ExperimentalDesignTable ExperimentalDesignTable::fromXML(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		return ExperimentalDesignTable();
	}

	std::shared_ptr<SSUtils::XML::Node> ExperimentalDesignTable::toXML(void) const
	{
		return std::shared_ptr<SSUtils::XML::Node>();
	}
};
