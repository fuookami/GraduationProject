#pragma once

#include "CARSDKGlobal.h"
#include "SSUtils/XSD/XSDModel.h"
#include <boost/any.hpp>

namespace CARSDK
{
	class CARSDK_API_DECLSPEC DataModelingModule
	{
	public:
		static std::shared_ptr<DataModelingModule> instance(void);
		static const std::string BaesTypePrefix;
		static const std::string DescriptionInfo;
		struct Info
		{
			std::string name;
			std::string type;
			std::string experimentalFactorType;
			std::map<std::string, std::string> infos;
			std::map<std::string, boost::any> validators;
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

		std::shared_ptr<XSDFrontend::XSDModel> normalize(const std::vector<Info> &infos, std::shared_ptr<XSDFrontend::XSDModel> originModel = nullptr) const;
		std::vector<Info> analyze(const std::shared_ptr<XSDFrontend::XSDModel> model) const;

		inline const std::string &lastError(void) const { return m_lastError; }

	private:
		static std::shared_ptr<XSDFrontend::SimpleType::NumberType> loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::NumberType> type, const Info &info);
		static std::shared_ptr<XSDFrontend::SimpleType::StringType> loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::StringType> type, const Info &info);
		static std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> type, const Info &info);

		static Info saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::NumberType> type);
		static Info saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::StringType> type);
		static Info saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> type);

	private:
		std::string m_lastError;
	};
};
