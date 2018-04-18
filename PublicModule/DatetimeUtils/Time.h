#pragma once

#include "_pri_datetime_global.h"

namespace SSUtils
{
	namespace Datetime
	{
		struct Time
		{
			int8 hour;
			uint8 minute;
			uint8 second;
			uint16 microsecond;
			uint16 millisecond;
			Precision precision;

			Time(void);
			Time(const uint32 _second);
			Time(const uint16 _hour, const uint8 _minute, const uint8 _second, const uint16 _microsecond = 0, const uint16 _millisecond = 0);
			Time(const Time &ano) = default;
			Time(Time &&ano) = default;
			Time &operator=(const Time &rhs) = default;
			Time &operator=(Time &&rhs) = default;
			~Time(void) = default;

			static inline Time fromMicrosecond(const uint32 _microsecond);
			static inline Time fromMillisecond(const uint32 _millisecond);

			inline Time &operator+=(const TimeDuration &duration);
			inline Time &operator-=(const TimeDuration &duration);

			inline Time getTimeAfter(const TimeDuration &duration) const;
			inline Time getTimeBefore(const TimeDuration &duration) const;

			inline const int64 totalMilliseconds(void) const;
			inline const int64 totalMicroseconds(void) const;
			inline const int32 totalSeconds(void) const;
			inline const int32 totalMinutes(void) const;
			inline const int32 totalHours(void) const;
			inline const int32 totalDays(void) const;

			inline const bool isTomorrow(void) const;
			inline const bool isTheDayAfterTomorrow(void) const;
			inline const bool isTheDaysAfter(void) const;

			inline const bool isYesterday(void) const;
			inline const bool isTheDayBeforeYesterday(void) const;
			inline const bool isTheDaysBefore(void) const;

			static inline Time fromString(const std::string &str);;
			inline std::string toString(void) const;

			void tidy(void);
		};

		struct TimeDuration
		{
			int32 hour;
			int32 minute;
			int32 second;
			int32 microsecond;
			int32 millisecond;
			Precision precision;

			TimeDuration(void);
			TimeDuration(const int32 _second);
			TimeDuration(const int32 _hour, const int32 _minute, const int32 _second, const int32 _microsecond = 0, const int32 _millisecond = 0);
			TimeDuration(const TimeDuration &ano) = default;
			TimeDuration(TimeDuration &&ano) = default;
			TimeDuration &operator=(const TimeDuration &rhs) = default;
			~TimeDuration(void) = default;

			static inline TimeDuration fromMicrosecond(const uint32 _microsecond);
			static inline TimeDuration fromMillisecond(const uint32 _millisecond);

			inline TimeDuration &operator+=(const TimeDuration &duration);
			inline TimeDuration &operator-=(const TimeDuration &duration);

			inline TimeDuration operator+(void) const;
			inline TimeDuration operator-(void) const;

			inline const int64 totalMilliseconds(void) const;
			inline const int64 totalMicroseconds(void) const;
			inline const int32 totalSeconds(void) const;
			inline const int32 totalMinutes(void) const;
			inline const int32 totalHours(void) const;
			inline const int32 totalDays(void) const;

			void tidy(void);
		};

		Time getLocalTime(void);
		Time getTimeAfterLocalTime(const TimeDuration &duration);
		Time getTimeBeforeLocalTime(const TimeDuration &duration);
	};
};

const bool operator<(const SSUtils::Datetime::Time &lhs, const SSUtils::Datetime::Time &rhs);
const bool operator<=(const SSUtils::Datetime::Time &lhs, const SSUtils::Datetime::Time &rhs);
const bool operator>(const SSUtils::Datetime::Time &lhs, const SSUtils::Datetime::Time &rhs);
const bool operator>=(const SSUtils::Datetime::Time &lhs, const SSUtils::Datetime::Time &rhs);
const bool operator==(const SSUtils::Datetime::Time &lhs, const SSUtils::Datetime::Time &rhs);
const bool operator!=(const SSUtils::Datetime::Time &lhs, const SSUtils::Datetime::Time &rhs);

const bool operator<(const SSUtils::Datetime::TimeDuration &lhs, const SSUtils::Datetime::TimeDuration &rhs);
const bool operator<=(const SSUtils::Datetime::TimeDuration &lhs, const SSUtils::Datetime::TimeDuration &rhs);
const bool operator>(const SSUtils::Datetime::TimeDuration &lhs, const SSUtils::Datetime::TimeDuration &rhs);
const bool operator>=(const SSUtils::Datetime::TimeDuration &lhs, const SSUtils::Datetime::TimeDuration &rhs);
const bool operator==(const SSUtils::Datetime::TimeDuration &lhs, const SSUtils::Datetime::TimeDuration &rhs);
const bool operator!=(const SSUtils::Datetime::TimeDuration &lhs, const SSUtils::Datetime::TimeDuration &rhs);

const SSUtils::Datetime::Time operator+(const SSUtils::Datetime::Time &lhs, const SSUtils::Datetime::TimeDuration &rhs);
const SSUtils::Datetime::Time operator-(const SSUtils::Datetime::Time &lhs, const SSUtils::Datetime::TimeDuration &rhs);
const SSUtils::Datetime::TimeDuration operator-(const SSUtils::Datetime::Time &lhs, const SSUtils::Datetime::Time &rhs);

const SSUtils::Datetime::TimeDuration operator+(const SSUtils::Datetime::TimeDuration &lhs, const SSUtils::Datetime::TimeDuration &rhs);
const SSUtils::Datetime::TimeDuration operator-(const SSUtils::Datetime::TimeDuration &lhs, const SSUtils::Datetime::TimeDuration &rhs);

std::ostream &operator<<(std::ostream &os, const SSUtils::Datetime::Time &date);
std::istream &operator>>(std::istream &is, SSUtils::Datetime::Time &date);
