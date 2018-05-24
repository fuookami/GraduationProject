#include "stdafx.h"
#include "TwoFactorsAEDM.h"

namespace AEDM
{
	std::shared_ptr<TwoFactorsAEDM> TwoFactorsAEDM::instance(void)
	{
		static std::shared_ptr<TwoFactorsAEDM> ret(new TwoFactorsAEDM());
		return ret;
	}

	const std::string & TwoFactorsAEDM::category(void) const
	{
		static const std::string ret("TwoFactorAEDM");
		return ret;
	}

	const std::string & TwoFactorsAEDM::displayName(void) const
	{
		static const std::string ret("二因子析因设计方法");
		return ret;
	}

	std::map<std::string, std::string> TwoFactorsAEDM::neededAttributes(void) const
	{
		return std::map<std::string, std::string>();
	}

	const bool TwoFactorsAEDM::valid(const std::map<std::string, std::string>& attributes) const
	{
		return false;
	}

	CARSDK::ExperimentalDesignTable TwoFactorsAEDM::generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel>& xsdModel, const std::map<std::string, std::string>& attributes) const
	{
		return CARSDK::ExperimentalDesignTable();
	}
};
