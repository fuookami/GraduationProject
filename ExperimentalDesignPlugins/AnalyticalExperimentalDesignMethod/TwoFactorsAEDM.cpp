#include "stdafx.h"
#include "TwoFactorsAEDM.h"

namespace AEDM
{
	boost::shared_ptr<TwoFactorsAEDM> TwoFactorsAEDM::create(void)
	{
		return boost::shared_ptr<TwoFactorsAEDM>(new TwoFactorsAEDM());
	}
	const std::string &TwoFactorsAEDM::category(void) const
	{
		static const std::string ret("TwoFactorAEDM");
		return ret;
	}

	const std::string &TwoFactorsAEDM::displayName(void) const
	{
		static const std::string ret("二因子析因设计方法");
		return ret;
	}

	const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> &TwoFactorsAEDM::neededAttributes(void) const
	{
		static const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> ret = {};
		return ret;
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
