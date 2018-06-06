#pragma once

#include "CARSDKGlobal.h"
#include "ExperimentalAnalyzerInterface.h"

#include <boost/shared_ptr.hpp>

namespace CARSDK
{
	class CARSDK_API_DECLSPEC IExperimentalAnalyzerUtilsInterface abstract
	{
	public:
		IExperimentalAnalyzerUtilsInterface(void) = default;
		IExperimentalAnalyzerUtilsInterface(const IExperimentalAnalyzerUtilsInterface &ano) = delete;
		IExperimentalAnalyzerUtilsInterface(IExperimentalAnalyzerUtilsInterface &&ano) = delete;
		IExperimentalAnalyzerUtilsInterface &operator=(const IExperimentalAnalyzerUtilsInterface &rhs) = delete;
		IExperimentalAnalyzerUtilsInterface &operator=(IExperimentalAnalyzerUtilsInterface &&rhs) = delete;
		virtual ~IExperimentalAnalyzerUtilsInterface(void) = default;

		virtual const std::string &name(void) const = 0;
		virtual const std::string &displayName(void) const = 0;
		inline boost::shared_ptr<IExperimentalAnalyzerInterface> analyzerGroup(const std::string &category) const { auto it(analyzerGroups().find(category)); return it == analyzerGroups().cend() ? nullptr : it->second; }
		virtual const std::map<std::string, boost::shared_ptr<IExperimentalAnalyzerInterface>> &analyzerGroups(void) const = 0;

	protected:
		static inline std::pair<std::string, boost::shared_ptr<IExperimentalAnalyzerInterface>> make_analyzers(boost::shared_ptr<IExperimentalAnalyzerInterface> analyzers)
		{
			return std::make_pair(analyzers->category(), analyzers);
		}
	};
};
