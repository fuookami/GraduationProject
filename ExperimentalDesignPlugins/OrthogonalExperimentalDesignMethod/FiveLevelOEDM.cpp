#include "stdafx.h"
#include "FiveLevelOEDM.h"

namespace OEDM
{
	const std::string FiveLevelOEDM::Category("FiveLevelOEDM");
	const std::string FiveLevelOEDM::DisplayName("五水平正交设计方法");
	const std::string FiveLevelOEDM::TimeAttr("time");
	const std::string FiveLevelOEDM::ColumnAttr("column");
	const std::string FiveLevelOEDM::InteractionEffectAttr("has_interaction_effect");

	boost::shared_ptr<FiveLevelOEDM> FiveLevelOEDM::create(void)
	{
		return boost::shared_ptr<FiveLevelOEDM>(new FiveLevelOEDM());
	}

	const std::string &FiveLevelOEDM::category(void) const
	{
		return Category;
	}

	const std::string &FiveLevelOEDM::displayName(void) const
	{
		return DisplayName;
	}

	const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> &FiveLevelOEDM::neededAttributes(void) const
	{
		static const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> ret =
		{
			std::make_pair(InteractionEffectAttr, std::make_pair(std::string("交互作用"), CARSDK::AttributeType::Boolean)),
			std::make_pair(TimeAttr, std::make_pair(std::string("实验次数"), CARSDK::AttributeType::Number)),
			std::make_pair(ColumnAttr, std::make_pair(std::string("列数"), CARSDK::AttributeType::Number))
		};
		return ret;
	}

	const std::map<std::string, std::string> &FiveLevelOEDM::factorNeededAttributes(void) const
	{
		static const std::map<std::string, std::string> ret = DefaultFactorAttributes;
		return ret;
	}

	const bool FiveLevelOEDM::valid(const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	const bool FiveLevelOEDM::valid(const std::map<std::string, std::string>& attributes, const CARSDK::FactorTypeGroup & factorTypeGroup)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	CARSDK::ExperimentalDesignTable FiveLevelOEDM::generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel>& xsdModel, const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return CARSDK::ExperimentalDesignTable();
	}

	CARSDK::ExperimentalDesignTable::Cell FiveLevelOEDM::generateCell(const CARSDK::FactorType & info, const std::string & value)
	{
		return IExperimentalDesignMethodInterface::generateCell(info, value);
	}

	boost::shared_ptr<FiveLevelOEDMAnalyzers> FiveLevelOEDMAnalyzers::create(void)
	{
		return boost::shared_ptr<FiveLevelOEDMAnalyzers>(new FiveLevelOEDMAnalyzers());
	}

	const std::string & FiveLevelOEDMAnalyzers::category(void) const
	{
		return FiveLevelOEDM::Category;
	}

	const std::string & FiveLevelOEDMAnalyzers::displayName(void) const
	{
		return FiveLevelOEDM::DisplayName;
	}

	FiveLevelOEDMAnalyzers::AnalyzerGroup FiveLevelOEDMAnalyzers::generateAnalyzerGroup(const CARSDK::FactorTypeGroup &group) const
	{
		// to do
		return AnalyzerGroup();
	}
};
