#pragma once

#include "Date.h"
#include "Time.h"

namespace SSUtils
{
	namespace Datetime
	{
		struct Datetime : public Date, public Time
		{
			static const Datetime EmptyDatetime;

			Datetime(void);
			Datetime(const int16 _year, const uint8 _month, const uint8 _day, const uint16 _hour, const uint8 _minute, const uint8 _second, const uint16 _microsecond = 0, const uint16 _millisecond = 0);
			Datetime(const Date &date, const uint32 _second);
			Datetime(const Date &date, const uint16 _hour, const uint8 _minute, const uint8 _second, const uint16 _microsecond = 0, const uint16 _millisecond = 0);
			Datetime(const int16 _year, const uint8 _month, const uint8 _day, const Time &time);
			Datetime(const Date &date, const Time &time);
			Datetime(const Datetime &ano) = default;
			Datetime(Datetime &&ano) = default;
			Datetime &operator=(const Datetime &rhs) = default;
			Datetime &operator=(Datetime &&rhs) = default;
			~Datetime(void) = default;

			inline Datetime &operator+=(const DatetimeDuration &duration);
			inline Datetime &operator-=(const DatetimeDuration &duration);

			inline Datetime getDatetimeAfter(const DatetimeDuration &duration) const;
			inline Datetime getDatetimeBefore(const DatetimeDuration &duration) const;

			static inline Date fromString(const std::string &str);
			inline std::string toString(void) const;

			void tidy(void);
		};

		struct DatetimeDuration : public DateDuration, public TimeDuration
		{
			DatetimeDuration(void);
			DatetimeDuration(const int32 _year, const int32 _month, const int32 _day, const int32 _hour, const int32 _minute, const int32 _second, const int32 _microsecond = 0, const int32 _millisecond = 0);
			DatetimeDuration(const DateDuration &dateDuration, const uint32 _second);
			DatetimeDuration(const DateDuration &dateDuration, const int32 _hour, const int32 _minute, const int32 _second, const int32 _microsecond = 0, const int32 _millisecond = 0);
			DatetimeDuration(const int32 _day, const TimeDuration &timeDuration);
			DatetimeDuration(const int32 _month, const int32 _day, const TimeDuration &timeDuration);
			DatetimeDuration(const int32 _year, const int32 _month, const int32 _day, const TimeDuration &timeDuration);
			DatetimeDuration(const DatetimeDuration &ano) = default;
			DatetimeDuration(DatetimeDuration &&ano) = default;
			DatetimeDuration &operator=(const DatetimeDuration &rhs) = default;
			DatetimeDuration &operator=(DatetimeDuration &rhs) = default;
			~DatetimeDuration(void);

			inline DatetimeDuration &operator+=(const DatetimeDuration &duration);
			inline DatetimeDuration &operator-=(const DatetimeDuration &duration);
			
			inline DatetimeDuration operator+(void) const;
			inline DatetimeDuration operator-(void) const;

			void tidy(void);
		};

		Datetime getBuildDatetime(const std::string &BuildOriginalDateString, const std::string &BuildTimeString);

		Datetime getLocalDatetime(void);
		Datetime getDatetimeAfterLocalDatetime(const DatetimeDuration &duration);
		Datetime getDatetimeBeforeLocalDatetime(const DatetimeDuration &duration);
	};
};

const bool operator<(const SSUtils::Datetime::Datetime &lhs, const SSUtils::Datetime::Datetime &rhs);
const bool operator<=(const SSUtils::Datetime::Datetime &lhs, const SSUtils::Datetime::Datetime &rhs);
const bool operator>(const SSUtils::Datetime::Datetime &lhs, const SSUtils::Datetime::Datetime &rhs);
const bool operator>=(const SSUtils::Datetime::Datetime &lhs, const SSUtils::Datetime::Datetime &rhs);
const bool operator==(const SSUtils::Datetime::Datetime &lhs, const SSUtils::Datetime::Datetime &rhs);
const bool operator!=(const SSUtils::Datetime::Datetime &lhs, const SSUtils::Datetime::Datetime &rhs);

const bool operator<(const SSUtils::Datetime::DatetimeDuration &lhs, const SSUtils::Datetime::DatetimeDuration &rhs);
const bool operator<=(const SSUtils::Datetime::DatetimeDuration &lhs, const SSUtils::Datetime::DatetimeDuration &rhs);
const bool operator>(const SSUtils::Datetime::DatetimeDuration &lhs, const SSUtils::Datetime::DatetimeDuration &rhs);
const bool operator>=(const SSUtils::Datetime::DatetimeDuration &lhs, const SSUtils::Datetime::DatetimeDuration &rhs);
const bool operator==(const SSUtils::Datetime::DatetimeDuration &lhs, const SSUtils::Datetime::DatetimeDuration &rhs);
const bool operator!=(const SSUtils::Datetime::DatetimeDuration &lhs, const SSUtils::Datetime::DatetimeDuration &rhs);

const SSUtils::Datetime::Datetime operator+(const SSUtils::Datetime::Datetime &lhs, const SSUtils::Datetime::DatetimeDuration &rhs);
const SSUtils::Datetime::Datetime operator-(const SSUtils::Datetime::Datetime &lhs, const SSUtils::Datetime::DatetimeDuration &rhs);
const SSUtils::Datetime::DatetimeDuration operator-(const SSUtils::Datetime::Datetime &lhs, const SSUtils::Datetime::Datetime &rhs);

const SSUtils::Datetime::DatetimeDuration operator+(const SSUtils::Datetime::DatetimeDuration &lhs, const SSUtils::Datetime::DatetimeDuration &rhs);
const SSUtils::Datetime::DatetimeDuration operator-(const SSUtils::Datetime::DatetimeDuration &lhs, const SSUtils::Datetime::DatetimeDuration &rhs);

std::ostream &operator<<(std::ostream &os, const SSUtils::Datetime::Datetime &date);
std::istream &operator>>(std::istream &is, SSUtils::Datetime::Datetime &date);
