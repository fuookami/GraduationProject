#pragma once

#include <functional>
#include <memory>

#ifdef _EXPORTING_CARSDK
#define CARSDK_API_DECLSPEC __declspec(dllexport)
#else
#define CARSDK_API_DECLSPEC __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib, "ComputerAidedResearchDevelopmentKitd.lib")
#else
#pragma comment(lib, "ComputerAidedResearchDevelopmentKit.lib")
#endif
#endif

namespace CARSDK
{
	class ExperimentalDesignTable;

	class DataModelingModule;
	class DataHandlingModule;

	class IExperimentalDesignMethodInterface;
	class IExperimentalDesignMethodUtilsInterface;
	class ExperimentalDesignMethodModule;

	using EDMUtilsFactoryMethod = std::function<IExperimentalDesignMethodUtilsInterface *(void)>;
	extern const std::string EDMUtilsFactoryMethodName;

	class IExperimentalAnalyzerInterface;
	class IExperimentalAnalyzerUtilsInterface;
	class ExperimentalAnalyzerModule;

	using EAUtilsFactoryMethod = std::function<IExperimentalAnalyzerUtilsInterface *(void)>;
	extern const std::string EAUtilsFactoryMethodName;

	enum class ExperimentalFactorType
	{
		ExperimentalFactor,
		EvaluateFactors,
		NotEvaluateFactors
	};

	enum class AnalysisResultType
	{
		Raw,
		Table,
		Html5,
		None
	};
};
