#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"
#include "CARSDK/ExperimentalAnalyzerInterface.h"

namespace UEDM
{
	class UEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static const std::string Category;
		static const std::string TimeAttr;
		static const std::string LevelAttr;
		static const std::string ColumnAttr;
		static const std::string InteractionEffectAttr;

	public:
		static boost::shared_ptr<UEDM> create(void);

	private:
		UEDM(void) = default;
	public:
		UEDM(const UEDM &ano) = delete;
		UEDM(UEDM &&ano) = delete;
		UEDM &operator=(const UEDM &rhs) = delete;
		UEDM &operator=(UEDM &&rhs) = delete;
		~UEDM(void) = default;
		
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

	class UEDMAnalyzers : public CARSDK::IExperimentalAnalyzerInterface
	{
	public:
		static const std::string VarianceOriginFlag;

	public:
		static boost::shared_ptr<UEDMAnalyzers> create(void);

	private:
		UEDMAnalyzers(void) = default;
	public:
		UEDMAnalyzers(const UEDMAnalyzers &ano) = delete;
		UEDMAnalyzers(UEDMAnalyzers &&ano) = delete;
		UEDMAnalyzers &operator=(const UEDMAnalyzers &ano) = delete;
		UEDMAnalyzers &operator=(UEDMAnalyzers &&ano) = delete;
		~UEDMAnalyzers(void) = default;

		const std::string &category(void) const override;
		AnalyzerGroup generateAnalyzerGroup(const std::shared_ptr<XSDFrontend::XSDModel> model) const override;
	};
};
