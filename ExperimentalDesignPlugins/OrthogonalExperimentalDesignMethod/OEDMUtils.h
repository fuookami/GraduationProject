#pragma once

#include "CARSDK/ExperimentalDesignMethodUtilsInterface.h"
#include "CARSDK/ExperimentalAnalyzerUtilsInterface.h"
#include <boost/dll/alias.hpp>
#include <boost/shared_ptr.hpp>

namespace OEDM
{
	class OEDMUtils : public CARSDK::IExperimentalDesignMethodUtilsInterface
	{
	public:
		static const std::string Name;
		static const std::string DisplayName;

	public:
		static boost::shared_ptr<OEDMUtils> create(void);

	private:
		OEDMUtils(void) = default;
	public:
		OEDMUtils(const OEDMUtils &ano) = delete;
		OEDMUtils(OEDMUtils &&ano) = delete;
		OEDMUtils &operator=(const OEDMUtils &rhs) = delete;
		OEDMUtils &operator=(OEDMUtils &&rhs) = delete;
		~OEDMUtils(void) = default;

		const std::string &name(void) const override;
		const std::string &displayName(void) const override;
		const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalDesignMethodInterface>> &methods(void) const override;
	};

	class OEDMAnalyzerUtils : public CARSDK::IExperimentalAnalyzerUtilsInterface
	{
	public:
		static boost::shared_ptr<OEDMAnalyzerUtils> create(void);

	private:
		OEDMAnalyzerUtils(void) = default;
	public:
		OEDMAnalyzerUtils(const OEDMAnalyzerUtils &ano) = delete;
		OEDMAnalyzerUtils(OEDMAnalyzerUtils &&ano) = delete;
		OEDMAnalyzerUtils &operator=(const OEDMAnalyzerUtils &rhs) = delete;
		OEDMAnalyzerUtils &operator=(OEDMAnalyzerUtils &&rhs) = delete;
		~OEDMAnalyzerUtils(void) = default;

		const std::string &name(void) const override;
		const std::string &displayName(void) const override;
		const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalAnalyzerInterface>> &analyzerGroups(void) const override;
	};
};

BOOST_DLL_ALIAS(OEDM::OEDMUtils::create, getEDMUtilsInterface);
BOOST_DLL_ALIAS(OEDM::OEDMAnalyzerUtils::create, getEAUtilsInterface);
