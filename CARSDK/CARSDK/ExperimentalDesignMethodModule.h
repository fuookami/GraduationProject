#pragma once

#include "CARSDKGlobal.h"
#include "ExperimentalDesignMethodUtilsInterface.h"
#include "UtilsHandler.h"

namespace CARSDK
{
	class CARSDK_API_DECLSPEC ExperimentalDesignMethodModule
	{
	public:
		static std::shared_ptr<ExperimentalDesignMethodModule> instance(void);
		static std::shared_ptr<ExperimentalDesignMethodModule> instance(const std::string &path);

	private:
		ExperimentalDesignMethodModule(void);
	public:
		ExperimentalDesignMethodModule(const ExperimentalDesignMethodModule &ano) = delete;
		ExperimentalDesignMethodModule(ExperimentalDesignMethodModule &&ano) = delete;
		ExperimentalDesignMethodModule &operator=(const ExperimentalDesignMethodModule &rhs) = delete;
		ExperimentalDesignMethodModule &operator=(ExperimentalDesignMethodModule &&rhs) = delete;
		~ExperimentalDesignMethodModule(void) = default;

		inline std::shared_ptr<UtilsHandler> utilsHandler(void) const { return m_utilsHandlers; }
		boost::shared_ptr<IExperimentalDesignMethodUtilsInterface> util(const std::string &name) const;
		inline const std::map<std::string, boost::shared_ptr<IExperimentalDesignMethodUtilsInterface>> &utils(void) const { return m_utils; }

		void refreshUtils(void);
		void refreshUtils(const std::string &path);

	private:
		std::shared_ptr<UtilsHandler> m_utilsHandlers;
		std::map<std::string, boost::shared_ptr<IExperimentalDesignMethodUtilsInterface>> m_utils;
	};
};
