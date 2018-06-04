#pragma once

#include "CARSDKGlobal.h"
#include "ExperimentalDesignTable.h"
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
			XSDFrontend::SimpleType::eSimpleType simpleType;
			std::map<std::string, std::string> infos;
			std::map<std::string, boost::any> validators;
			std::map<std::string, std::string> attributes;
		};
		using NumberEnumContainer = std::vector<SSUtils::Math::Real>;
		using StringEnumContainer = std::vector<std::string>;
		using DatetimeEnumContainer = std::vector<SSUtils::Datetime::DatetimeDuration>;

		using FactorType = DataModelingModule::Info;
		struct FactorTypeGroup
		{
			std::vector<std::reference_wrapper<const FactorType>> experimentalFactors;
			std::vector<std::reference_wrapper<const FactorType>> evaluateFactor;
			std::vector<std::reference_wrapper<const FactorType>> notEvaluateFactor;
		};

	public:
		static const int getEnumNumber(const DataModelingModule::FactorType &factor);
		static std::vector<std::string> getEnumString(const DataModelingModule::FactorType &factor);
		static DataModelingModule::FactorTypeGroup divideToGroup(const std::vector<DataModelingModule::FactorType> &infos);

	private:
		DataModelingModule(void) = default;
	public:
		DataModelingModule(const DataModelingModule &ano) = delete;
		DataModelingModule(DataModelingModule &&ano) = delete;
		DataModelingModule &operator=(const DataModelingModule &rhs) = delete;
		DataModelingModule &operator=(DataModelingModule &&rhs) = delete;
		~DataModelingModule(void) = default;

		std::shared_ptr<XSDFrontend::XSDModel> normalize(const std::vector<Info> &infos, std::shared_ptr<XSDFrontend::XSDModel> originModel = nullptr);
		std::shared_ptr<XSDFrontend::XSDModel> normalizeWithPublicModel(const std::vector<Info> &infos, const std::shared_ptr<XSDFrontend::XSDModel> publicModel, std::shared_ptr<XSDFrontend::XSDModel> originModel = nullptr);
		std::vector<Info> analyze(const std::shared_ptr<XSDFrontend::XSDModel> model);
		std::vector<Info> analyzeForDesignMethod(const std::shared_ptr<XSDFrontend::XSDModel> model);

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
