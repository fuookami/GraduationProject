#include "stdafx.h"
#include "UEDM.h"

namespace UEDM
{
	const std::string UEDM::Category("UEDM");
	const std::string UEDM::TimeAttr("time");
	const std::string UEDM::LevelAttr("level");
	const std::string UEDM::ColumnAttr("column");
	const std::string UEDM::InteractionEffectAttr("has_interaction_effect");

	boost::shared_ptr<UEDM> UEDM::create(void)
	{
		return boost::shared_ptr<UEDM>(new UEDM());
	}

	const std::string &UEDM::category(void) const
	{
		return Category;
	}

	const std::string &UEDM::displayName(void) const
	{
		static const std::string ret("均匀设计方法");
		return ret;
	}

	const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> &UEDM::neededAttributes(void) const
	{
		static const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> ret =
		{
			std::make_pair(InteractionEffectAttr, std::make_pair(std::string("交互作用"), CARSDK::AttributeType::Boolean)),
			std::make_pair(TimeAttr, std::make_pair(std::string("实验次数"), CARSDK::AttributeType::Number)),
			std::make_pair(LevelAttr, std::make_pair(std::string("实验因素水平数"), CARSDK::AttributeType::Number)),
			std::make_pair(ColumnAttr, std::make_pair(std::string("列数"), CARSDK::AttributeType::Number))
		};
		return ret;
	}

	const std::map<std::string, std::string> &UEDM::factorNeededAttributes(void) const
	{
		static const std::map<std::string, std::string> ret = DefaultFactorAttributes;
		return ret;
	}

	const bool UEDM::valid(const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	const bool UEDM::valid(const std::map<std::string, std::string>& attributes, const CARSDK::DataModelingModule::FactorTypeGroup & factorTypeGroup)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return false;
	}

	CARSDK::ExperimentalDesignTable UEDM::generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel>& xsdModel, const std::map<std::string, std::string>& attributes)
	{
		m_lastError.assign(std::string("未实现"));
		// to do
		return CARSDK::ExperimentalDesignTable();
	}

	CARSDK::ExperimentalDesignTable::Cell UEDM::generateCell(const CARSDK::DataModelingModule::FactorType & info, const std::string & value)
	{
		return IExperimentalDesignMethodInterface::generateCell(info, value);
	}

	boost::shared_ptr<UEDMAnalyzers> UEDMAnalyzers::create(void)
	{
		return boost::shared_ptr<UEDMAnalyzers>(new UEDMAnalyzers());
	}

	const std::string & UEDMAnalyzers::category(void) const
	{
		return UEDM::Category;
	}

	UEDMAnalyzers::AnalyzerGroup UEDMAnalyzers::generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const
	{
		// to do
		return AnalyzerGroup();
	}
};
