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
			std::wstring(L"星期日"), std::wstring(L"星期一"), std::wstring(L"星期二"),
			std::wstring(L"星期三"), std::wstring(L"星期四"), std::wstring(L"星期五"),
			std::wstring(L"星期六")
		};

		const unsigned short MillisecondsPerSecond = 1000;
		const unsigned short MicrosecondsPerMillisecond = 1000;
		const unsigned short SecondsPerHour = 3600;
		const unsigned short SecondsPerMinute = 60;
		const unsigned short MinutesPerHour = 60;
		const unsigned short HoursPerDay = 24;
	};
};
