#pragma once

#include "Global.h"
#include <string>
#include <array>

namespace SSUtils
{
	namespace Datetime
	{
		extern API_DECLSPEC const std::array<uint8, 12> DaysOfMonth;
		extern API_DECLSPEC const std::array<std::string, 12> MonthShortName;
		extern API_DECLSPEC const std::array<std::wstring, 7> DayInWeekChineseName;

		extern API_DECLSPEC const uint16 MillisecondsPerSecond;
		extern API_DECLSPEC const uint16 MicrosecondsPerMillisecond;
		extern API_DECLSPEC const uint16 SecondsPerHour;
		extern API_DECLSPEC const uint8 SecondsPerMinute;
		extern API_DECLSPEC const uint8 MinutesPerHour;
		extern API_DECLSPEC const uint8 HoursPerDay;

		extern API_DECLSPEC const uint8 FractionSecondDigits;
		extern API_DECLSPEC const uint32 MicrosecondPerFractionSecond;

		class Date;
		class DateDuration;
		class Time;
		class TimeDuration;
		class Datetime;
		class DatetimeDuration;

		enum class Precision
		{
			Second,
			MicroSecond,
			MilliSecond
		};
	};
};
