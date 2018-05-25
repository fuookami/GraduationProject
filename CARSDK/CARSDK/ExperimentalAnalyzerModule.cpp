#include "stdafx.h"
#include "ExperimentalDesignMethodModule.h"
#include "ExperimentalAnalyzerModule.h"

#include <boost/function.hpp>

namespace CARSDK
{
	std::shared_ptr<ExperimentalAnalyzerModule> ExperimentalAnalyzerModule::instance(void)
	{
		static std::shared_ptr<ExperimentalAnalyzerModule> ret(new ExperimentalAnalyzerModule());
		ret->refreshUtils();
		return ret;
	}

	std::shared_ptr<ExperimentalAnalyzerModule> ExperimentalAnalyzerModule::instance(const std::string & path)
	{
		static std::shared_ptr<ExperimentalAnalyzerModule> ret(new ExperimentalAnalyzerModule());
		ret->refreshUtils(path);
		return ret;
	}

	ExperimentalAnalyzerModule::ExperimentalAnalyzerModule(void)
		: m_utilsHandlers(UtilsHandler::instance())
	{
	}

	boost::shared_ptr<IExperimentalAnalyzerUtilsInterface> ExperimentalAnalyzerModule::util(const std::string & name) const
	{
		auto it(m_utils.find(name));
		return it == m_utils.cend() ? nullptr : it->second;
	}

	void ExperimentalAnalyzerModule::refreshUtils(void)
	{
		for (const auto &pair : m_utilsHandlers->libs())
		{
			if (m_utils.find(pair.first) == m_utils.cend())
			{
				boost::function<boost::shared_ptr<IExperimentalAnalyzerUtilsInterface>()> factoryMethod(pair.second->get_alias<boost::shared_ptr<IExperimentalAnalyzerUtilsInterface>()>(EAUtilsFactoryMethodName));
				m_utils.insert(std::make_pair(pair.first, factoryMethod()));
			}
		}
	}

	void ExperimentalAnalyzerModule::refreshUtils(const std::string & path)
	{
		m_utilsHandlers->loadUtils(path);
		refreshUtils();
	}
};
