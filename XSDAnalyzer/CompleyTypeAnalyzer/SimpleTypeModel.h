#pragma once

#include "StringType.h"
#include "NumberType.h"
#include "DateTimeType.h"
#include "DataType.h"
#include "ContainerType.h"

namespace XSDFrontend
{
	class SimpleTypeModel
	{
	public:
		SimpleTypeModel(void);
		SimpleTypeModel(const SimpleTypeModel &ano) = delete;
		SimpleTypeModel(const SimpleTypeModel &&ano) = delete;
		SimpleTypeModel &operator=(const SimpleTypeModel &rhs) = delete;
		SimpleTypeModel &operator=(const SimpleTypeModel &&rhs) = delete;
		~SimpleTypeModel(void);

		const std::shared_ptr<SimpleType::StringType> getStringType(const std::string &typeName) const;
		inline std::map<std::string, std::shared_ptr<SimpleType::StringType>> &getStringTypes(void) { return m_stringTypes; }
		inline const std::map<std::string, std::shared_ptr<SimpleType::StringType>> &getStringTypes(void) const { return m_stringTypes; }

		const std::shared_ptr<SimpleType::NumberType> getNumberType(const std::string &typeName) const;
		inline std::map<std::string, std::shared_ptr<SimpleType::NumberType>> &getNumberTypes(void) { return m_numberTypes; }
		inline const std::map<std::string, std::shared_ptr<SimpleType::NumberType>> &getNumberTypes(void) const { return m_numberTypes; }

		const std::shared_ptr<SimpleType::DateTimeType> getDateTimeType(const std::string &typeName) const;
		inline std::map<std::string, std::shared_ptr<SimpleType::DateTimeType>> &getDateTimeTypes(void) { return m_dateTimeTypes; }
		inline const std::map<std::string, std::shared_ptr<SimpleType::DateTimeType>> &getDateTimeTypes(void) const { return m_dateTimeTypes; }

		const std::shared_ptr<SimpleType::DataType> getDataType(const std::string &typeName) const;
		inline std::map<std::string, std::shared_ptr<SimpleType::DataType>> &getDataTypes(void) { return m_dataTypes; }
		inline const std::map<std::string, std::shared_ptr<SimpleType::DataType>> &getDataTypes(void) const { return m_dataTypes; }

		const std::shared_ptr<SimpleType::ContainerType> getContainerType(const std::string &typeName) const;
		inline std::map<std::string, std::shared_ptr<SimpleType::ContainerType>> &getContainerTypes(void) { return m_containerTypes; }
		inline const std::map<std::string, std::shared_ptr<SimpleType::ContainerType>> &getContainerTypes(void) const { return m_containerTypes; }

		const SimpleType::ISimpleTypeInterface *getSimpleType(const std::string &typeName) const;
		inline std::map<std::string, SimpleType::ISimpleTypeInterface *> &getSimpleTypes(void) { return m_simpleTypes; }
		inline const std::map<std::string, SimpleType::ISimpleTypeInterface *> &getSimpleTypes(void) const { return m_simpleTypes; }

		const XSDFrontend::SimpleType::eSimpleType getType(const std::string &typeName) const;
		inline const bool isTypeExist(const std::string &typeName) const { return getType(typeName) != XSDFrontend::SimpleType::eSimpleType::tNonExist; }
		static const bool isBaseType(const std::string &typeName);

		void checkAndEraseIlegalTypeInContainer(std::shared_ptr<XSDFrontend::SimpleType::ContainerType> type);

	public:
		static const std::string getNewDefaultName(void);

	private:
		std::map<std::string, std::shared_ptr<SimpleType::StringType>> m_stringTypes;
		std::map<std::string, std::shared_ptr<SimpleType::NumberType>> m_numberTypes;
		std::map<std::string, std::shared_ptr<SimpleType::DateTimeType>> m_dateTimeTypes;
		std::map<std::string, std::shared_ptr<SimpleType::DataType>> m_dataTypes;
		std::map<std::string, std::shared_ptr<SimpleType::ContainerType>> m_containerTypes;

		std::map<std::string, SimpleType::ISimpleTypeInterface *> m_simpleTypes;
	};
};
