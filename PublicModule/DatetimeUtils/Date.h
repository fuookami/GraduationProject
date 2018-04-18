#pragma once

#include "_pri_datetime_global.h"

namespace SSUtils
{
	namespace Datetime
	{
		struct Date
		{
			static const Date EmptyDate;

			int16 year;
			uint8 month;
			uint8 day;

			Date(void);
			Date(const int16 _year, const uint8 _month, const uint8 _day);
			Date(const Date &ano) = default;
			Date(Date &&ano) = default;
			Date &operator=(const Date &rhs) = default;
			Date &operator=(Date &&rhs) = default;
			~Date(void) = default;

			inline Date &operator+=(const DateDuration &duration);
			inline Date &operator-=(const DateDuration &duration);

			inline Date getDateAfter(const DateDuration &duration) const;
			inline Date getDateBefore(const DateDuration &duration) const;

			inline const bool isLegalDate(void) const;
			inline const bool isLeapYear(void) const;
			inline const uint8 getDayOfMonth(void) const;
			inline const uint8 getDayInWeek(void) const;

			static inline Date fromString(const std::string &str);
			inline std::string toString(void) const;
		};

		struct DateDuration
		{
			int32 year;
			int32 month;
			int32 day;

			DateDuration(void);
			DateDuration(const int32 _day);
			DateDuration(const int32 _month, const int32 _day);
			DateDuration(const int32 _year, const int32 _month, const int32 _day);
			DateDuration(const DateDuration &ano) = default;
			DateDuration(DateDuration &&ano) = default;
			DateDuration &operator=(const DateDuration &rhs) = default;
			DateDuration &operator=(DateDuration &&rhs) = default;
			~DateDuration(void) = default;

			inline DateDuration &operator+=(const DateDuration &duration);
			inline DateDuration &operator-=(const DateDuration &duration);

			inline DateDuration operator+(void) const;
			inline DateDuration operator-(void) const;
		};

		Date getLocalDate(void);
		Date getDateAfterLocalDate(const DateDuration &duration);
		Date getDateBeforeLocalDate(const DateDuration &duration);

		const bool isLeapYear(const int16 year);
		const bool isLeapYear(const Date & date);

		const uint8 getDaysOfMonth(const int16 year, const uint8 month);
		const uint8 getDaysOfMonth(const Date &date);

		const uint8 getDayInWeek(const int16 year, const uint8 month, const uint8 day);
		const uint8 getDayInWeek(const Date &date);
	};
};

const bool operator<(const SSUtils::Datetime::Date &lhs, const SSUtils::Datetime::Date &rhs);
const bool operator<=(const SSUtils::Datetime::Date &lhs, const SSUtils::Datetime::Date &rhs);
const bool operator>(const SSUtils::Datetime::Date &lhs, const SSUtils::Datetime::Date &rhs);
const bool operator>=(const SSUtils::Datetime::Date &lhs, const SSUtils::Datetime::Date &rhs);
const bool operator==(const SSUtils::Datetime::Date &lhs, const SSUtils::Datetime::Date &rhs);
const bool operator!=(const SSUtils::Datetime::Date &lhs, const SSUtils::Datetime::Date &rhs);

const bool operator<(const SSUtils::Datetime::DateDuration &lhs, const SSUtils::Datetime::DateDuration &rhs);
const bool operator<=(const SSUtils::Datetime::DateDuration &lhs, const SSUtils::Datetime::DateDuration &rhs);
const bool operator>(const SSUtils::Datetime::DateDuration &lhs, const SSUtils::Datetime::DateDuration &rhs);
const bool operator>=(const SSUtils::Datetime::DateDuration &lhs, const SSUtils::Datetime::DateDuration &rhs);
const bool operator==(const SSUtils::Datetime::DateDuration &lhs, const SSUtils::Datetime::DateDuration &rhs);
const bool operator!=(const SSUtils::Datetime::DateDuration &lhs, const SSUtils::Datetime::DateDuration &rhs);

const SSUtils::Datetime::Date operator+(const SSUtils::Datetime::Date &lhs, const SSUtils::Datetime::DateDuration &rhs);
const SSUtils::Datetime::Date operator-(const SSUtils::Datetime::Date &lhs, const SSUtils::Datetime::DateDuration &rhs);
const SSUtils::Datetime::DateDuration operator-(const SSUtils::Datetime::Date &lhs, const SSUtils::Datetime::Date &rhs);

const SSUtils::Datetime::DateDuration operator+(const SSUtils::Datetime::DateDuration &lhs, const SSUtils::Datetime::DateDuration &rhs);
const SSUtils::Datetime::DateDuration operator-(const SSUtils::Datetime::DateDuration &lhs, const SSUtils::Datetime::DateDuration &rhs);

std::ostream &operator<<(std::ostream &os, const SSUtils::Datetime::Date &date);
std::istream &operator>>(std::istream &is, SSUtils::Datetime::Date &date);
