#pragma once

#include "CARSDKGlobal.h"
#include "ExperimentalDesignTable.h"

namespace CARSDK
{
	class CARSDK_API_DECLSPEC DataHandlingModule
	{
	public:
		static std::shared_ptr<DataHandlingModule> instance(void);
	
	private:
		DataHandlingModule(void) = default;
	public:
		DataHandlingModule(const DataHandlingModule &ano) = delete;
		DataHandlingModule(DataHandlingModule &&ano) = delete;
		DataHandlingModule &operator=(const DataHandlingModule &rhs) = delete;
		DataHandlingModule &operator=(DataHandlingModule &&rhs) = delete;
		~DataHandlingModule(void) = default;

		std::shared_ptr<SSUtils::XML::Node> normalize(const ExperimentalDesignTable &table) const;
		ExperimentalDesignTable analyze(const std::shared_ptr<SSUtils::XML::Node> data) const;
		const bool check(const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data) const;
		const bool check(const std::shared_ptr<XSDFrontend::XSDModel> mode, const ExperimentalDesignTable &table) const;
	};
};
