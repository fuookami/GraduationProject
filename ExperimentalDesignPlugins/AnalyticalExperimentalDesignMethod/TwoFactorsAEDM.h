#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"
#include "CARSDK/ExperimentalAnalyzerInterface.h"
#include <tuple>

namespace AEDM
{
	class TwoFactorsAEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static const std::string Category;
		static const std::string DisplayName;
		static const std::string RepeatTimeAttr;
		static const std::string InteractionEffectAttr;

	public:
		static boost::shared_ptr<TwoFactorsAEDM> create(void);

	private:
		TwoFactorsAEDM(void) = default;
	public:
		TwoFactorsAEDM(const TwoFactorsAEDM &ano) = delete;
		TwoFactorsAEDM(TwoFactorsAEDM &&ano) = delete;
		TwoFactorsAEDM &operator=(const TwoFactorsAEDM &rhs) = delete;
		TwoFactorsAEDM &operator=(TwoFactorsAEDM &&rhs) = delete;
		~TwoFactorsAEDM(void) = default;

		const std::string &category(void) const override;
		const std::string &displayName(void) const override;
		const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> &neededAttributes(void) const override;
		const std::map<std::string, std::string> &factorNeededAttributes(void) const override;
		const bool valid(const std::map<std::string, std::string> &attributes) override;
		const bool valid(const std::map<std::string, std::string> &attributes, const CARSDK::FactorTypeGroup &factorTypeGroup) override;
		CARSDK::ExperimentalDesignTable generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel> &xsdModel, const std::map<std::string, std::string> &attributes) override;

	protected:
		CARSDK::ExperimentalDesignTable::Cell generateCell(const CARSDK::FactorType &info, const std::string &value = std::string("")) override;
	};

	class TwoFactorsAEDMAnalyzers : public CARSDK::IExperimentalAnalyzerInterface
	{
	public:
		static std::tuple<std::string, std::string, Analyzer> OriginAnalyzer(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 evaluateFactorOrder);
		static std::tuple<std::string, std::string, Analyzer> VarianceOriginAnalyzer(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 evaluateFactorOrder);
		static std::tuple<std::string, std::string, Analyzer> FactorSumAnalyzer(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder);
		static std::tuple<std::string, std::string, Analyzer> FactorAverageAnalyzer(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder);
		static std::tuple<std::string, std::string, Analyzer> Factor1Factor2SumAnalyzer(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 evaluateFactorOrder);
		static std::tuple<std::string, std::string, Analyzer> Factor1Factor2AverageAnalyzer(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 evaluateFactorOrder);

	public:
		static boost::shared_ptr<TwoFactorsAEDMAnalyzers> create(void);

	private:
		TwoFactorsAEDMAnalyzers(void) = default;
	public:
		TwoFactorsAEDMAnalyzers(const TwoFactorsAEDMAnalyzers &ano) = delete;
		TwoFactorsAEDMAnalyzers(TwoFactorsAEDMAnalyzers &&ano) = delete;
		TwoFactorsAEDMAnalyzers &operator=(const TwoFactorsAEDMAnalyzers &rhs) = delete;
		TwoFactorsAEDMAnalyzers &operator=(TwoFactorsAEDMAnalyzers &&rhs) = delete;
		~TwoFactorsAEDMAnalyzers(void) = default;

		const std::string &category(void) const override;
		const std::string &displayName(void) const override;
		AnalyzerGroup generateAnalyzerGroup(const CARSDK::FactorTypeGroup &group) const override;

	private:
		static const std::pair<CARSDK::AnalysisResultType, std::string> originAnalyse(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 experimentalFactorOrder, const CARSDK::ExperimentalDesignTable &table, const std::map<std::string, std::string> &attributes);
		static const std::pair<CARSDK::AnalysisResultType, std::string> varianceOriginAnalyse(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 experimentalFactorOrder, const CARSDK::ExperimentalDesignTable &table, const std::map<std::string, std::string> &attributes);
		static const std::pair<CARSDK::AnalysisResultType, std::string> factorSumAnalyse(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable &table, const std::map<std::string, std::string> &attributes);
		static const std::pair<CARSDK::AnalysisResultType, std::string> factorAverageAnalyse(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable &table, const std::map<std::string, std::string> &attributes);
		static const std::pair<CARSDK::AnalysisResultType, std::string> factor1Factor2SumAnalyse(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable &table, const std::map<std::string, std::string> &attributes);
		static const std::pair<CARSDK::AnalysisResultType, std::string> factor1Factor2AverageAnalyse(const CARSDK::FactorTypeGroup &group, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable &table, const std::map<std::string, std::string> &attributes);
	};
};
