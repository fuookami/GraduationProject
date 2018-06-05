#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"
#include "CARSDK/ExperimentalAnalyzerInterface.h"

namespace AEDM
{
	class ThreeFactorsAEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static const std::string Category;
		static const std::string RepeatTimeAttr;
		static const std::string InteractionEffectAttr;

	public:
		static boost::shared_ptr<ThreeFactorsAEDM> create(void);

	private:
		ThreeFactorsAEDM(void) = default;
	public:
		ThreeFactorsAEDM(const ThreeFactorsAEDM &ano) = delete;
		ThreeFactorsAEDM(ThreeFactorsAEDM &&ano) = delete;
		ThreeFactorsAEDM &operator=(const ThreeFactorsAEDM &rhs) = delete;
		ThreeFactorsAEDM &operator=(ThreeFactorsAEDM &&rhs) = delete;
		~ThreeFactorsAEDM(void) = default;

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

	class ThreeFactorsAEDMAnalyzers : public CARSDK::IExperimentalAnalyzerInterface
	{
	public:
		static const std::string VarianceOriginFlag;

	public:
		static boost::shared_ptr<ThreeFactorsAEDMAnalyzers> create(void);

	private:
		ThreeFactorsAEDMAnalyzers(void) = default;
	public:
		ThreeFactorsAEDMAnalyzers(const ThreeFactorsAEDMAnalyzers &ano) = delete;
		ThreeFactorsAEDMAnalyzers(ThreeFactorsAEDMAnalyzers &&ano) = delete;
		ThreeFactorsAEDMAnalyzers &operator=(const ThreeFactorsAEDMAnalyzers &rhs) = delete;
		ThreeFactorsAEDMAnalyzers &operator=(ThreeFactorsAEDMAnalyzers &&rhs) = delete;
		~ThreeFactorsAEDMAnalyzers(void) = default;

		const std::string &category(void) const override;
		AnalyzerGroup generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const override;
	};
};
