#pragma once

#include "_pri_datetime_global.h"

namespace SSUtils
{
	namespace Datetime
	{
		class Time
		{
		public:
			Time(void);
			Time(const int32 second);
			Time(const int32 hour, const uint8 minute, const uint8 second, const uint16 millisecond = 0, const uint16 microsecond = 0);
			Time(const Time &ano) = default;
			Time(Time &&ano) = default;
			Time &operator=(const Time &rhs) = default;
			Time &operator=(Time &&rhs) = default;
			~Time(void) = default;

			static inline Time fromMillisecond(const int32 millisecond);
			static inline Time fromMicrosecond(const int32 microsecond);

			inline Time &operator+=(const TimeDuration &duration);
			inline Time &operator-=(const TimeDuration &duration);

			inline Time getTimeAfter(const TimeDuration &duration) const;
			inline Time getTimeBefore(const TimeDuration &duration) const;

			inline const int32 hour(void) const;
			inline void setHour(const int32 hour);
			inline const uint8 minute(void) const;
			inline void setMinute(const uint8 minute);
			inline const uint8 second(void) const;
			inline void setSecond(const uint8 second);
			inline const uint16 millisecond(void) const;
			inline void setMillisecond(const uint16 millisecond);
			inline const uint16 microsecond(void) const;
			inline void setMicrosecond(const uint16 microsecond);
			inline const Precision precision(void)const;
			inline void setPrecision(const Precision precision);
			inline const uint32 fractionsecond(void) const;

			inline const int64 totalMicroseconds(void) const;
			inline const int64 totalMilliseconds(void) const;
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

			static Time fromString(const std::string &str);;
			std::string toString(void) const;

			void tidy(void);

		private:
			int32 m_hour;
			uint8 m_minute;
			uint8 m_second;
			uint16 m_millisecond;
			uint16 m_microsecond;
			Precision m_precision;
		};

		class TimeDuration
		{
		public:
			TimeDuration(void);
			TimeDuration(const int32 _second);
			TimeDuration(const int32 _hour, const int32 _minute, const int32 _second, const int32 _millisecond = 0, const int32 _microsecond = 0);
			TimeDuration(const DatetimeDuration &datetimeDuration);
			TimeDuration(const TimeDuration &ano) = default;
			TimeDuration(TimeDuration &&ano) = default;
			TimeDuration &operator=(const TimeDuration &rhs) = default;
			~TimeDuration(void) = default;

			static inline TimeDuration fromMillisecond(const int32 millisecond);
			static inline TimeDuration fromMicrosecond(const int32 microsecond);
			static inline TimeDuration fromDatetimeDuration(const DatetimeDuration &datetimeDuration);
			inline DatetimeDuration toDatetimeDuration(void) const;

			inline TimeDuration &operator+=(const TimeDuration &duration);
			inline TimeDuration &operator-=(const TimeDuration &duration);

			inline TimeDuration operator+(void) const;
			inline TimeDuration operator-(void) const;

			inline const int32 hour(void) const;
			inline void setHour(const int32 hour);
			inline const int32 minute(void) const;
			inline void setMinute(const int32 minute);
			inline const int32 second(void) const;
			inline void setSecond(const int32 second);
			inline const int32 millisecond(void) const;
			inline void setMillisecond(const int32 millisecond);
			inline const int32 microsecond(void) const;
			inline void setMicrosecond(const int32 microsecond);
			inline const Precision precision(void)const;
			inline void setPrecision(const Precision precision);
			inline const int32 fractionsecond(void) const;

			inline const int64 totalMicroseconds(void) const;
			inline const int64 totalMilliseconds(void) const;
			inline const int32 totalSeconds(void) const;
			inline const int32 totalMinutes(void) const;
			inline const int32 totalHours(void) const;
			inline const int32 totalDays(void) const;

			void tidy(void);

		private:
			int32 m_hour;
			int32 m_minute;
			int32 m_second;
			int32 m_millisecond;
			int32 m_microsecond;
			Precision m_precision;
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

std::ostream &operator<<(std::ostream &os, const SSUtils::Datetime::Time &time);
