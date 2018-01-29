#pragma once

#include "SimpleTypeInterface.h"
#include "DatetimeUtils.h"

#include <map>
#include <set>
#include <memory>

namespace XSDFrontend
{
	namespace SimpleType
	{
		class DatetimeType : public ISimpleTypeInterface, 
			public ValueLimitConfiguration<DatetimeUtils::DatetimeMs>, 
			public ValueEnumrationConfiguration<DatetimeUtils::DatetimeMs>
		{
		public:
			enum class eBaseType
			{
				tDate,
				tTime,
				tDatetime,
				gYear,
				gYearMonth,
				gMonth,
				gMonthDay,
				gDay,
				tDuration
			};

		public:
			DatetimeType(void);
			DatetimeType(const std::string &name, const eBaseType baseType= eBaseType::tDatetime);
			DatetimeType(std::string &&name, const eBaseType baseType= eBaseType::tDatetime);
			DatetimeType(const DatetimeType &ano) = default;
			DatetimeType(DatetimeType &&ano) = default;
			DatetimeType &operator=(const DatetimeType &rhs) = default;
			DatetimeType &operator=(DatetimeType &&rhs) = default;
			~DatetimeType(void) = default;

			void refreshValidator(const XMLUtils::XMLNode &node) override;

			inline void setBaseType(const eBaseType baseType) { m_baseType = baseType; }
			inline const eBaseType getBaseType(void) const { return m_baseType; }

		private:
			eBaseType m_baseType;
		};

		static const std::map<std::string, DatetimeType::eBaseType> DatetimeBaseTypeName2Type =
		{
			std::make_pair(std::string("date"), DatetimeType::eBaseType::tDate),
			std::make_pair(std::string("time"), DatetimeType::eBaseType::tTime),
			std::make_pair(std::string("dateTime"), DatetimeType::eBaseType::tDatetime),
			std::make_pair(std::string("gYear"), DatetimeType::eBaseType::gYear),
			std::make_pair(std::string("gYearMonth"), DatetimeType::eBaseType::gYearMonth),
			std::make_pair(std::string("gMonth"), DatetimeType::eBaseType::gMonth),
			std::make_pair(std::string("gMonthDay"), DatetimeType::eBaseType::gMonthDay),
			std::make_pair(std::string("gDay"), DatetimeType::eBaseType::gDay),
			std::make_pair(std::string("duration"), DatetimeType::eBaseType::tDuration)
		};
	};
};
