#include "ChineseNumberUtils.h"
#include "FileUtils.h"
#include <iostream>
#include <vector>
#include <locale>
#include "MathUtils.h"

typedef struct
{
	SSUtils::Math::integer num;
	std::wstring chnNumStr;
}TEST_DATA;

std::vector<TEST_DATA> testPair =
{
	{ SSUtils::Math::integer(0), L"零" },
	{ SSUtils::Math::integer(1), L"一" },
	{ SSUtils::Math::integer(2), L"二" },
	{ SSUtils::Math::integer(3), L"三" },
	{ SSUtils::Math::integer(4), L"四" },
	{ SSUtils::Math::integer(5), L"五" },
	{ SSUtils::Math::integer(6), L"六" },
	{ SSUtils::Math::integer(7), L"七" },
	{ SSUtils::Math::integer(8), L"八" },
	{ SSUtils::Math::integer(9), L"九" },
	{ SSUtils::Math::integer(10), L"一十" },
	{ SSUtils::Math::integer(11), L"一十一" },
	{ SSUtils::Math::integer(110), L"一百一十" },
	{ SSUtils::Math::integer(111), L"一百一十一" },
	{ SSUtils::Math::integer(100), L"一百" },
	{ SSUtils::Math::integer(102), L"一百零二" },
	{ SSUtils::Math::integer(1020), L"一千零二十" },
	{ SSUtils::Math::integer(1001), L"一千零一" },
	{ SSUtils::Math::integer(1015), L"一千零一十五" },
	{ SSUtils::Math::integer(1000), L"一千" },
	{ SSUtils::Math::integer(10000), L"一万" },
	{ SSUtils::Math::integer(20010), L"二万零一十" },
	{ SSUtils::Math::integer(20001), L"二万零一" },
	{ SSUtils::Math::integer(100000), L"一十万" },
	{ SSUtils::Math::integer(1000000), L"一百万" },
	{ SSUtils::Math::integer(10000000), L"一千万" },
	{ SSUtils::Math::integer(100000000), L"一亿" },
	{ SSUtils::Math::integer(1000000000), L"一十亿" },
	{ SSUtils::Math::integer(1000001000), L"一十亿一千" },
	{ SSUtils::Math::integer(1000000100), L"一十亿零一百" },
	{ SSUtils::Math::integer(200010), L"二十万零一十" },
	{ SSUtils::Math::integer(2000105), L"二百万零一百零五" },
	{ SSUtils::Math::integer(20001007), L"二千万一千零七" },
	{ SSUtils::Math::integer(2000100190), L"二十亿零一十万零一百九十" },
	{ SSUtils::Math::integer(1040010000), L"一十亿四千零一万" },
	{ SSUtils::Math::integer(200012301), L"二亿零一万二千三百零一" },
	{ SSUtils::Math::integer(2005010010), L"二十亿零五百零一万零一十" },
	{ SSUtils::Math::integer(4009060200), L"四十亿零九百零六万零二百" },
	{ SSUtils::Math::integer(4294967295), L"四十二亿九千四百九十六万七千二百九十五" }
};

void testNumberToChinese()
{
	std::wstring chnNum;

	for (int i = 0, j(testPair.size()); i != j; ++i)
	{
		std::wstring str = SSUtils::ChineseNumber::toChineseNumber(testPair[i].num.getUInt32());
		std::wcout << testPair[i].num.getUInt32() << ' ' << testPair[i].chnNumStr << ' ' << str << ' ' << std::boolalpha << (str == testPair[i].chnNumStr) << std::endl;
	}
}

void testChineseToNumber()
{
	for (int i = 0, j(testPair.size()); i != j; ++i)
	{
		unsigned int num = SSUtils::ChineseNumber::fromChineseNumber(testPair[i].chnNumStr);
		std::wcout << testPair[i].num.getUInt32() << ' ' << testPair[i].chnNumStr << ' ' << num << ' ' << std::boolalpha << (num == testPair[i].num.value()) << std::endl;
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
