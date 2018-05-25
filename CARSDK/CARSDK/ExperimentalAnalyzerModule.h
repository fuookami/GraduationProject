#pragma once

#include "CARSDKGlobal.h"
#include "ExperimentalAnalyzerUtilsInterface.h"
#include "UtilsHandler.h"

namespace CARSDK
{
	class CARSDK_API_DECLSPEC ExperimentalAnalyzerModule
	{
	public:
		static std::shared_ptr<ExperimentalAnalyzerModule> instance(void);
		static std::shared_ptr<ExperimentalAnalyzerModule> instance(const std::string &path);
		
	private:
		ExperimentalAnalyzerModule(void);
	public:
		ExperimentalAnalyzerModule(const ExperimentalAnalyzerModule &ano) = delete;
		ExperimentalAnalyzerModule(ExperimentalAnalyzerModule &&ano) = delete;
		ExperimentalAnalyzerModule &operator=(const ExperimentalAnalyzerModule &rhs) = delete;
		ExperimentalAnalyzerModule &operator=(ExperimentalAnalyzerModule &&rhs) = delete;
		~ExperimentalAnalyzerModule(void) = default;

		inline std::shared_ptr<UtilsHandler> utilsHandler(void) const { return m_utilsHandlers; }
		boost::shared_ptr<IExperimentalAnalyzerUtilsInterface> util(const std::string &name) const;
		inline const std::map<std::string, boost::shared_ptr<IExperimentalAnalyzerUtilsInterface>> &utils(void) const { return m_utils; }

	private:
		void refreshUtils(void);
		void refreshUtils(const std::string &path);

	private:
		std::shared_ptr<UtilsHandler> m_utilsHandlers;
		std::map<std::string, boost::shared_ptr<IExperimentalAnalyzerUtilsInterface>> m_utils;
	};
};
