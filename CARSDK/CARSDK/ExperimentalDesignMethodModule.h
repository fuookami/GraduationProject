#pragma once

#include "CARSDKGlobal.h"
#include "ExperimentalDesignMethodUtilsInterface.h"

#include <set>
#include <boost/dll.hpp>

namespace CARSDK
{
	class CARSDK_API_DECLSPEC ExperimentalDesignMethodModule
	{
	public:
		static std::shared_ptr<ExperimentalDesignMethodModule> instance(void);
		static std::shared_ptr<ExperimentalDesignMethodModule> instance(const std::string &path);

	private:
		ExperimentalDesignMethodModule(void) = default;
	public:
		ExperimentalDesignMethodModule(const ExperimentalDesignMethodModule &ano) = delete;
		ExperimentalDesignMethodModule(ExperimentalDesignMethodModule &&ano) = delete;
		ExperimentalDesignMethodModule &operator=(const ExperimentalDesignMethodModule &rhs) = delete;
		ExperimentalDesignMethodModule &operator=(ExperimentalDesignMethodModule &&rhs) = delete;
		~ExperimentalDesignMethodModule(void) = default;

		const bool hasLoaded(const std::string &url) const;
		inline const std::set<std::string> &urls(void) const { return m_urls; }

		boost::shared_ptr<IExperimentalDesignMethodUtilsInterface> util(const std::string &name) const;
		inline const std::map<std::string, boost::shared_ptr<IExperimentalDesignMethodUtilsInterface>> &utils(void) const { return m_utils; }

	private:
		void loadUtils(const std::string &path);
		void loadUtil(const std::string &url);

	private:
		std::set<std::string> m_urls;
		std::set<std::shared_ptr<boost::dll::shared_library>> m_libs;
		std::map<std::string, boost::shared_ptr<IExperimentalDesignMethodUtilsInterface>> m_utils;
	};
};
