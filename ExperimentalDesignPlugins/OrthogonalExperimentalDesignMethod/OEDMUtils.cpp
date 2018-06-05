#include "stdafx.h"
#include "OEDMUtils.h"
#include "TwoLevelOEDM.h"
#include "ThreeLevelOEDM.h"
#include "FourLevelOEDM.h"
#include "FiveLevelOEDM.h"
#include "TwoMultiLevelOEDM.h"
#include "ThreeMultiLevelOEDM.h"

#include <boost/make_shared.hpp>

namespace OEDM
{
	const std::string OEDMUtils::Name("OEDM");

	boost::shared_ptr<OEDMUtils> OEDMUtils::create(void)
	{
		static boost::shared_ptr<OEDMUtils> ret(new OEDMUtils());
		return ret;
	}

	const std::string &OEDMUtils::name(void) const
	{
		return Name;
	}

	const std::string &OEDMUtils::displayName(void) const
	{
		static const std::string ret("正交设计");
		return ret;
	}

	const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalDesignMethodInterface>> &OEDMUtils::methods(void) const
	{
		static const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalDesignMethodInterface>> ret =
		{
		};

		return ret;
	}

	boost::shared_ptr<OEDMAnalyzerUtils> OEDMAnalyzerUtils::create(void)
	{
		static boost::shared_ptr<OEDMAnalyzerUtils> ret(new OEDMAnalyzerUtils());
		return ret;
	}

	const std::string & OEDMAnalyzerUtils::name(void) const
	{
		return OEDMUtils::Name;
	}

	const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalAnalyzerInterface>>& OEDMAnalyzerUtils::analyzerGroups(void) const
	{
		static const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalAnalyzerInterface>> ret =
		{
		};

		return ret;
	}
};
