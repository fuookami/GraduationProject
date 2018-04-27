#include "ChineseNumberUtils.h"
#include "FileUtils.h"
#include <iostream>
#include <vector>
#include <locale>
#include "MathUtils.h"

typedef struct
{
	SSUtils::Math::UInteger num;
	std::wstring chnNumStr;
}TEST_DATA;

std::vector<TEST_DATA> testPair =
{
	{ SSUtils::Math::UInteger(0), L"零" },
	{ SSUtils::Math::UInteger(1), L"一" },
	{ SSUtils::Math::UInteger(2), L"二" },
	{ SSUtils::Math::UInteger(3), L"三" },
	{ SSUtils::Math::UInteger(4), L"四" },
	{ SSUtils::Math::UInteger(5), L"五" },
	{ SSUtils::Math::UInteger(6), L"六" },
	{ SSUtils::Math::UInteger(7), L"七" },
	{ SSUtils::Math::UInteger(8), L"八" },
	{ SSUtils::Math::UInteger(9), L"九" },
	{ SSUtils::Math::UInteger(10), L"一十" },
	{ SSUtils::Math::UInteger(11), L"一十一" },
	{ SSUtils::Math::UInteger(110), L"一百一十" },
	{ SSUtils::Math::UInteger(111), L"一百一十一" },
	{ SSUtils::Math::UInteger(100), L"一百" },
	{ SSUtils::Math::UInteger(102), L"一百零二" },
	{ SSUtils::Math::UInteger(1020), L"一千零二十" },
	{ SSUtils::Math::UInteger(1001), L"一千零一" },
	{ SSUtils::Math::UInteger(1015), L"一千零一十五" },
	{ SSUtils::Math::UInteger(1000), L"一千" },
	{ SSUtils::Math::UInteger(10000), L"一万" },
	{ SSUtils::Math::UInteger(20010), L"二万零一十" },
	{ SSUtils::Math::UInteger(20001), L"二万零一" },
	{ SSUtils::Math::UInteger(100000), L"一十万" },
	{ SSUtils::Math::UInteger(1000000), L"一百万" },
	{ SSUtils::Math::UInteger(10000000), L"一千万" },
	{ SSUtils::Math::UInteger(100000000), L"一亿" },
	{ SSUtils::Math::UInteger(1000000000), L"一十亿" },
	{ SSUtils::Math::UInteger(1000001000), L"一十亿一千" },
	{ SSUtils::Math::UInteger(1000000100), L"一十亿零一百" },
	{ SSUtils::Math::UInteger(200010), L"二十万零一十" },
	{ SSUtils::Math::UInteger(2000105), L"二百万零一百零五" },
	{ SSUtils::Math::UInteger(20001007), L"二千万一千零七" },
	{ SSUtils::Math::UInteger(2000100190), L"二十亿零一十万零一百九十" },
	{ SSUtils::Math::UInteger(1040010000), L"一十亿四千零一万" },
	{ SSUtils::Math::UInteger(200012301), L"二亿零一万二千三百零一" },
	{ SSUtils::Math::UInteger(2005010010), L"二十亿零五百零一万零一十" },
	{ SSUtils::Math::UInteger(4009060200), L"四十亿零九百零六万零二百" },
	{ SSUtils::Math::UInteger(4294967295), L"四十二亿九千四百九十六万七千二百九十五" }
};

void testNumberToChinese()
{
	std::wstring chnNum;

	for (int i = 0, j(testPair.size()); i != j; ++i)
	{
		std::wstring str = SSUtils::ChineseNumber::toChineseNumber(testPair[i].num.toUInt32());
		std::wcout << testPair[i].num.toUInt32() << ' ' << testPair[i].chnNumStr << ' ' << str << ' ' << std::boolalpha << (str == testPair[i].chnNumStr) << std::endl;
	}
}

void testChineseToNumber()
{
	for (int i = 0, j(testPair.size()); i != j; ++i)
	{
		unsigned int num = SSUtils::ChineseNumber::fromChineseNumber(testPair[i].chnNumStr);
		std::wcout << testPair[i].num.toUInt32() << ' ' << testPair[i].chnNumStr << ' ' << num << ' ' << std::boolalpha << (num == testPair[i].num.value()) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	std::wcout.imbue(std::locale("chs"));
	testNumberToChinese();
	testChineseToNumber();
	system("pause");

	return 0;
}
