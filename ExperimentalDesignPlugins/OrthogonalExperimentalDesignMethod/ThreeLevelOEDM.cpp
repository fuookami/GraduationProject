#include "stdafx.h"
#include "ThreeLevelOEDM.h"

namespace OEDM
{
	const std::string ThreeLevelOEDM::Category("ThreeLevelOEDM");
	const std::string ThreeLevelOEDM::TimeAttr("time");
	const std::string ThreeLevelOEDM::ColumnAttr("column");
	const std::string ThreeLevelOEDM::InteractionEffectAttr("has_interaction_effect");

	boost::shared_ptr<ThreeLevelOEDM> ThreeLevelOEDM::create(void)
	{
		return boost::shared_ptr<ThreeLevelOEDM>(new ThreeLevelOEDM());
	}

	const std::string &ThreeLevelOEDM::category(void) const
	{
		return Category;
	}

	const std::string &ThreeLevelOEDM::displayName(void) const
	{
		static const std::string ret("三水平正交设计方法");
		return ret;
	}

	const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> &ThreeLevelOEDM::neededAttributes(void) const
	{
		static const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> ret =
		{
			std::make_pair(InteractionEffectAttr, std::make_pair(std::string("交互作用"), CARSDK::AttributeType::Boolean)),
			std::make_pair(TimeAttr, std::make_pair(std::string("实验次数"), CARSDK::AttributeType::Number)),
			std::make_pair(ColumnAttr, std::make_pair(std::string("列数"), CARSDK::AttributeType::Number))
		};
		return ret;
	}

	const std::map<std::string, std::string> &ThreeLevelOEDM::factorNeededAttributes(void) const
	{
		static const std::map<std::string, std::string> ret = DefaultFactorAttributes;
		return ret;
	}

	const bool ThreeLevelOEDM::valid(const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	const bool ThreeLevelOEDM::valid(const std::map<std::string, std::string>& attributes, const CARSDK::FactorTypeGroup & factorTypeGroup)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	CARSDK::ExperimentalDesignTable ThreeLevelOEDM::generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel>& xsdModel, const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return CARSDK::ExperimentalDesignTable();
	}

	CARSDK::ExperimentalDesignTable::Cell ThreeLevelOEDM::generateCell(const CARSDK::FactorType & info, const std::string & value)
	{
		return IExperimentalDesignMethodInterface::generateCell(info, value);
	}

	boost::shared_ptr<ThreeLevelOEDMAnalyzers> ThreeLevelOEDMAnalyzers::create(void)
	{
		return boost::shared_ptr<ThreeLevelOEDMAnalyzers>(new ThreeLevelOEDMAnalyzers());
	}

	const std::string & ThreeLevelOEDMAnalyzers::category(void) const
	{
		return ThreeLevelOEDM::Category;
	}

	ThreeLevelOEDMAnalyzers::AnalyzerGroup ThreeLevelOEDMAnalyzers::generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const
	{
		// to do
		return AnalyzerGroup();
	}
};
