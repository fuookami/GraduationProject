#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"
#include "CARSDK/ExperimentalAnalyzerInterface.h"

namespace OEDM
{
	class TwoLevelOEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static const std::string Category;
		static const std::string TimeAttr;
		static const std::string ColumnAttr;
		static const std::string InteractionEffectAttr;

	public:
		static boost::shared_ptr<TwoLevelOEDM> create(void);

	private:
		TwoLevelOEDM(void) = default;
	public:
		TwoLevelOEDM(const TwoLevelOEDM &ano) = delete;
		TwoLevelOEDM(TwoLevelOEDM &&ano) = delete;
		TwoLevelOEDM &operator=(const TwoLevelOEDM &rhs) = delete;
		TwoLevelOEDM &operator=(TwoLevelOEDM &&rhs) = delete;
		~TwoLevelOEDM(void) = default;

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

	class TwoLevelOEDMAnalyzers : public CARSDK::IExperimentalAnalyzerInterface
	{
	public:
		static const std::string VarianceOriginFlag;

	public:
		static boost::shared_ptr<TwoLevelOEDMAnalyzers> create(void);

	private:
		TwoLevelOEDMAnalyzers(void) = default;
	public:
		TwoLevelOEDMAnalyzers(const TwoLevelOEDMAnalyzers &ano) = delete;
		TwoLevelOEDMAnalyzers(TwoLevelOEDMAnalyzers &&ano) = delete;
		TwoLevelOEDMAnalyzers &operator=(const TwoLevelOEDMAnalyzers &ano) = delete;
		TwoLevelOEDMAnalyzers &operator=(TwoLevelOEDMAnalyzers &&ano) = delete;
		~TwoLevelOEDMAnalyzers(void) = default;

		const std::string &category(void) const override;
		AnalyzerGroup generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const override;
	};
};
