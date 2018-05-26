#include "stdafx.h"
#include "DataHandlingModule.h"

namespace CARSDK
{
	std::shared_ptr<DataHandlingModule> DataHandlingModule::instance(void)
	{
		static std::shared_ptr<DataHandlingModule> ret(new DataHandlingModule());
		return ret;
	}

	std::shared_ptr<SSUtils::XML::Node> DataHandlingModule::normalize(const ExperimentalDesignTable & table) const
	{
		return std::shared_ptr<SSUtils::XML::Node>();
	}

	ExperimentalDesignTable DataHandlingModule::analyze(const std::shared_ptr<SSUtils::XML::Node> data) const
	{
		return ExperimentalDesignTable();
	}

	const bool DataHandlingModule::check(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data) const
	{
		return false;
	}

	const bool DataHandlingModule::check(const std::shared_ptr<XSDFrontend::XSDModel> mode, const ExperimentalDesignTable & table) const
	{
		return false;
	}
};
