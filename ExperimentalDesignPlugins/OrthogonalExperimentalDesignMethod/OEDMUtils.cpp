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
	const std::string OEDMUtils::DisplayName("正交设计");

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
		return DisplayName;
	}

	const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalDesignMethodInterface>> &OEDMUtils::methods(void) const
	{
		static const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalDesignMethodInterface>> ret =
		{
			make_method(TwoLevelOEDM::create()),
			make_method(ThreeLevelOEDM::create()),
			make_method(FourLevelOEDM::create()),
			make_method(FiveLevelOEDM::create()),
			make_method(TwoMultiLevelOEDM::create()),
			make_method(ThreeMultiLevelOEDM::create())
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

	const std::string & OEDMAnalyzerUtils::displayName(void) const
	{
		return OEDMUtils::DisplayName;
	}

	const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalAnalyzerInterface>>& OEDMAnalyzerUtils::analyzerGroups(void) const
	{
		static const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalAnalyzerInterface>> ret =
		{
			make_analyzers(TwoLevelOEDMAnalyzers::create()),
			make_analyzers(ThreeLevelOEDMAnalyzers::create()),
			make_analyzers(FourLevelOEDMAnalyzers::create()),
			make_analyzers(FiveLevelOEDMAnalyzers::create()),
			make_analyzers(TwoMultiLevelOEDMAnalyzers::create()),
			make_analyzers(ThreeMultiLevelOEDMAnalyzers::create()),
		};

		return ret;
	}
};
