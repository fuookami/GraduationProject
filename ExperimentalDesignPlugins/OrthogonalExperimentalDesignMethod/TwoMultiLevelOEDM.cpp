#include "stdafx.h"
#include "TwoMultiLevelOEDM.h"

namespace OEDM
{
	const std::string TwoMultiLevelOEDM::Category("TwoMultiLevelOEDM");
	const std::string TwoMultiLevelOEDM::TimeAttr("time");
	const std::string TwoMultiLevelOEDM::ColumnAttr("column");
	const std::string TwoMultiLevelOEDM::Level1Number("level_1_number");
	const std::string TwoMultiLevelOEDM::Level2Number("level_2_number");
	const std::string TwoMultiLevelOEDM::InteractionEffectAttr("has_interaction_effect");

	boost::shared_ptr<TwoMultiLevelOEDM> TwoMultiLevelOEDM::create(void)
	{
		return boost::shared_ptr<TwoMultiLevelOEDM>(new TwoMultiLevelOEDM());
	}

	const std::string &TwoMultiLevelOEDM::category(void) const
	{
		return Category;
	}

	const std::string &TwoMultiLevelOEDM::displayName(void) const
	{
		static const std::string ret("二混合水平正交设计方法");
		return ret;
	}

	const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> &TwoMultiLevelOEDM::neededAttributes(void) const
	{
		static const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> ret =
		{
			std::make_pair(InteractionEffectAttr, std::make_pair(std::string("交互作用"), CARSDK::AttributeType::Boolean)),
			std::make_pair(TimeAttr, std::make_pair(std::string("实验次数"), CARSDK::AttributeType::Number)),
			std::make_pair(ColumnAttr, std::make_pair(std::string("列数"), CARSDK::AttributeType::Number)),
			std::make_pair(Level1Number, std::make_pair(std::string("水平一数量"), CARSDK::AttributeType::Number)),
			std::make_pair(Level2Number, std::make_pair(std::string("水平二数量"), CARSDK::AttributeType::Number))
		};
		return ret;
	}

	const std::map<std::string, std::string> &TwoMultiLevelOEDM::factorNeededAttributes(void) const
	{
		static const std::map<std::string, std::string> ret = DefaultFactorAttributes;
		return ret;
	}

	const bool TwoMultiLevelOEDM::valid(const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	const bool TwoMultiLevelOEDM::valid(const std::map<std::string, std::string>& attributes, const CARSDK::FactorTypeGroup & factorTypeGroup)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	CARSDK::ExperimentalDesignTable TwoMultiLevelOEDM::generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel>& xsdModel, const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return CARSDK::ExperimentalDesignTable();
	}

	CARSDK::ExperimentalDesignTable::Cell TwoMultiLevelOEDM::generateCell(const CARSDK::FactorType & info, const std::string & value)
	{
		return IExperimentalDesignMethodInterface::generateCell(info, value);
	}

	boost::shared_ptr<TwoMultiLevelOEDMAnalyzers> TwoMultiLevelOEDMAnalyzers::create(void)
	{
		return boost::shared_ptr<TwoMultiLevelOEDMAnalyzers>(new TwoMultiLevelOEDMAnalyzers());
	}

	const std::string & TwoMultiLevelOEDMAnalyzers::category(void) const
	{
		return TwoMultiLevelOEDM::Category;
	}

	TwoMultiLevelOEDMAnalyzers::AnalyzerGroup TwoMultiLevelOEDMAnalyzers::generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const
	{
		// to do
		return AnalyzerGroup();
	}
};
