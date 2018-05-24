#include "stdafx.h"
#include "AEDMUtils.h"
#include "TwoFactorsAEDM.h"

namespace AEDM
{
	const CARSDK::IExperimentalDesignMethodUtilsInterface * getEDMUtilsInterface(void)
	{
		static auto instance(AEDM::AEDMUtils::instance());
		return dynamic_cast<const CARSDK::IExperimentalDesignMethodUtilsInterface *>(instance.get());
	}

	std::shared_ptr<AEDMUtils> AEDMUtils::instance(void)
	{
		static std::shared_ptr<AEDMUtils> ret(new AEDMUtils());
		return ret;
	}

	const std::string & AEDMUtils::name(void) const
	{
		static const std::string ret("AEDM");
		return ret;
	}

	const std::string & AEDMUtils::displayName(void) const
	{
		static const std::string ret("Œˆ“Ú…Ëº∆");
		return ret;
	}

	const std::map<std::string, const CARSDK::IExperimentalDesignMethodInterface *>& AEDMUtils::methods(void) const
	{
		static const std::map<std::string, const CARSDK::IExperimentalDesignMethodInterface *> ret = 
		{
			std::make_pair(TwoFactorsAEDM::instance()->category(), dynamic_cast<const CARSDK::IExperimentalDesignMethodInterface *>(TwoFactorsAEDM::instance().get()))
		};

		return ret;
	}
};
