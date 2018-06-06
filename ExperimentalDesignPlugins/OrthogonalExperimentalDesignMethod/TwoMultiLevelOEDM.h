#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"
#include "CARSDK/ExperimentalAnalyzerInterface.h"

namespace OEDM
{
	class TwoMultiLevelOEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static const std::string Category;
		static const std::string DisplayName;
		static const std::string TimeAttr;
		static const std::string ColumnAttr;
		static const std::string Level1Number;
		static const std::string Level2Number;
		static const std::string InteractionEffectAttr;

	public:
		static boost::shared_ptr<TwoMultiLevelOEDM> create(void);

	private:
		TwoMultiLevelOEDM(void) = default;
	public:
		TwoMultiLevelOEDM(const TwoMultiLevelOEDM &ano) = delete;
		TwoMultiLevelOEDM(TwoMultiLevelOEDM &&ano) = delete;
		TwoMultiLevelOEDM &operator=(const TwoMultiLevelOEDM &rhs) = delete;
		TwoMultiLevelOEDM &operator=(TwoMultiLevelOEDM &&rhs) = delete;
		~TwoMultiLevelOEDM(void) = default;

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

	class TwoMultiLevelOEDMAnalyzers : public CARSDK::IExperimentalAnalyzerInterface
	{
	public:
		static const std::string VarianceOriginFlag;

	public:
		static boost::shared_ptr<TwoMultiLevelOEDMAnalyzers> create(void);

	private:
		TwoMultiLevelOEDMAnalyzers(void) = default;
	public:
		TwoMultiLevelOEDMAnalyzers(const TwoMultiLevelOEDMAnalyzers &ano) = delete;
		TwoMultiLevelOEDMAnalyzers(TwoMultiLevelOEDMAnalyzers &&ano) = delete;
		TwoMultiLevelOEDMAnalyzers &operator=(const TwoMultiLevelOEDMAnalyzers &ano) = delete;
		TwoMultiLevelOEDMAnalyzers &operator=(TwoMultiLevelOEDMAnalyzers &&ano) = delete;
		~TwoMultiLevelOEDMAnalyzers(void) = default;

		const std::string &category(void) const override;
		const std::string &displayName(void) const override;
		AnalyzerGroup generateAnalyzerGroup(const CARSDK::FactorTypeGroup &group) const override;
	};
};
