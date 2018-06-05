#pragma once

#include "CARSDKGlobal.h"
#include "ExperimentalDesignTable.h"
#include <boost/any.hpp>

namespace CARSDK
{
	class CARSDK_API_DECLSPEC DataModelingModule
	{
	public:
		static std::shared_ptr<DataModelingModule> instance(void);
		static const std::string BaesTypePrefix;
		static const std::string DescriptionInfo;

		using NumberEnumContainer = std::vector<SSUtils::Math::Real>;
		using StringEnumContainer = std::vector<std::string>;
		using DatetimeEnumContainer = std::vector<SSUtils::Datetime::DatetimeDuration>;

	public:
		static const int getEnumNumber(const FactorType &factor);
		static std::vector<std::string> getEnumString(const FactorType &factor);
		static FactorTypeGroup divideToGroup(const std::vector<FactorType> &infos);

	private:
		DataModelingModule(void) = default;
	public:
		DataModelingModule(const DataModelingModule &ano) = delete;
		DataModelingModule(DataModelingModule &&ano) = delete;
		DataModelingModule &operator=(const DataModelingModule &rhs) = delete;
		DataModelingModule &operator=(DataModelingModule &&rhs) = delete;
		~DataModelingModule(void) = default;

		std::shared_ptr<XSDFrontend::XSDModel> normalize(const std::vector<FactorType> &infos, std::shared_ptr<XSDFrontend::XSDModel> originModel = nullptr);
		std::shared_ptr<XSDFrontend::XSDModel> normalizeWithPublicModel(const std::vector<FactorType> &infos, const std::shared_ptr<XSDFrontend::XSDModel> publicModel, std::shared_ptr<XSDFrontend::XSDModel> originModel = nullptr);
		std::vector<FactorType> analyze(const std::shared_ptr<XSDFrontend::XSDModel> model);
		std::vector<FactorType> analyzeForData(const std::shared_ptr<XSDFrontend::XSDModel> model);

		inline const std::string &lastError(void) const { return m_lastError; }

	private:
		static std::shared_ptr<XSDFrontend::SimpleType::NumberType> loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::NumberType> type, const FactorType &info);
		static std::shared_ptr<XSDFrontend::SimpleType::StringType> loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::StringType> type, const FactorType &info);
		static std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> loadSimpleType(std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> type, const FactorType &info);

		static FactorType saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::NumberType> type);
		static FactorType saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::StringType> type);
		static FactorType saveSimpleType(const std::shared_ptr<XSDFrontend::SimpleType::DatetimeType> type);

	private:
		std::string m_lastError;
	};
};
