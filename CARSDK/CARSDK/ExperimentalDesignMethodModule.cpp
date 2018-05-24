#include "stdafx.h"
#include "ExperimentalAnalyzerModule.h"
#include "ExperimentalDesignMethodModule.h"
#include "SSUtils\FileUtils.h"

#include <boost/dll.hpp>
#include <boost/function.hpp>

namespace CARSDK
{
	std::shared_ptr<ExperimentalDesignMethodModule> ExperimentalDesignMethodModule::instance(void)
	{
		static std::shared_ptr<ExperimentalDesignMethodModule> ret(new ExperimentalDesignMethodModule());
		return ret;
	}

	std::shared_ptr<ExperimentalDesignMethodModule> ExperimentalDesignMethodModule::instance(const std::string & path)
	{
		static std::shared_ptr<ExperimentalDesignMethodModule> ret(instance());
		ret->loadUtils(path);
		return ret;
	}

	const bool ExperimentalDesignMethodModule::hasLoaded(const std::string & url) const
	{
		return m_urls.find(url) != m_urls.cend();
	}

	const IExperimentalDesignMethodUtilsInterface * ExperimentalDesignMethodModule::util(const std::string & name) const
	{
		auto it(m_utils.find(name));
		return it == m_utils.cend() ? nullptr : it->second;
	}

	void ExperimentalDesignMethodModule::loadUtils(const std::string & path)
	{
		auto urls(SSUtils::File::getAllFilesUrlsOfPath(path));
		for (const auto &url : urls)
		{
			if (SSUtils::File::getFileExtensionOfUrl(url) == SSUtils::File::SharedLibraryExtension()
				&& !hasLoaded(url))
			{
				loadUtil(url);
			}
		}
	}

	void ExperimentalDesignMethodModule::loadUtil(const std::string & url)
	{
		boost::dll::shared_library lib(url);
		if (lib.has(EDMUtilsFactoryMethodName))
		{
			boost::function<const IExperimentalDesignMethodUtilsInterface *()> factoryMethod(lib.get_alias<const IExperimentalDesignMethodUtilsInterface *()>(EDMUtilsFactoryMethodName));
			auto *util = factoryMethod();
			m_urls.insert(url);
			m_utils.insert(std::make_pair(util->name(), util));
		}
	}
};
