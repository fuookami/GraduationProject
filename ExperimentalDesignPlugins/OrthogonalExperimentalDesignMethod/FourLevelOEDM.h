#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"
#include "CARSDK/ExperimentalAnalyzerInterface.h"

namespace OEDM
{
	class FourLevelOEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static const std::string Category;
		static const std::string TimeAttr;
		static const std::string ColumnAttr;
		static const std::string InteractionEffectAttr;

	public:
		static boost::shared_ptr<FourLevelOEDM> create(void);

	private:
		FourLevelOEDM(void) = default;
	public:
		FourLevelOEDM(const FourLevelOEDM &ano) = delete;
		FourLevelOEDM(FourLevelOEDM &&ano) = delete;
		FourLevelOEDM &operator=(const FourLevelOEDM &rhs) = delete;
		FourLevelOEDM &operator=(FourLevelOEDM &&rhs) = delete;
		~FourLevelOEDM(void) = default;

		const std::string &category(void) const override;
		const std::string &displayName(void) const override;
		const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> &neededAttributes(void) const override;
		const std::map<std::string, std::string> &factorNeededAttributes(void) const override;
		const bool valid(const std::map<std::string, std::string> &attributes) override;
		const bool valid(const std::map<std::string, std::string> &attributes, const CARSDK::DataModelingModule::FactorTypeGroup &factorTypeGroup) override;
		CARSDK::ExperimentalDesignTable generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel> &xsdModel, const std::map<std::string, std::string> &attributes) override;

	protected:
		CARSDK::ExperimentalDesignTable::Cell generateCell(const CARSDK::DataModelingModule::FactorType &info, const std::string &value = std::string("")) override;
	};

	class FourLevelOEDMAnalyzers : public CARSDK::IExperimentalAnalyzerInterface
	{
	public:
		static const std::string VarianceOriginFlag;

	public:
		static boost::shared_ptr<FourLevelOEDMAnalyzers> create(void);

	private:
		FourLevelOEDMAnalyzers(void) = default;
	public:
		FourLevelOEDMAnalyzers(const FourLevelOEDMAnalyzers &ano) = delete;
		FourLevelOEDMAnalyzers(FourLevelOEDMAnalyzers &&ano) = delete;
		FourLevelOEDMAnalyzers &operator=(const FourLevelOEDMAnalyzers &ano) = delete;
		FourLevelOEDMAnalyzers &operator=(FourLevelOEDMAnalyzers &&ano) = delete;
		~FourLevelOEDMAnalyzers(void) = default;

		const std::string &category(void) const override;
		AnalyzerGroup generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const override;
	};
};
