#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"
#include "CARSDK/ExperimentalAnalyzerInterface.h"

namespace OEDM
{
	class FiveLevelOEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static const std::string Category;
		static const std::string TimeAttr;
		static const std::string ColumnAttr;
		static const std::string InteractionEffectAttr;

	public:
		static boost::shared_ptr<FiveLevelOEDM> create(void);

	private:
		FiveLevelOEDM(void) = default;
	public:
		FiveLevelOEDM(const FiveLevelOEDM &ano) = delete;
		FiveLevelOEDM(FiveLevelOEDM &&ano) = delete;
		FiveLevelOEDM &operator=(const FiveLevelOEDM &rhs) = delete;
		FiveLevelOEDM &operator=(FiveLevelOEDM &&rhs) = delete;
		~FiveLevelOEDM(void) = default;

		const std::string &category(void) const override;
		const std::string &displayName(void) const override;
		const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> &neededAttributes(void) const override;
		const std::map<std::string, std::string> &factorNeededAttributes(void) const override;
		const bool valid(const std::map<std::string, std::string> &attributes) override;
		const bool valid(const std::map<std::string, std::string> &attributes, const CARSDK::DataModelingModule::FactorTypeGroup &factorTypeGroup) override;
		CARSDK::ExperimentalDesignTable generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel> &xsdModel, const std::map<std::string, std::string> &attributes) override;

	protected:
		CARSDK::ExperimentalDesignTable::Cell generateCell(const CARSDK::DataModelingModule::FactorType &info, const std::string &value = std::string("")) override;
	};

	class FiveLevelOEDMAnalyzers : public CARSDK::IExperimentalAnalyzerInterface
	{
	public:
		static const std::string VarianceOriginFlag;

	public:
		static boost::shared_ptr<FiveLevelOEDMAnalyzers> create(void);

	private:
		FiveLevelOEDMAnalyzers(void) = default;
	public:
		FiveLevelOEDMAnalyzers(const FiveLevelOEDMAnalyzers &ano) = delete;
		FiveLevelOEDMAnalyzers(FiveLevelOEDMAnalyzers &&ano) = delete;
		FiveLevelOEDMAnalyzers &operator=(const FiveLevelOEDMAnalyzers &ano) = delete;
		FiveLevelOEDMAnalyzers &operator=(FiveLevelOEDMAnalyzers &&ano) = delete;
		~FiveLevelOEDMAnalyzers(void) = default;

		const std::string &category(void) const override;
		AnalyzerGroup generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const override;
	};
};
