#pragma once

#include "SimpleTypeInterface.h"
#include "DateTimeUtils.h"

#include <map>
#include <set>
#include <memory>

namespace XSDAnalyzer
{
	namespace SimpleType
	{
		class DateTimeType : public ISimpleTypeInterface
		{
		public:
			enum class eBaseType
			{
				tDate,
				tTime,
				tDateTime,
				gYear,
				gYearMonth,
				gMonth,
				gMonthDay,
				gDay,
				tDuration
			};
			using ValueType = DateTimeUtils::DateTime;
			static const ValueType NoValueValidator;

		private:
			struct DateTime
			{
				bool enabled;
				ValueType value;

				DateTime(void);
				DateTime(const DateTime &ano);
				DateTime(const DateTime &&ano);
				DateTime &operator=(const DateTime &rhs);
				DateTime &operator=(const DateTime &&rhs);
				~DateTime(void);

				void set(const ValueType &_value);
				void set(const ValueType &&_value);
				void clear(void);
			};

			struct _ValueTypeCompare
			{
				const bool operator()(const ValueType &lhs, const ValueType &rhs) const;
			};

		public:
			DateTimeType(void);
			DateTimeType(const std::string &name, const eBaseType baseType= eBaseType::tDateTime);
			DateTimeType(const std::string &&name, const eBaseType baseType= eBaseType::tDateTime);
			DateTimeType(const DateTimeType &ano);
			DateTimeType(const DateTimeType &&ano);
			DateTimeType &operator=(const DateTimeType &rhs);
			DateTimeType &operator=(const DateTimeType &&rhs);
			~DateTimeType(void);

			void refreshValidator(const boost::property_tree::ptree &root) override;

			inline void setBaseType(const eBaseType baseType) { m_baseType = baseType; }
			inline const eBaseType getBaseType(void) const { return m_baseType; }

			void setMaxExclusive(const ValueType &maxExclusive);
			void setMaxExclusive(const ValueType &&maxExclusive);
			inline void removeMaxExclusive(void) { m_maxExclusive.clear(); }
			inline const bool hasMaxExclusive(void) const { return m_maxExclusive.enabled; }
			inline const ValueType &getMaxExclusive(void) const { return m_maxExclusive.value; }

			void setMaxInclusive(const ValueType &maxInclusive);
			void setMaxInclusive(const ValueType &&maxInclusive);
			inline void removeMaxInclusive(void) { m_maxInclusive.clear(); }
			inline const bool hasMaxInclusive(void) const { return m_maxInclusive.enabled; }
			inline const ValueType &getMaxInclusive(void) const { return m_maxInclusive.value; }

			void setMinExclusive(const ValueType &minExclusive);
			void setMinExclusive(const ValueType &&minExclusive);
			inline void removeMinExclusive(void) { m_minExclusive.clear(); }
			inline const bool hasMinExclusive(void) const { return m_minExclusive.enabled; }
			inline const ValueType &getMinExclusive(void) const { return m_minExclusive.value; }

			void setMinInclusive(const ValueType &minInclusive);
			void setMinInclusive(const ValueType &&minInclusive);
			inline void removeMinInclusive(void) { m_minInclusive.clear(); }
			inline const bool hasMinInclusive(void) const { return m_minInclusive.enabled; }
			inline const ValueType &getMinInclusive(void) const { return m_minInclusive.value; }

			inline void setIsEnum(const bool isEnum) { m_isEnum = isEnum; }
			inline const bool getIsEnum(void) const { return m_isEnum; }

			inline void addEnumValue(const ValueType &enumValue) { m_enumValues.insert(enumValue); }
			inline void addEnumValue(const ValueType &&enumValue) { m_enumValues.insert(std::move(enumValue)); }
			inline void eraseEnumValue(const ValueType &enumValue) { m_enumValues.erase(enumValue); }
			inline void clearEnumValue(void) { m_enumValues.clear(); }
			inline const bool hasEnumValue(const ValueType &enumValue) const { return m_enumValues.find(enumValue) != m_enumValues.cend(); }
			inline const std::set<ValueType, _ValueTypeCompare> &getEnumValues(void) const { return m_enumValues; }

		private:
			eBaseType m_baseType;

			DateTime m_maxExclusive;
			DateTime m_maxInclusive;
			DateTime m_minExclusive;
			DateTime m_minInclusive;

			bool m_isEnum;
			std::set<ValueType, _ValueTypeCompare> m_enumValues;
		};

		static const std::map<std::string, DateTimeType::eBaseType> DateTimeBaseTypeName2Type =
		{
			std::make_pair(std::string("date"), DateTimeType::eBaseType::tDate),
			std::make_pair(std::string("time"), DateTimeType::eBaseType::tTime),
			std::make_pair(std::string("dateTime"), DateTimeType::eBaseType::tDateTime),
			std::make_pair(std::string("gYear"), DateTimeType::eBaseType::gYear),
			std::make_pair(std::string("gYearMonth"), DateTimeType::eBaseType::gYearMonth),
			std::make_pair(std::string("gMonth"), DateTimeType::eBaseType::gMonth),
			std::make_pair(std::string("gMonthDay"), DateTimeType::eBaseType::gMonthDay),
			std::make_pair(std::string("gDay"), DateTimeType::eBaseType::gDay),
			std::make_pair(std::string("duration"), DateTimeType::eBaseType::tDuration)
		};
	};
};
