#pragma once

#include "Global.h"
#include <string>
#include <array>

namespace SSUtils
{
	namespace Datetime
	{
		extern const std::array<uint8, 12> DaysOfMonth;
		extern const std::array<std::string, 12> MonthShortName;
		extern const std::array<std::wstring, 7> DayInWeekChineseName;

		extern const uint16 MillisecondsPerSecond;
		extern const uint16 MicrosecondsPerMillisecond;
		extern const uint16 SecondsPerHour;
		extern const uint16 SecondsPerMinute;
		extern const uint16 MinutesPerHour;
		extern const uint16 HoursPerDay;

		struct Date;
		struct DateDuration;
		struct Time;
		struct TimeDuration;
		struct Datetime;
		struct DatetimeDuration;

		enum class Precision
		{
			Second,
			MicroSecond,
			MilliSecond
		};
	};
};
