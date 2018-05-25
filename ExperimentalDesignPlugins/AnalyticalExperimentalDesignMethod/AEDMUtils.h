#pragma once

#include "CARSDK/ExperimentalDesignMethodUtilsInterface.h"
#include "CARSDK/ExperimentalAnalyzerUtilsInterface.h"
#include <boost/dll/alias.hpp>
#include <boost/shared_ptr.hpp>

namespace AEDM
{
	class AEDMUtils : public CARSDK::IExperimentalDesignMethodUtilsInterface
	{
	public:
		static const std::string Name;

	public:
		static boost::shared_ptr<AEDMUtils> create(void);

	private:
		AEDMUtils(void) = default;
	public:
		AEDMUtils(const AEDMUtils &ano) = delete;
		AEDMUtils(AEDMUtils &&ano) = delete;
		AEDMUtils &operator=(const AEDMUtils &rhs) = delete;
		AEDMUtils &operator=(AEDMUtils &&rhs) = delete;
		~AEDMUtils(void) = default;

		const std::string &name(void) const override;
		const std::string &displayName(void) const override;
		const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalDesignMethodInterface>> &methods(void) const override;
	};

	class AEDMAnalyzerUtils : public CARSDK::IExperimentalAnalyzerUtilsInterface
	{
	public:
		static boost::shared_ptr<AEDMAnalyzerUtils> create(void);

	private:
		AEDMAnalyzerUtils(void) = default;
	public:
		AEDMAnalyzerUtils(const AEDMAnalyzerUtils &ano) = delete;
		AEDMAnalyzerUtils(AEDMAnalyzerUtils &&ano) = delete;
		AEDMAnalyzerUtils &operator=(const AEDMAnalyzerUtils &rhs) = delete;
		AEDMAnalyzerUtils &operator=(AEDMAnalyzerUtils &&rhs) = delete;
		~AEDMAnalyzerUtils(void) = default;

		const std::string &name(void) const override;
		const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalAnalyzerInterface>> &analyzerGroups(void) const override;
	};
};

BOOST_DLL_ALIAS(AEDM::AEDMUtils::create, getEDMUtilsInterface);
BOOST_DLL_ALIAS(AEDM::AEDMAnalyzerUtils::create, getEAUtilsInterface);
