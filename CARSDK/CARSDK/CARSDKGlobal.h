#pragma once

#include "SSUtils/XSD/XSDModel.h"
#include <vector>
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
	CARSDK_API_DECLSPEC const boost::bimap<AnalysisResultType, std::string> &AnalysisResultType2String(void);

	enum class AttributeType
	{
		Boolean,
		Number,
		String
	};
	CARSDK_API_DECLSPEC const boost::bimap<AttributeType, std::string> &AttributeType2String(void);

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

	struct CARSDK_API_DECLSPEC FactorType
	{
		std::string name;
		std::string type;
		std::string experimentalFactorType;
		XSDFrontend::SimpleType::eSimpleType simpleType;
		std::map<std::string, std::string> infos;
		std::map<std::string, boost::any> validators;
		std::map<std::string, std::string> attributes;
	};
	struct CARSDK_API_DECLSPEC FactorTypeGroup
	{
		std::vector<std::reference_wrapper<const FactorType>> experimentalFactors;
		std::vector<std::reference_wrapper<const FactorType>> evaluateFactor;
		std::vector<std::reference_wrapper<const FactorType>> notEvaluateFactor;

		std::reference_wrapper<const FactorType> getFactorType(const std::string &name) const;
		std::vector<std::reference_wrapper<const FactorType>> factors(void) const;
		inline const bool empty(void) const { return experimentalFactors.empty() && evaluateFactor.empty() && notEvaluateFactor.empty(); }
	};

#undef String_Declaration
};
