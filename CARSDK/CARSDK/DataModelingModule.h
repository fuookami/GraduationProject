#pragma once

#include "CARSDKGlobal.h"
#include "SSUtils/XSD/XSDModel.h"

namespace CARSDK
{
	class CARSDK_API_DECLSPEC DataModelingModule
	{
	public:
		static std::shared_ptr<DataModelingModule> instance(void);
		struct Info
		{
			std::string name;
			std::string type;
			std::string experimentalFactorType;
			std::map<std::string, std::string> infos;
			std::map<std::string, std::string> validators;
			std::map<std::string, std::string> attributes;
		};

	private:
		DataModelingModule(void) = default;
	public:
		DataModelingModule(const DataModelingModule &ano) = delete;
		DataModelingModule(DataModelingModule &&ano) = delete;
		DataModelingModule &operator=(const DataModelingModule &rhs) = delete;
		DataModelingModule &operator=(DataModelingModule &&rhs) = delete;
		~DataModelingModule(void) = default;

		std::shared_ptr<XSDFrontend::XSDModel> normalize(const std::vector<Info> &infos, const std::shared_ptr<XSDFrontend::XSDModel> originModel) const;
		std::vector<Info> analyze(const std::shared_ptr<XSDFrontend::XSDModel> model) const;
	};
};
