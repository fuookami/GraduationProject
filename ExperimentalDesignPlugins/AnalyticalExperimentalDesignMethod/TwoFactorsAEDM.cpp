#include "stdafx.h"
#include "TwoFactorsAEDM.h"

namespace AEDM
{
	const std::string TwoFactorsAEDM::Category("TwoFactorAEDM");
	const std::string TwoFactorsAEDM::RepeatTimeAttr("repeat_time");
	const std::string TwoFactorsAEDM::InteractionEffectAttr("has_interaction_effect");

	const std::string TwoFactorsAEDMAnalyzers::VarianceOriginFlag("variance_origin");
	const std::string TwoFactorsAEDMAnalyzers::Factor1_2_SumFlag("factor1_2_sum");

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

	const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> &TwoFactorsAEDM::neededAttributes(void) const
	{
		static const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> ret = 
		{
			std::make_pair(InteractionEffectAttr, std::make_pair(std::string("交互作用"), CARSDK::AttributeType::Boolean)),
			std::make_pair(RepeatTimeAttr, std::make_pair(std::string("重复次数"), CARSDK::AttributeType::Number))
		};
		return ret;
	}

	const std::map<std::string, std::string>& TwoFactorsAEDM::factorNeededAttributes(void) const
	{
		static const std::map<std::string, std::string> ret;
		return ret;
	}

	const bool TwoFactorsAEDM::valid(const std::map<std::string, std::string>& attributes) const
	{
		return false;
	}

	CARSDK::ExperimentalDesignTable TwoFactorsAEDM::generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel>& xsdModel, const std::map<std::string, std::string>& attributes) const
	{
		return CARSDK::ExperimentalDesignTable();
	}

	boost::shared_ptr<TwoFactorsAEDMAnalyzers> TwoFactorsAEDMAnalyzers::create(void)
	{
		return boost::shared_ptr<TwoFactorsAEDMAnalyzers>(new TwoFactorsAEDMAnalyzers());
	}

	const std::string & TwoFactorsAEDMAnalyzers::category(void) const
	{
		return TwoFactorsAEDM::Category;
	}

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

	std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::variance_origin_anzlyer(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data, const std::map<std::string, std::string>& attributes, const std::string & flag)
	{
		return std::pair<CARSDK::AnalysisResultType, std::string>();
	}

	std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::factor_1_2_sum_anzlyer(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data, const std::map<std::string, std::string>& attributes, const std::string & flag)
	{
		return std::pair<CARSDK::AnalysisResultType, std::string>();
	}
};
