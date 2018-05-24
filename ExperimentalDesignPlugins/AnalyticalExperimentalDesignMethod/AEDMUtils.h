#pragma once

#include "CARSDK/ExperimentalDesignMethodUtilsInterface.h"
#include <boost/dll/alias.hpp>

namespace AEDM
{
	const CARSDK::IExperimentalDesignMethodUtilsInterface * getEDMUtilsInterface(void);

	class AEDMUtils : public CARSDK::IExperimentalDesignMethodUtilsInterface
	{
	public:
		static std::shared_ptr<AEDMUtils> instance(void);

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
		const std::map<std::string, const CARSDK::IExperimentalDesignMethodInterface *> &methods(void) const override;
	};
};

BOOST_DLL_ALIAS(AEDM::getEDMUtilsInterface, getEDMUtilsInterface);
