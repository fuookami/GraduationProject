#include "stdafx.h"
#include "AEDMUtils.h"
#include "TwoFactorsAEDM.h"

#include <boost/make_shared.hpp>

namespace AEDM
{
	const std::string AEDMUtils::Name("AEDM");

	boost::shared_ptr<AEDMUtils> AEDMUtils::create(void)
	{
		static boost::shared_ptr<AEDMUtils> ret(new AEDMUtils());
		return ret;
	}

	const std::string &AEDMUtils::name(void) const
	{
		return Name;
	}

	const std::string &AEDMUtils::displayName(void) const
	{
		static const std::string ret("Œˆ“Ú…Ëº∆");
		return ret;
	}

	const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalDesignMethodInterface>> &AEDMUtils::methods(void) const
	{
		static const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalDesignMethodInterface>> ret = 
		{
			make_method(TwoFactorsAEDM::create())
		};

		return ret;
	}

	boost::shared_ptr<AEDMAnalyzerUtils> AEDMAnalyzerUtils::create(void)
	{
		static boost::shared_ptr<AEDMAnalyzerUtils> ret(new AEDMAnalyzerUtils());
		return ret;
	}

	const std::string & AEDMAnalyzerUtils::name(void) const
	{
		return AEDMUtils::Name;
	}

	const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalAnalyzerInterface>>& AEDMAnalyzerUtils::analyzerGroups(void) const
	{
		static const std::map<std::string, boost::shared_ptr<CARSDK::IExperimentalAnalyzerInterface>> ret =
		{
			make_analyzers(TwoFactorsAEDMAnalyzers::create())
		};

		return ret;
	}
};
