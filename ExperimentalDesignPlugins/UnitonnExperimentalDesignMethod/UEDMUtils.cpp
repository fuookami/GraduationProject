#include "stdafx.h"
#include "UEDMUtils.h"
#include "UEDM.h"

#include <boost/make_shared.hpp>

namespace UEDM
{
	const std::string UEDMUtils::Name("UEDM");
	const std::string UEDMUtils::DisplayName("æ˘‘»…Ëº∆");

	boost::shared_ptr<UEDMUtils> UEDMUtils::create(void)
	{
		static boost::shared_ptr<UEDMUtils> ret(new UEDMUtils());
		return ret;
	}

	const std::string &UEDMUtils::name(void) const
	{
		return Name;
	}

	const std::string &UEDMUtils::displayName(void) const
	{
		return DisplayName;
	}

	const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalDesignMethodInterface>> &UEDMUtils::methods(void) const
	{
		static const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalDesignMethodInterface>> ret = 
		{
			make_method(UEDM::create())
		};

		return ret;
	}

	boost::shared_ptr<UEDMAnalyzerUtils> UEDMAnalyzerUtils::create(void)
	{
		static boost::shared_ptr<UEDMAnalyzerUtils> ret(new UEDMAnalyzerUtils());
		return ret;
	}

	const std::string & UEDMAnalyzerUtils::name(void) const
	{
		return UEDMUtils::Name;
	}

	const std::string & UEDMAnalyzerUtils::displayName(void) const
	{
		return UEDMUtils::DisplayName;
	}

	const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalAnalyzerInterface>> &UEDMAnalyzerUtils::analyzerGroups(void) const
	{
		static const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalAnalyzerInterface>> ret =
		{
			make_analyzers(UEDMAnalyzers::create())
		};

		return ret;
	}
};
