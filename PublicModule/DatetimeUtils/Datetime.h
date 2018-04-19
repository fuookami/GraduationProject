#pragma once

#include "Date.h"
#include "Time.h"

namespace SSUtils
{
	namespace Datetime
	{
		struct Datetime : public Date
		{
		public:
			static const Datetime EmptyDatetime;

			Datetime(void);
			Datetime(const int16 year, const uint8 month, const uint8 day, const int32 hour, const uint8 minute, const uint8 second, const uint16 millisecond = 0, const uint16 microsecond = 0);
			Datetime(const Date &date, const uint32 second);
			Datetime(const Date &date, const int32 hour, const uint8 minute, const uint8 second, const uint16 millisecond = 0, const uint16 microsecond = 0);
			Datetime(const int16 year, const uint8 month, const uint8 day, const Time &time);
			Datetime(const Date &date);
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

			inline const bool isTomorrow(void) const;
			inline const bool isTheDayAfterTomorrow(void) const;
			inline const bool isTheDaysAfter(void) const;

			inline const bool isYesterday(void) const;
			inline const bool isTheDayBeforeYesterday(void) const;
			inline const bool isTheDaysBefore(void) const;

			static Datetime fromString(const std::string &str);
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

		struct DatetimeDuration : public DateDuration
		{
		public:
			DatetimeDuration(void);
			DatetimeDuration(const int32 year, const int32 month, const int32 day, const int32 hour, const int32 minute, const int32 second, const int32 millisecond = 0, const int32 microsecond = 0);
			DatetimeDuration(const DateDuration &dateDuration, const uint32 second);
			DatetimeDuration(const DateDuration &dateDuration, const int32 hour, const int32 minute, const int32 second, const int32 millisecond = 0, const int32 microsecond = 0);
			DatetimeDuration(const int32 day, const TimeDuration &timeDuration);
			DatetimeDuration(const int32 month, const int32 day, const TimeDuration &timeDuration);
			DatetimeDuration(const int32 year, const int32 month, const int32 day, const TimeDuration &timeDuration);
			DatetimeDuration(const DateDuration &dateDuration);
			DatetimeDuration(const DateDuration &dateDuration, const TimeDuration &timeDuration);
			DatetimeDuration(const TimeDuration &timeDuration);
			DatetimeDuration(const DatetimeDuration &ano) = default;
			DatetimeDuration(DatetimeDuration &&ano) = default;
			DatetimeDuration &operator=(const DatetimeDuration &rhs) = default;
			DatetimeDuration &operator=(DatetimeDuration &&rhs) = default;
			~DatetimeDuration(void) = default;

			static inline DatetimeDuration fromTimeDuration(const TimeDuration &timeDuration);
			inline TimeDuration toTimeDuration(void) const;

			inline DatetimeDuration &operator+=(const DatetimeDuration &duration);
			inline DatetimeDuration &operator-=(const DatetimeDuration &duration);
			
			inline DatetimeDuration operator+(void) const;
			inline DatetimeDuration operator-(void) const;

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

			void tidy(void);

		private:
			int32 m_hour;
			int32 m_minute;
			int32 m_second;
			int32 m_millisecond;
			int32 m_microsecond;
			Precision m_precision;
		};

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

std::ostream &operator<<(std::ostream &os, const SSUtils::Datetime::Datetime &datetime);
