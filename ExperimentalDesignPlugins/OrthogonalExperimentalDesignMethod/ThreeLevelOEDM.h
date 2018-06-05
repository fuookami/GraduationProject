#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"
#include "CARSDK/ExperimentalAnalyzerInterface.h"

namespace OEDM
{
	class ThreeLevelOEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static const std::string Category;
		static const std::string TimeAttr;
		static const std::string ColumnAttr;
		static const std::string InteractionEffectAttr;

	public:
		static boost::shared_ptr<ThreeLevelOEDM> create(void);

	private:
		ThreeLevelOEDM(void) = default;
	public:
		ThreeLevelOEDM(const ThreeLevelOEDM &ano) = delete;
		ThreeLevelOEDM(ThreeLevelOEDM &&ano) = delete;
		ThreeLevelOEDM &operator=(const ThreeLevelOEDM &rhs) = delete;
		ThreeLevelOEDM &operator=(ThreeLevelOEDM &&rhs) = delete;
		~ThreeLevelOEDM(void) = default;

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

	class ThreeLevelOEDMAnalyzers : public CARSDK::IExperimentalAnalyzerInterface
	{
	public:
		static const std::string VarianceOriginFlag;

	public:
		static boost::shared_ptr<ThreeLevelOEDMAnalyzers> create(void);

	private:
		ThreeLevelOEDMAnalyzers(void) = default;
	public:
		ThreeLevelOEDMAnalyzers(const ThreeLevelOEDMAnalyzers &ano) = delete;
		ThreeLevelOEDMAnalyzers(ThreeLevelOEDMAnalyzers &&ano) = delete;
		ThreeLevelOEDMAnalyzers &operator=(const ThreeLevelOEDMAnalyzers &ano) = delete;
		ThreeLevelOEDMAnalyzers &operator=(ThreeLevelOEDMAnalyzers &&ano) = delete;
		~ThreeLevelOEDMAnalyzers(void) = default;

		const std::string &category(void) const override;
		AnalyzerGroup generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const override;
	};
};
