#include "stdafx.h"
#include "DataHandlingModule.h"
#include "DataModelingModule.h"
#include "SSUtils/XSD/XSDAnalyzer.h"

namespace CARSDK
{
	std::shared_ptr<DataHandlingModule> DataHandlingModule::instance(void)
	{
		static std::shared_ptr<DataHandlingModule> ret(new DataHandlingModule());
		return ret;
	}

	std::shared_ptr<SSUtils::XML::Node> DataHandlingModule::normalize(const ExperimentalDesignTable & table) const
	{
		return table.toXML();
	}

	ExperimentalDesignTable DataHandlingModule::analyze(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data) const
	{
		return std::move(_analyze(model, data));
	}

	const bool DataHandlingModule::check(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data) const
	{
		auto pair = _analyze(model, data);
		return pair.valid(model);
	}

	const bool DataHandlingModule::check(const std::shared_ptr<XSDFrontend::XSDModel> model, const ExperimentalDesignTable & table) const
	{
		return table.valid(model);
	}

	ExperimentalDesignTable DataHandlingModule::_analyze(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data)
	{
		if (data->getTag() != ExperimentalDesignTable::Tag)
		{
			return ExperimentalDesignTable();
		}

		auto modelingModuleInstance(DataModelingModule::instance());
		auto infos(modelingModuleInstance->analyze(model));

		std::set<std::string> factors;
		for (const auto &info : infos)
		{
			factors.insert(info.name);
		}

		return ExperimentalDesignTable::fromXML(data, factors);
	}
};
