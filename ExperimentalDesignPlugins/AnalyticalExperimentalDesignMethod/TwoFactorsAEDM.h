#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"

namespace AEDM
{
	class TwoFactorsAEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static std::shared_ptr<TwoFactorsAEDM> instance(void);

	public:
		TwoFactorsAEDM(void) = default;
		TwoFactorsAEDM(const TwoFactorsAEDM &ano) = delete;
		TwoFactorsAEDM(TwoFactorsAEDM &&ano) = delete;
		TwoFactorsAEDM &operator=(const TwoFactorsAEDM &rhs) = delete;
		TwoFactorsAEDM &operator=(TwoFactorsAEDM &&rhs) = delete;
		~TwoFactorsAEDM(void) = default;

		const std::string &category(void) const override;
		const std::string &displayName(void) const override;
		std::map<std::string, std::string> neededAttributes(void) const override;
		const bool valid(const std::map<std::string, std::string> &attributes) const override;
		CARSDK::ExperimentalDesignTable generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel> &xsdModel, const std::map<std::string, std::string> &attributes) const override;
	};
};
