#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"
#include "CARSDK/ExperimentalAnalyzerInterface.h"

namespace AEDM
{
	class TwoFactorsAEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static const std::string Category;
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
		const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> &neededAttributes(void) const override;
		const std::map<std::string, std::string> &factorNeededAttributes(void) const override;
		const bool valid(const std::map<std::string, std::string> &attributes) override;
		CARSDK::ExperimentalDesignTable generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel> &xsdModel, const std::map<std::string, std::string> &attributes) override;
	};

	class TwoFactorsAEDMAnalyzers : public CARSDK::IExperimentalAnalyzerInterface
	{
	public:
		static const std::string VarianceOriginFlag;
		static const std::string Factor1_2_SumFlag;

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
		const std::map<std::string, std::string> &flags(void) const override;
		const std::map<std::string, Analyzer> &analyzers(void) const override;

	private:
		static std::pair<CARSDK::AnalysisResultType, std::string> variance_origin_anzlyer(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data, const std::map<std::string, std::string> &attributes, const std::string &flag);
		static std::pair<CARSDK::AnalysisResultType, std::string> factor_1_2_sum_anzlyer(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data, const std::map<std::string, std::string> &attributes, const std::string &flag);
	};
};
