#pragma once

#include "CARSDK/ExperimentalDesignMethodUtilsInterface.h"
#include "CARSDK/ExperimentalAnalyzerUtilsInterface.h"
#include <boost/dll/alias.hpp>
#include <boost/shared_ptr.hpp>

namespace UEDM
{
	class UEDMUtils : public CARSDK::IExperimentalDesignMethodUtilsInterface
	{
	public:
		static const std::string Name;

	public:
		static boost::shared_ptr<UEDMUtils> create(void);

	private:
		UEDMUtils(void) = default;
	public:
		UEDMUtils(const UEDMUtils &ano) = delete;
		UEDMUtils(UEDMUtils &&ano) = delete;
		UEDMUtils &operator=(const UEDMUtils &rhs) = delete;
		UEDMUtils &operator=(UEDMUtils &&rhs) = delete;
		~UEDMUtils(void) = default;

		const std::string &name(void) const override;
		const std::string &displayName(void) const override;
		const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalDesignMethodInterface>> &methods(void) const override;
	};

	class UEDMAnalyzerUtils : public CARSDK::IExperimentalAnalyzerUtilsInterface
	{
	public:
		static boost::shared_ptr<UEDMAnalyzerUtils> create(void);

	private:
		UEDMAnalyzerUtils(void) = default;
	public:
		UEDMAnalyzerUtils(const UEDMAnalyzerUtils &ano) = delete;
		UEDMAnalyzerUtils(UEDMAnalyzerUtils &&ano) = delete;
		UEDMAnalyzerUtils &operator=(const UEDMAnalyzerUtils &rhs) = delete;
		UEDMAnalyzerUtils &operator=(UEDMAnalyzerUtils &&rhs) = delete;
		~UEDMAnalyzerUtils(void) = default;

		const std::string &name(void) const override;
		const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalAnalyzerInterface>> &analyzerGroups(void) const override;
	};
};

BOOST_DLL_ALIAS(UEDM::UEDMUtils::create, getEDMUtilsInterface);
BOOST_DLL_ALIAS(UEDM::UEDMAnalyzerUtils::create, getEAUtilsInterface);
