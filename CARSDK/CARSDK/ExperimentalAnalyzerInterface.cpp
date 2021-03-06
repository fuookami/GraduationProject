#include "stdafx.h"
#include "ExperimentalAnalyzerInterface.h"

#include <sstream>

namespace CARSDK
{
	IExperimentalAnalyzerInterface::Analyzer::result_type IExperimentalAnalyzerInterface::AnalyzerGroup::analyze(const FactorTypeGroup &group, const ExperimentalDesignTable &table, const std::map<std::string, std::string> &attributes, const std::string &flag) const
	{
		auto it(analyzers.find(flag));
		return it == analyzers.cend()
			? std::make_pair(AnalysisResultType::None, generateNotFoundMessage(flag))
			: it->second(group, table, attributes);
	}

	std::string IExperimentalAnalyzerInterface::AnalyzerGroup::generateNotFoundMessage(const std::string & str) const
	{
		const auto &nameMap(flags);
		auto nameIt(nameMap.find(str));
		if (nameIt == nameMap.cend())
		{
			std::ostringstream sout;
			sout << "未定义的分析方法：" << str;
			return sout.str();
		}
		auto analyzerMap(analyzers);
		auto analyzerIt(analyzerMap.find(str));
		if (analyzerIt == analyzerMap.cend())
		{
			std::ostringstream sout;
			sout << "未实现的分析方法：" << nameIt->second << '(' << str << ')';
			return sout.str();
		}
		return SSUtils::String::EmptyString();
	}
};
