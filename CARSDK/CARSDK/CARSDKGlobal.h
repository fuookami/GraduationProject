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
	class DataModelingModule;
	class DataHandlingModule;

	class ExperimentalDesignTable;
	class IExperimentalDesignMethodInterface;
	class IExperimentalDesignMethodUtilsInterface;
	class ExperimentalDesignMethodModule;

	using EDMUtilsFactoryMethod = std::function<EDMUtilsFactoryMethod *(void)>;
	extern const std::string EDMUtilsFactoryMethodName;

	class IExperimentalAnalyzerInterface;
	class IExperimentalAnalyzerUtilsInterface;
	class ExperimentalAnalyzerModule;

	using EAUtilsFactorMethod = std::function<EAUtilsFactorMethod *(void)>;
	extern const std::string EAUtilsFactorMethodName;

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
