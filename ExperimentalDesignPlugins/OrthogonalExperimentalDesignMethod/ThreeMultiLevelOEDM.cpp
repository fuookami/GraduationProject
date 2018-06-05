#include "stdafx.h"
#include "ThreeMultiLevelOEDM.h"

namespace OEDM
{
	const std::string ThreeMultiLevelOEDM::Category("ThreeMultiLevelOEDM");
	const std::string ThreeMultiLevelOEDM::TimeAttr("time");
	const std::string ThreeMultiLevelOEDM::ColumnAttr("column");
	const std::string ThreeMultiLevelOEDM::Level1Number("level_1_number");
	const std::string ThreeMultiLevelOEDM::Level2Number("level_2_number");
	const std::string ThreeMultiLevelOEDM::Level3Number("level_3_number");
	const std::string ThreeMultiLevelOEDM::InteractionEffectAttr("has_interaction_effect");

	boost::shared_ptr<ThreeMultiLevelOEDM> ThreeMultiLevelOEDM::create(void)
	{
		return boost::shared_ptr<ThreeMultiLevelOEDM>(new ThreeMultiLevelOEDM());
	}

	const std::string &ThreeMultiLevelOEDM::category(void) const
	{
		return Category;
	}

	const std::string &ThreeMultiLevelOEDM::displayName(void) const
	{
		static const std::string ret("三混合水平正交设计方法");
		return ret;
	}

	const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> &ThreeMultiLevelOEDM::neededAttributes(void) const
	{
		static const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> ret =
		{
			std::make_pair(InteractionEffectAttr, std::make_pair(std::string("交互作用"), CARSDK::AttributeType::Boolean)),
			std::make_pair(TimeAttr, std::make_pair(std::string("实验次数"), CARSDK::AttributeType::Number)),
			std::make_pair(ColumnAttr, std::make_pair(std::string("列数"), CARSDK::AttributeType::Number)),
			std::make_pair(Level1Number, std::make_pair(std::string("水平一数量"), CARSDK::AttributeType::Number)),
			std::make_pair(Level2Number, std::make_pair(std::string("水平二数量"), CARSDK::AttributeType::Number)),
			std::make_pair(Level3Number, std::make_pair(std::string("水平三数量"), CARSDK::AttributeType::Number))
		};
		return ret;
	}

	const std::map<std::string, std::string> &ThreeMultiLevelOEDM::factorNeededAttributes(void) const
	{
		static const std::map<std::string, std::string> ret = DefaultFactorAttributes;
		return ret;
	}

	const bool ThreeMultiLevelOEDM::valid(const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	const bool ThreeMultiLevelOEDM::valid(const std::map<std::string, std::string>& attributes, const CARSDK::FactorTypeGroup & factorTypeGroup)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	CARSDK::ExperimentalDesignTable ThreeMultiLevelOEDM::generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel>& xsdModel, const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return CARSDK::ExperimentalDesignTable();
	}

	CARSDK::ExperimentalDesignTable::Cell ThreeMultiLevelOEDM::generateCell(const CARSDK::FactorType & info, const std::string & value)
	{
		return IExperimentalDesignMethodInterface::generateCell(info, value);
	}

	boost::shared_ptr<ThreeMultiLevelOEDMAnalyzers> ThreeMultiLevelOEDMAnalyzers::create(void)
	{
		return boost::shared_ptr<ThreeMultiLevelOEDMAnalyzers>(new ThreeMultiLevelOEDMAnalyzers());
	}

	const std::string & ThreeMultiLevelOEDMAnalyzers::category(void) const
	{
		return ThreeMultiLevelOEDM::Category;
	}

	ThreeMultiLevelOEDMAnalyzers::AnalyzerGroup ThreeMultiLevelOEDMAnalyzers::generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const
	{
		// to do
		return AnalyzerGroup();
	}
};
