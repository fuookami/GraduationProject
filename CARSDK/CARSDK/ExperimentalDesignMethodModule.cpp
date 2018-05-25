#include "stdafx.h"
#include "ExperimentalAnalyzerModule.h"
#include "ExperimentalDesignMethodModule.h"

#include <boost/function.hpp>

namespace CARSDK
{
	const std::map<std::string, std::string> ExperimentalDesignMethodModule::DefaultFactorAttributes = 
	{
		std::make_pair(UnitAttr(), std::string("单位")),
		std::make_pair(DigitAttr(), std::string("小数点后位数"))
	};

	std::shared_ptr<ExperimentalDesignMethodModule> ExperimentalDesignMethodModule::instance(void)
	{
		static std::shared_ptr<ExperimentalDesignMethodModule> ret(new ExperimentalDesignMethodModule());
		ret->refreshUtils();
		return ret;
	}

	std::shared_ptr<ExperimentalDesignMethodModule> ExperimentalDesignMethodModule::instance(const std::string & path)
	{
		static std::shared_ptr<ExperimentalDesignMethodModule> ret(instance());
		ret->refreshUtils(path);
		return ret;
	}

	ExperimentalDesignMethodModule::ExperimentalDesignMethodModule(void)
		: m_utilsHandlers(UtilsHandler::instance())
	{
	}

	boost::shared_ptr<IExperimentalDesignMethodUtilsInterface> ExperimentalDesignMethodModule::util(const std::string & name) const
	{
		auto it(m_utils.find(name));
		return it == m_utils.cend() ? nullptr : it->second;
	}

	void ExperimentalDesignMethodModule::refreshUtils(void)
	{
		for (const auto &pair : m_utilsHandlers->libs())
		{
			if (m_utils.find(pair.first) == m_utils.cend())
			{
				boost::function<boost::shared_ptr<IExperimentalDesignMethodUtilsInterface>()> factoryMethod(pair.second->get_alias<boost::shared_ptr<IExperimentalDesignMethodUtilsInterface>()>(EDMUtilsFactoryMethodName));
				m_utils.insert(std::make_pair(pair.first, factoryMethod()));
			}
		}
	}

	void ExperimentalDesignMethodModule::refreshUtils(const std::string & path)
	{
		m_utilsHandlers->loadUtils(path);
		refreshUtils();
	}
};
