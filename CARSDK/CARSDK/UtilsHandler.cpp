#include "stdafx.h"
#include "UtilsHandler.h"
#include "SSUtils\FileUtils.h"
#include "ExperimentalDesignMethodUtilsInterface.h"

#include <boost/function.hpp>

namespace CARSDK
{
	std::shared_ptr<UtilsHandler> UtilsHandler::instance(void)
	{
		static std::shared_ptr<UtilsHandler> ret(new UtilsHandler());
		return ret;
	}

	std::shared_ptr<UtilsHandler> UtilsHandler::instance(const std::string & path)
	{
		static std::shared_ptr<UtilsHandler> ret(instance());
		ret->loadUtils(path);
		return ret;
	}

	const bool UtilsHandler::hasLoaded(const std::string & url) const
	{
		return m_urls.find(url) != m_urls.cend();
	}

	std::shared_ptr<boost::dll::shared_library> UtilsHandler::lib(const std::string & url) const
	{
		auto it(m_libs.find(url));
		return it == m_libs.cend() ? nullptr : it->second;
	}

	void UtilsHandler::loadUtils(const std::string & path)
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

	void UtilsHandler::loadUtil(const std::string & url)
	{
		std::shared_ptr<boost::dll::shared_library> lib(new boost::dll::shared_library(url));
		if (lib->has(EDMUtilsFactoryMethodName) && lib->has(EAUtilsFactoryMethodName))
		{
			boost::function<boost::shared_ptr<IExperimentalDesignMethodUtilsInterface>()> factoryMethod(lib->get_alias<boost::shared_ptr<IExperimentalDesignMethodUtilsInterface>()>(EDMUtilsFactoryMethodName));
			auto util = factoryMethod();

			m_urls.insert(url);
			m_libs.insert(std::make_pair(util->name(), lib));
		}
	}
};
