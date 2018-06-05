#include "stdafx.h"
#include "TwoLevelOEDM.h"

namespace OEDM
{
	const std::string TwoLevelOEDM::Category("TwoLevelOEDM");
	const std::string TwoLevelOEDM::TimeAttr("time");
	const std::string TwoLevelOEDM::ColumnAttr("column");
	const std::string TwoLevelOEDM::InteractionEffectAttr("has_interaction_effect");

	boost::shared_ptr<TwoLevelOEDM> TwoLevelOEDM::create(void)
	{
		return boost::shared_ptr<TwoLevelOEDM>(new TwoLevelOEDM());
	}

	const std::string &TwoLevelOEDM::category(void) const
	{
		return Category;
	}

	const std::string &TwoLevelOEDM::displayName(void) const
	{
		static const std::string ret("二水平正交设计方法");
		return ret;
	}

	const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> &TwoLevelOEDM::neededAttributes(void) const
	{
		static const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> ret =
		{
			std::make_pair(InteractionEffectAttr, std::make_pair(std::string("交互作用"), CARSDK::AttributeType::Boolean)),
			std::make_pair(TimeAttr, std::make_pair(std::string("实验次数"), CARSDK::AttributeType::Number)),
			std::make_pair(ColumnAttr, std::make_pair(std::string("列数"), CARSDK::AttributeType::Number))
		};
		return ret;
	}

	const std::map<std::string, std::string> &TwoLevelOEDM::factorNeededAttributes(void) const
	{
		static const std::map<std::string, std::string> ret = DefaultFactorAttributes;
		return ret;
	}

	const bool TwoLevelOEDM::valid(const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	const bool TwoLevelOEDM::valid(const std::map<std::string, std::string>& attributes, const CARSDK::DataModelingModule::FactorTypeGroup & factorTypeGroup)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	CARSDK::ExperimentalDesignTable TwoLevelOEDM::generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel>& xsdModel, const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return CARSDK::ExperimentalDesignTable();
	}

	CARSDK::ExperimentalDesignTable::Cell TwoLevelOEDM::generateCell(const CARSDK::DataModelingModule::FactorType & info, const std::string & value)
	{
		return IExperimentalDesignMethodInterface::generateCell(info, value);
	}

	boost::shared_ptr<TwoLevelOEDMAnalyzers> TwoLevelOEDMAnalyzers::create(void)
	{
		return boost::shared_ptr<TwoLevelOEDMAnalyzers>(new TwoLevelOEDMAnalyzers());
	}

	const std::string & TwoLevelOEDMAnalyzers::category(void) const
	{
		return TwoLevelOEDM::Category;
	}

	TwoLevelOEDMAnalyzers::AnalyzerGroup TwoLevelOEDMAnalyzers::generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const
	{
		// to do
		return AnalyzerGroup();
	}
};
