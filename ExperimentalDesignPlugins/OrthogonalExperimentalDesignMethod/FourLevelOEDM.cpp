#include "stdafx.h"
#include "FourLevelOEDM.h"

namespace OEDM
{
	const std::string FourLevelOEDM::Category("FourLevelOEDM");
	const std::string FourLevelOEDM::TimeAttr("time");
	const std::string FourLevelOEDM::ColumnAttr("column");
	const std::string FourLevelOEDM::InteractionEffectAttr("has_interaction_effect");

	boost::shared_ptr<FourLevelOEDM> FourLevelOEDM::create(void)
	{
		return boost::shared_ptr<FourLevelOEDM>(new FourLevelOEDM());
	}

	const std::string &FourLevelOEDM::category(void) const
	{
		return Category;
	}

	const std::string &FourLevelOEDM::displayName(void) const
	{
		static const std::string ret("四水平正交设计方法");
		return ret;
	}

	const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> &FourLevelOEDM::neededAttributes(void) const
	{
		static const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> ret =
		{
			std::make_pair(InteractionEffectAttr, std::make_pair(std::string("交互作用"), CARSDK::AttributeType::Boolean)),
			std::make_pair(TimeAttr, std::make_pair(std::string("实验次数"), CARSDK::AttributeType::Number)),
			std::make_pair(ColumnAttr, std::make_pair(std::string("列数"), CARSDK::AttributeType::Number))
		};
		return ret;
	}

	const std::map<std::string, std::string> &FourLevelOEDM::factorNeededAttributes(void) const
	{
		static const std::map<std::string, std::string> ret = DefaultFactorAttributes;
		return ret;
	}

	const bool FourLevelOEDM::valid(const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	const bool FourLevelOEDM::valid(const std::map<std::string, std::string>& attributes, const CARSDK::FactorTypeGroup & factorTypeGroup)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	CARSDK::ExperimentalDesignTable FourLevelOEDM::generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel>& xsdModel, const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return CARSDK::ExperimentalDesignTable();
	}

	CARSDK::ExperimentalDesignTable::Cell FourLevelOEDM::generateCell(const CARSDK::FactorType & info, const std::string & value)
	{
		return IExperimentalDesignMethodInterface::generateCell(info, value);
	}

	boost::shared_ptr<FourLevelOEDMAnalyzers> FourLevelOEDMAnalyzers::create(void)
	{
		return boost::shared_ptr<FourLevelOEDMAnalyzers>(new FourLevelOEDMAnalyzers());
	}

	const std::string & FourLevelOEDMAnalyzers::category(void) const
	{
		return FourLevelOEDM::Category;
	}

	FourLevelOEDMAnalyzers::AnalyzerGroup FourLevelOEDMAnalyzers::generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const
	{
		// to do
		return AnalyzerGroup();
	}
};
