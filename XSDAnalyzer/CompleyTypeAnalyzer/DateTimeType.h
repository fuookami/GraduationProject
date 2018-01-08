#pragma once

#include "SimpleTypeInterface.h"
#include "DateTimeUtils.h"

#include <map>
#include <set>
#include <memory>

namespace XSDFrontend
{
	namespace SimpleType
	{
		class DateTimeType : public ISimpleTypeInterface, 
			public ValueLimitConfiguration<DateTimeUtils::DateTime>, 
			public ValueEnumrationConfiguration<DateTimeUtils::DateTime>
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

		public:
			DateTimeType(void);
			DateTimeType(const std::string &name, const eBaseType baseType= eBaseType::tDateTime);
			DateTimeType(const std::string &&name, const eBaseType baseType= eBaseType::tDateTime);
			DateTimeType(const DateTimeType &ano);
			DateTimeType(const DateTimeType &&ano);
			DateTimeType &operator=(const DateTimeType &rhs);
			DateTimeType &operator=(const DateTimeType &&rhs);
			~DateTimeType(void);

			void refreshValidator(const XMLUtils::XMLNode &node) override;

			inline void setBaseType(const eBaseType baseType) { m_baseType = baseType; }
			inline const eBaseType getBaseType(void) const { return m_baseType; }

		private:
			eBaseType m_baseType;
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
