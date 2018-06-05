#include "stdafx.h"
#include "TwoFactorsAEDM.h"
#include "SSUtils\MathUtils.h"

namespace AEDM
{
	const std::string TwoFactorsAEDM::Category("TwoFactorAEDM");
	const std::string TwoFactorsAEDM::RepeatTimeAttr("repeat_time");
	const std::string TwoFactorsAEDM::InteractionEffectAttr("has_interaction_effect");

	const std::string TwoFactorsAEDMAnalyzers::VarianceOriginFlag("variance_origin");

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
		static const std::string ret("二因子析因设计方法");
		return ret;
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

	const bool TwoFactorsAEDM::valid(const std::map<std::string, std::string>& attributes, const CARSDK::DataModelingModule::FactorTypeGroup & factorTypeGroup)
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
		auto infos(modelingModule->analyzeForDesignMethod(xsdModel));
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

	CARSDK::ExperimentalDesignTable::Cell TwoFactorsAEDM::generateCell(const CARSDK::DataModelingModule::FactorType & info, const std::string & value)
	{
		return IExperimentalDesignMethodInterface::generateCell(info, value);
	}

	boost::shared_ptr<TwoFactorsAEDMAnalyzers> TwoFactorsAEDMAnalyzers::create(void)
	{
		return boost::shared_ptr<TwoFactorsAEDMAnalyzers>(new TwoFactorsAEDMAnalyzers());
	}

	const std::string & TwoFactorsAEDMAnalyzers::category(void) const
	{
		return TwoFactorsAEDM::Category;
	}

	TwoFactorsAEDMAnalyzers::AnalyzerGroup TwoFactorsAEDMAnalyzers::generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const
	{
		// to do
		return AnalyzerGroup();
	}

	/*
	const std::map<std::string, std::string>& TwoFactorsAEDMAnalyzers::flags(void) const
	{
		static const std::map<std::string, std::string> ret =
		{
			std::make_pair(VarianceOriginFlag, std::string("方差法（原始）")), 
			std::make_pair(Factor1_2_SumFlag, std::string("无（因子1-因子2-指标和值)"))
		};
		return ret;
	}

	const std::map<std::string, CARSDK::IExperimentalAnalyzerInterface::Analyzer>& TwoFactorsAEDMAnalyzers::analyzers(void) const
	{
		static const std::map<std::string, CARSDK::IExperimentalAnalyzerInterface::Analyzer> ret = 
		{
			std::make_pair(VarianceOriginFlag, variance_origin_anzlyer),
			std::make_pair(Factor1_2_SumFlag, factor_1_2_sum_anzlyer)
		};
		return ret;
	}
	*/

	std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::variance_origin_anzlyer(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data, const std::map<std::string, std::string>& attributes, const std::string & flag)
	{
		return std::pair<CARSDK::AnalysisResultType, std::string>();
	}

	std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::factor_1_2_sum_anzlyer(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data, const std::map<std::string, std::string>& attributes, const std::string & flag)
	{
		return std::pair<CARSDK::AnalysisResultType, std::string>();
	}
};
