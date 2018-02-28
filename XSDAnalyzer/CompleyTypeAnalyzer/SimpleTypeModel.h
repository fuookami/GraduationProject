#pragma once

#include "StringType.h"
#include "NumberType.h"
#include "DatetimeType.h"
#include "DataType.h"
#include "ContainerType.h"

namespace XSDFrontend
{
	class SimpleTypeModel
	{
	public:
		SimpleTypeModel(void) = default;
		SimpleTypeModel(const SimpleTypeModel &ano) = delete;
		SimpleTypeModel(SimpleTypeModel &&ano) = delete;
		SimpleTypeModel &operator=(const SimpleTypeModel &rhs) = delete;
		SimpleTypeModel &operator=(SimpleTypeModel &&rhs) = delete;
		~SimpleTypeModel(void) = default;

		std::shared_ptr<SimpleType::StringType> getStringType(const std::string &typeName);
		const std::shared_ptr<SimpleType::StringType> getStringType(const std::string &typeName) const;
		inline std::map<std::string, std::shared_ptr<SimpleType::StringType>> &getStringTypes(void) { return m_stringTypes; }
		inline const std::map<std::string, std::shared_ptr<SimpleType::StringType>> &getStringTypes(void) const { return m_stringTypes; }

		std::shared_ptr<SimpleType::NumberType> getNumberType(const std::string &typeName);
		const std::shared_ptr<SimpleType::NumberType> getNumberType(const std::string &typeName) const;
		inline std::map<std::string, std::shared_ptr<SimpleType::NumberType>> &getNumberTypes(void) { return m_numberTypes; }
		inline const std::map<std::string, std::shared_ptr<SimpleType::NumberType>> &getNumberTypes(void) const { return m_numberTypes; }

		std::shared_ptr<SimpleType::DatetimeType> getDatetimeType(const std::string &typeName);
		const std::shared_ptr<SimpleType::DatetimeType> getDatetimeType(const std::string &typeName) const;
		inline std::map<std::string, std::shared_ptr<SimpleType::DatetimeType>> &getDatetimeTypes(void) { return m_datetimeTypes; }
		inline const std::map<std::string, std::shared_ptr<SimpleType::DatetimeType>> &getDatetimeTypes(void) const { return m_datetimeTypes; }

		std::shared_ptr<SimpleType::DataType> getDataType(const std::string &typeName);
		const std::shared_ptr<SimpleType::DataType> getDataType(const std::string &typeName) const;
		inline std::map<std::string, std::shared_ptr<SimpleType::DataType>> &getDataTypes(void) { return m_dataTypes; }
		inline const std::map<std::string, std::shared_ptr<SimpleType::DataType>> &getDataTypes(void) const { return m_dataTypes; }

		std::shared_ptr<SimpleType::ContainerType> getContainerType(const std::string &typeName);
		const std::shared_ptr<SimpleType::ContainerType> getContainerType(const std::string &typeName) const;
		inline std::map<std::string, std::shared_ptr<SimpleType::ContainerType>> &getContainerTypes(void) { return m_containerTypes; }
		inline const std::map<std::string, std::shared_ptr<SimpleType::ContainerType>> &getContainerTypes(void) const { return m_containerTypes; }

		SimpleType::ISimpleTypeInterface *getSimpleType(const std::string &typeName);
		const SimpleType::ISimpleTypeInterface *getSimpleType(const std::string &typeName) const;
		inline std::map<std::string, SimpleType::ISimpleTypeInterface *> &getSimpleTypes(void) { return m_simpleTypes; }
		inline const std::map<std::string, SimpleType::ISimpleTypeInterface *> &getSimpleTypes(void) const { return m_simpleTypes; }

		const XSDFrontend::SimpleType::eSimpleType getType(const std::string &typeName) const;
		inline const bool isTypeExist(const std::string &typeName) const { return isSimpleType(typeName) || isBaseType(typeName); }
		static const bool isBaseType(const std::string &typeName);
		inline const bool isSimpleType(const std::string &typeName) const { return getType(typeName) != XSDFrontend::SimpleType::eSimpleType::tNonExist; }

		inline const bool hasToken(const std::string &token) { return isTypeExist(token); }
		inline void clear(void) { m_stringTypes.clear(); m_numberTypes.clear(); m_datetimeTypes.clear(); m_dataTypes.clear(); m_containerTypes.clear(); m_simpleTypes.clear(); }

		void checkAndEraseIlegalTypeInContainer(std::shared_ptr<XSDFrontend::SimpleType::ContainerType> type);

	public:
		std::string getNewDefaultSimpleTypeName(void) const;

	private:
		std::map<std::string, std::shared_ptr<SimpleType::StringType>> m_stringTypes;
		std::map<std::string, std::shared_ptr<SimpleType::NumberType>> m_numberTypes;
		std::map<std::string, std::shared_ptr<SimpleType::DatetimeType>> m_datetimeTypes;
		std::map<std::string, std::shared_ptr<SimpleType::DataType>> m_dataTypes;
		std::map<std::string, std::shared_ptr<SimpleType::ContainerType>> m_containerTypes;

		std::map<std::string, SimpleType::ISimpleTypeInterface *> m_simpleTypes;
	};
};
