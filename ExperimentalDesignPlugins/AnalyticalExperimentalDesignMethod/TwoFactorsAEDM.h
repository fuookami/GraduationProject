#pragma once

#include "CARSDK/ExperimentalDesignMethodInterface.h"

namespace AEDM
{
	class TwoFactorsAEDM : public CARSDK::IExperimentalDesignMethodInterface
	{
	public:
		static boost::shared_ptr<TwoFactorsAEDM> create(void);

	private:
		TwoFactorsAEDM(void) = default;
	public:
		TwoFactorsAEDM(const TwoFactorsAEDM &ano) = delete;
		TwoFactorsAEDM(TwoFactorsAEDM &&ano) = delete;
		TwoFactorsAEDM &operator=(const TwoFactorsAEDM &rhs) = delete;
		TwoFactorsAEDM &operator=(TwoFactorsAEDM &&rhs) = delete;
		~TwoFactorsAEDM(void) = default;

		const std::string &category(void) const override;
		const std::string &displayName(void) const override;
		const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> &neededAttributes(void) const override;
		const bool valid(const std::map<std::string, std::string> &attributes) const override;
		CARSDK::ExperimentalDesignTable generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel> &xsdModel, const std::map<std::string, std::string> &attributes) const override;
	};
};
