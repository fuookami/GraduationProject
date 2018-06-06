#include "stdafx.h"
#include "TwoFactorsAEDM.h"
#include "SSUtils\MathUtils.h"

namespace AEDM
{
	const std::string TwoFactorsAEDM::Category("TwoFactorAEDM");
	const std::string TwoFactorsAEDM::DisplayName("二因子析因设计方法");
	const std::string TwoFactorsAEDM::RepeatTimeAttr("repeat_time");
	const std::string TwoFactorsAEDM::InteractionEffectAttr("has_interaction_effect");

	boost::shared_ptr<TwoFactorsAEDM> TwoFactorsAEDM::create(void)
	{
		return boost::shared_ptr<TwoFactorsAEDM>(new TwoFactorsAEDM());
	}

	const std::string &TwoFactorsAEDM::category(void) const
	{
		return Category;
	}

	const std::string &TwoFactorsAEDM::displayName(void) const
	{
		return DisplayName;
	}

	const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> &TwoFactorsAEDM::neededAttributes(void) const
	{
		static const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> ret = 
		{
			std::make_pair(InteractionEffectAttr, std::make_pair(std::string("交互作用"), CARSDK::AttributeType::Boolean)),
			std::make_pair(RepeatTimeAttr, std::make_pair(std::string("重复次数"), CARSDK::AttributeType::Number))
		};
		return ret;
	}

	const std::map<std::string, std::string>& TwoFactorsAEDM::factorNeededAttributes(void) const
	{
		static const std::map<std::string, std::string> ret = DefaultFactorAttributes;
		return ret;
	}

	const bool TwoFactorsAEDM::valid(const std::map<std::string, std::string>& attributes)
	{
		if (!SSUtils::String::isPositiveDecInteger(attributes.find(RepeatTimeAttr)->second))
		{
			m_lastError.assign("重复次数不是一个有效的十进制正整数");
			return false;
		}

		return true;
	}

	const bool TwoFactorsAEDM::valid(const std::map<std::string, std::string>& attributes, const CARSDK::FactorTypeGroup & factorTypeGroup)
	{
		if (!valid(attributes))
		{
			return false;
		}

		if (factorTypeGroup.experimentalFactors.size() != 2)
		{
			m_lastError.assign("实验因素类型的数量不为2");
			return false;
		}

		std::vector<std::string> NoEnumFactors;
		for (const auto &factorWrapper : factorTypeGroup.experimentalFactors)
		{
			const auto &factor = factorWrapper.get();
			if (CARSDK::DataModelingModule::getEnumNumber(factor) <= 0)
			{
				NoEnumFactors.push_back(factor.name);
			}
		}
		if (!NoEnumFactors.empty())
		{
			std::ostringstream sout;
			sout << "实验因素" << SSUtils::String::join(NoEnumFactors, std::string("，")) << "没有水平值";
			m_lastError.assign(sout.str());
			return false;
		}

		return true;
	}

	CARSDK::ExperimentalDesignTable TwoFactorsAEDM::generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel>& xsdModel, const std::map<std::string, std::string>& attributes)
	{
		auto modelingModule(CARSDK::DataModelingModule::instance());
		auto infos(modelingModule->analyzeForData(xsdModel));
		auto group(CARSDK::DataModelingModule::divideToGroup(infos));

		if (!valid(attributes, group))
		{
			return CARSDK::ExperimentalDesignTable();
		}
		
		CARSDK::ExperimentalDesignTable table;
		auto factorInserter = [&table](const decltype(group.experimentalFactors) &factorWrappers) 
		{
			for (const auto factorWrapper : factorWrappers)
			{
				table.typeNames().push_back(factorWrapper.get().name);
			}
		};
		factorInserter(group.experimentalFactors);
		factorInserter(group.evaluateFactor);
		factorInserter(group.notEvaluateFactor);
		for (const auto factorWrapper : group.experimentalFactors)
		{
			table.readOnlyTypeNames().insert(factorWrapper.get().name);
		}

		SSUtils::uint32 repeatTime = std::stoul(attributes.find(RepeatTimeAttr)->second);

		std::vector<std::vector<std::string>> enumStrings;
		std::vector<SSUtils::int32> numbers;
		for (const auto &factor : group.experimentalFactors)
		{
			enumStrings.push_back(CARSDK::DataModelingModule::getEnumString(factor));
			numbers.push_back(enumStrings.back().size());
		}
		
		SSUtils::Math::CombinationGenerator combinationGenerator(numbers);
		do 
		{
			CARSDK::ExperimentalDesignTable::Batch batch;
			const auto &combination(combinationGenerator.currCombination);
			for (SSUtils::uint32 i(0), j(combination.size()); i != j; ++i)
			{
				batch.push_back(generateCell(group.experimentalFactors[i], enumStrings[i][combination[i]]));
			}
			for (SSUtils::uint32 i(0), j(group.evaluateFactor.size()); i != j; ++i)
			{
				batch.push_back(generateCell(group.evaluateFactor[i]));
			}
			for (SSUtils::uint32 i(0), j(group.notEvaluateFactor.size()); i != j; ++i)
			{
				batch.push_back(generateCell(group.notEvaluateFactor[i]));
			}

			table.batches().insert(table.batches().end(), repeatTime, batch);
		} while (combinationGenerator.next());

		std::random_shuffle(table.batches().begin(), table.batches().end());
		return table;
	}

	CARSDK::ExperimentalDesignTable::Cell TwoFactorsAEDM::generateCell(const CARSDK::FactorType & info, const std::string & value)
	{
		return IExperimentalDesignMethodInterface::generateCell(info, value);
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::OriginAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "evaluate_" << evaluateFactorOrder << "_origin";
		displaySout << "原始（" << group.evaluateFactor[evaluateFactorOrder].get().name << "）";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(originAnalyse, std::placeholders::_1, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::VarianceOriginAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "evaluate_" << evaluateFactorOrder << "_variance_origin";
		displaySout << "方差法原始（" << group.evaluateFactor[evaluateFactorOrder].get().name << "）";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(varianceOriginAnalyse, std::placeholders::_1, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::FactorSumAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "factor_" << experimentalFactorOrder << "_evaluate_" << evaluateFactorOrder << "_sum";
		displaySout << group.experimentalFactors[experimentalFactorOrder].get().name << "-" << group.evaluateFactor[evaluateFactorOrder].get().name << "和值";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(factorSumAnalyse, std::placeholders::_1, experimentalFactorOrder, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::FactorAverageAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "factor_" << experimentalFactorOrder << "_evaluate_" << evaluateFactorOrder << "_average";
		displaySout << group.experimentalFactors[experimentalFactorOrder].get().name << "-" << group.evaluateFactor[evaluateFactorOrder].get().name << "平均值";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(factorAverageAnalyse, std::placeholders::_1, experimentalFactorOrder, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::Factor1Factor2SumAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "evaluate_" << evaluateFactorOrder << "_sum";
		displaySout << "(" << group.experimentalFactors[0].get().name << ", " << group.experimentalFactors[1].get().name << ")-" << group.evaluateFactor[evaluateFactorOrder].get().name << "和值";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(factor1Factor2SumAnalyse, std::placeholders::_1, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::Factor1Factor2AverageAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "evaluate_" << evaluateFactorOrder << "_average";
		displaySout << "(" << group.experimentalFactors[0].get().name << ", " << group.experimentalFactors[1].get().name << ")-" << group.evaluateFactor[evaluateFactorOrder].get().name << "平均值";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(factor1Factor2AverageAnalyse, std::placeholders::_1, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	boost::shared_ptr<TwoFactorsAEDMAnalyzers> TwoFactorsAEDMAnalyzers::create(void)
	{
		return boost::shared_ptr<TwoFactorsAEDMAnalyzers>(new TwoFactorsAEDMAnalyzers());
	}

	const std::string & TwoFactorsAEDMAnalyzers::category(void) const
	{
		return TwoFactorsAEDM::Category;
	}

	const std::string & TwoFactorsAEDMAnalyzers::displayName(void) const
	{
		return TwoFactorsAEDM::DisplayName;
	}

	TwoFactorsAEDMAnalyzers::AnalyzerGroup TwoFactorsAEDMAnalyzers::generateAnalyzerGroup(const CARSDK::FactorTypeGroup &group) const
	{
		AnalyzerGroup ret;
		const auto AddAnalyzer([&ret](const std::tuple<std::string, std::string, Analyzer> &tuple) 
		{
			ret.flags.insert(std::make_pair(std::get<0>(tuple), std::get<1>(tuple)));
			ret.analyzers.insert(std::make_pair(std::get<0>(tuple), std::get<2>(tuple)));
		});

		for (SSUtils::uint32 i(0), j(group.evaluateFactor.size()); i != j; ++i)
		{
			AddAnalyzer(OriginAnalyzer(group, i));
			AddAnalyzer(VarianceOriginAnalyzer(group, i));
			AddAnalyzer(FactorSumAnalyzer(group, 0, i));
			AddAnalyzer(FactorSumAnalyzer(group, 1, i));
			AddAnalyzer(FactorAverageAnalyzer(group, 0, i));
			AddAnalyzer(FactorAverageAnalyzer(group, 1, i));
			AddAnalyzer(Factor1Factor2SumAnalyzer(group, i));
			AddAnalyzer(Factor1Factor2AverageAnalyzer(group, i));
		}

		return ret;
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::originAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		// to do

		return std::make_pair(CARSDK::AnalysisResultType::Raw, std::string("未实现"));
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::varianceOriginAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		// to do

		return std::make_pair(CARSDK::AnalysisResultType::Raw, std::string("未实现"));
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::factorSumAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		// to do

		return std::make_pair(CARSDK::AnalysisResultType::Raw, std::string("未实现"));
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::factorAverageAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		// to do

		return std::make_pair(CARSDK::AnalysisResultType::Raw, std::string("未实现"));
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::factor1Factor2SumAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		// to do

		return std::make_pair(CARSDK::AnalysisResultType::Raw, std::string("未实现"));
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::factor1Factor2AverageAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		// to do

		return std::make_pair(CARSDK::AnalysisResultType::Raw, std::string("未实现"));
	}
};
