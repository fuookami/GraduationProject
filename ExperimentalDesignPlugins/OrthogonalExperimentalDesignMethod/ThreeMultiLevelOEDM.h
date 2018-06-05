#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"
#include "CARSDK/ExperimentalAnalyzerInterface.h"

namespace OEDM
{
	class ThreeMultiLevelOEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static const std::string Category;
		static const std::string TimeAttr;
		static const std::string ColumnAttr;
		static const std::string Level1Number;
		static const std::string Level2Number;
		static const std::string Level3Number;
		static const std::string InteractionEffectAttr;

	public:
		static boost::shared_ptr<ThreeMultiLevelOEDM> create(void);

	private:
		ThreeMultiLevelOEDM(void) = default;
	public:
		ThreeMultiLevelOEDM(const ThreeMultiLevelOEDM &ano) = delete;
		ThreeMultiLevelOEDM(ThreeMultiLevelOEDM &&ano) = delete;
		ThreeMultiLevelOEDM &operator=(const ThreeMultiLevelOEDM &rhs) = delete;
		ThreeMultiLevelOEDM &operator=(ThreeMultiLevelOEDM &&rhs) = delete;
		~ThreeMultiLevelOEDM(void) = default;

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

	class ThreeMultiLevelOEDMAnalyzers : public CARSDK::IExperimentalAnalyzerInterface
	{
	public:
		static const std::string VarianceOriginFlag;

	public:
		static boost::shared_ptr<ThreeMultiLevelOEDMAnalyzers> create(void);

	private:
		ThreeMultiLevelOEDMAnalyzers(void) = default;
	public:
		ThreeMultiLevelOEDMAnalyzers(const ThreeMultiLevelOEDMAnalyzers &ano) = delete;
		ThreeMultiLevelOEDMAnalyzers(ThreeMultiLevelOEDMAnalyzers &&ano) = delete;
		ThreeMultiLevelOEDMAnalyzers &operator=(const ThreeMultiLevelOEDMAnalyzers &ano) = delete;
		ThreeMultiLevelOEDMAnalyzers &operator=(ThreeMultiLevelOEDMAnalyzers &&ano) = delete;
		~ThreeMultiLevelOEDMAnalyzers(void) = default;

		const std::string &category(void) const override;
		AnalyzerGroup generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const override;
	};
};
