#pragma once

#include <functional>
#include <memory>
#include <boost/bimap.hpp>

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
#define String_Declaration(name) CARSDK_API_DECLSPEC const std::string &##name##(void);\

	extern const std::string EDMUtilsFactoryMethodName;
	extern const std::string EAUtilsFactoryMethodName;
	String_Declaration(UnitAttr);
	String_Declaration(DigitAttr);

	enum class ExperimentalFactorType
	{
		ExperimentalFactor,
		EvaluateFactor,
		NotEvaluateFactor
	};
	String_Declaration(ExperimentalFactorTypeAttr);
	CARSDK_API_DECLSPEC const boost::bimap<ExperimentalFactorType, std::string> &ExperimentalFactorType2String(void);
	CARSDK_API_DECLSPEC const boost::bimap<ExperimentalFactorType, std::string> &ExperimentalFactorType2Display(void);

	enum class AnalysisResultType
	{
		Raw,
		Table,
		Html5,
		None
	};

	enum class AttributeType
	{
		Boolean,
		Number,
		String
	};

	class UtilsHandler;
	class ExperimentalDesignTable;

	class DataModelingModule;
	class DataHandlingModule;

	class IExperimentalDesignMethodInterface;
	class IExperimentalDesignMethodUtilsInterface;
	class ExperimentalDesignMethodModule;

	class IExperimentalAnalyzerInterface;
	class IExperimentalAnalyzerUtilsInterface;
	class ExperimentalAnalyzerModule;

#undef String_Declaration
};
