#pragma once

#include "CARSDKGlobal.h"
#include "DataHandlingModule.h"

namespace CARSDK
{
	class CARSDK_API_DECLSPEC IExperimentalAnalyzerInterface abstract
	{
	public:
		using Analyzer = std::function<std::pair<AnalysisResultType, std::string>(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data, const std::map<std::string, std::string> &attributes, const std::string &flag)>;

	public:
		IExperimentalAnalyzerInterface(void) = default;
		IExperimentalAnalyzerInterface(const IExperimentalAnalyzerInterface &ano) = delete;
		IExperimentalAnalyzerInterface(IExperimentalAnalyzerInterface &&ano) = delete;
		IExperimentalAnalyzerInterface &operator=(const IExperimentalAnalyzerInterface &rhs) = delete;
		IExperimentalAnalyzerInterface &operator=(IExperimentalAnalyzerInterface &&rhs) = delete;
		virtual ~IExperimentalAnalyzerInterface(void) = default;

		virtual const std::string &category(void) const = 0;
		virtual const std::map<std::string, std::string> &flags(void) const = 0;
		virtual const std::map<std::string, Analyzer> &analyzers(void) const = 0;
		Analyzer::result_type analyze(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data, const std::map<std::string, std::string> &attributes, const std::string &flag) const;

	protected:
		std::string generateNotFoundMessage(const std::string &str) const;
	};
};