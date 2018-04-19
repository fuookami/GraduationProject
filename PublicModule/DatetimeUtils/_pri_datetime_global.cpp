#include "_pri_datetime_global.h"

namespace SSUtils
{
	namespace Datetime
	{
		const std::array<unsigned char, 12> DaysOfMonth =
		{
			31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
		};

		const std::array<std::string, 12> MonthShortName =
		{
			std::string("Jan"), std::string("Feb"), std::string("Mar"),
			std::string("Apr"), std::string("May"), std::string("Jun"),
			std::string("Jul"), std::string("Aug"), std::string("Sep"),
			std::string("Oct"), std::string("Nov"), std::string("Dec")
		};

		const std::array<std::wstring, 7> DayInWeekChineseName =
		{
			std::wstring(L"������"), std::wstring(L"����һ"), std::wstring(L"���ڶ�"),
			std::wstring(L"������"), std::wstring(L"������"), std::wstring(L"������"),
			std::wstring(L"������")
		};

		const uint16 MillisecondsPerSecond = 1000;
		const uint16 MicrosecondsPerMillisecond = 1000;
		const uint16 SecondsPerHour = 3600;
		const uint8 SecondsPerMinute = 60;
		const uint8 MinutesPerHour = 60;
		const uint8 HoursPerDay = 24;

		const uint8 FractionSecondDigits = 6;
	};
};
