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

	ExperimentalDesignTable DataHandlingModule::analyze(const std::shared_ptr<SSUtils::XML::Node> data) const
	{
		return std::move(_analyze(data).second);
	}

	const bool DataHandlingModule::check(const std::shared_ptr<SSUtils::XML::Node> data) const
	{
		auto pair = _analyze(data);
		return pair.second.valid(pair.first);
	}

	const bool DataHandlingModule::check(const std::shared_ptr<XSDFrontend::XSDModel> model, const ExperimentalDesignTable & table) const
	{
		return table.valid(model);
	}

	std::pair<std::shared_ptr<XSDFrontend::XSDModel>, ExperimentalDesignTable> DataHandlingModule::_analyze(const std::shared_ptr<SSUtils::XML::Node> data)
	{
		if (data->getChildren().size() != 2
			|| data->getChildren()[0]->getTag() != XSDFrontend::Token::SchemaTag()
			|| data->getChildren()[1]->getTag() != ExperimentalDesignTable::Tag)
		{
			return std::make_pair(nullptr, ExperimentalDesignTable());
		}

		auto modelNode(data->getChildren()[0]), tableNode(data->getChildren()[1]);
		std::set<std::string> factors;

		XSDAnalyzer::XSDAnalyzer analyzer;
		if (!analyzer.scan(modelNode))
		{
			return std::make_pair(nullptr, ExperimentalDesignTable());
		}

		auto model(analyzer.getModel());
		auto modelingModuleInstance(DataModelingModule::instance());
		auto infos(modelingModuleInstance->analyze(model));

		for (const auto &info : infos)
		{
			factors.insert(info.name);
		}

		return std::make_pair(model, ExperimentalDesignTable::fromXML(tableNode, factors));

		return std::pair<std::shared_ptr<XSDFrontend::XSDModel>, ExperimentalDesignTable>();
	}
};
