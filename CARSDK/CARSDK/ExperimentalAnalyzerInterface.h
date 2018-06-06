#pragma once

#include "CARSDKGlobal.h"
#include "DataHandlingModule.h"
#include "ExperimentalDesignMethodInterface.h"
#include "ExperimentalDesignTable.h"

namespace CARSDK
{
	class CARSDK_API_DECLSPEC IExperimentalAnalyzerInterface abstract
	{
	public:
		using Analyzer = std::function<std::pair<AnalysisResultType, std::string>(const FactorTypeGroup &group, const ExperimentalDesignTable &table, const std::map<std::string, std::string> &attributes)>;
		struct CARSDK_API_DECLSPEC AnalyzerGroup
		{
			std::map<std::string, std::string> flags;
			std::map<std::string, Analyzer> analyzers;

			Analyzer::result_type analyze(const FactorTypeGroup &group, const ExperimentalDesignTable &table, const std::map<std::string, std::string> &attributes, const std::string &flag) const;
			std::string generateNotFoundMessage(const std::string &str) const;
		};

	public:
		IExperimentalAnalyzerInterface(void) = default;
		IExperimentalAnalyzerInterface(const IExperimentalAnalyzerInterface &ano) = delete;
		IExperimentalAnalyzerInterface(IExperimentalAnalyzerInterface &&ano) = delete;
		IExperimentalAnalyzerInterface &operator=(const IExperimentalAnalyzerInterface &rhs) = delete;
		IExperimentalAnalyzerInterface &operator=(IExperimentalAnalyzerInterface &&rhs) = delete;
		virtual ~IExperimentalAnalyzerInterface(void) = default;

		virtual const std::string &category(void) const = 0;
		virtual const std::string &displayName(void) const = 0;
		virtual AnalyzerGroup generateAnalyzerGroup(const FactorTypeGroup &group) const = 0;
	};
};
