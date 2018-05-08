#pragma once

#include "SimpleTypeInterface.h"
#include "DatetimeUtils.h"

#include <map>
#include <set>
#include <memory>
#include <boost/variant.hpp>

namespace XSDFrontend
{
	namespace SimpleType
	{
		class DatetimeType : public ISimpleTypeInterface, 
			public ValueLimitConfiguration<SSUtils::Datetime::DatetimeDuration>,
			public ValueEnumrationConfiguration<SSUtils::Datetime::DatetimeDuration>
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

			const bool refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node) override;

			void setBaseType(const eBaseType baseType);
			inline const eBaseType getBaseType(void) const { return m_baseType; }

		private:
			eBaseType m_baseType;
		};

		extern const std::map<std::string, DatetimeType::eBaseType> DatetimeBaseTypeName2Type;

		SSUtils::Datetime::DatetimeDuration XSDString2Datetime(const DatetimeType::eBaseType type, const std::string &str);
	};
};
