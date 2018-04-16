#include "ChineseNumberUtils.h"
#include <iostream>
#include <vector>
#include <locale>

typedef struct
{
	unsigned long num;
	std::wstring chnNumStr;
}TEST_DATA;

std::vector<TEST_DATA> testPair =
{
	{ 0, L"零" },
	{ 1, L"一" },
	{ 2, L"二" },
	{ 3, L"三" },
	{ 4, L"四" },
	{ 5, L"五" },
	{ 6, L"六" },
	{ 7, L"七" },
	{ 8, L"八" },
	{ 9, L"九" },
	{ 10, L"一十" },
	{ 11, L"一十一" },
	{ 110, L"一百一十" },
	{ 111, L"一百一十一" },
	{ 100, L"一百" },
	{ 102, L"一百零二" },
	{ 1020, L"一千零二十" },
	{ 1001, L"一千零一" },
	{ 1015, L"一千零一十五" },
	{ 1000, L"一千" },
	{ 10000, L"一万" },
	{ 20010, L"二万零一十" },
	{ 20001, L"二万零一" },
	{ 100000, L"一十万" },
	{ 1000000, L"一百万" },
	{ 10000000, L"一千万" },
	{ 100000000, L"一亿" },
	{ 1000000000, L"一十亿" },
	{ 1000001000, L"一十亿一千" },
	{ 1000000100, L"一十亿零一百" },
	{ 200010, L"二十万零一十" },
	{ 2000105, L"二百万零一百零五" },
	{ 20001007, L"二千万一千零七" },
	{ 2000100190, L"二十亿零一十万零一百九十" },
	{ 1040010000, L"一十亿四千零一万" },
	{ 200012301, L"二亿零一万二千三百零一" },
	{ 2005010010, L"二十亿零五百零一万零一十" },
	{ 4009060200, L"四十亿零九百零六万零二百" },
	{ 4294967295, L"四十二亿九千四百九十六万七千二百九十五" }
};

void testNumberToChinese()
{
	std::wstring chnNum;

	for (int i = 0, j(testPair.size()); i != j; ++i)
	{
		std::wstring str = SSUtils::ChineseNumber::toChineseNumber(testPair[i].num);
		std::wcout << testPair[i].num << ' ' << testPair[i].chnNumStr << ' ' << str << ' ' << std::boolalpha << (str == testPair[i].chnNumStr) << std::endl;
	}
}

void testChineseToNumber()
{
	for (int i = 0, j(testPair.size()); i != j; ++i)
	{
		unsigned int num = SSUtils::ChineseNumber::fromChineseNumber(testPair[i].chnNumStr);
		std::wcout << testPair[i].num << ' ' << testPair[i].chnNumStr << ' ' << num << ' ' << std::boolalpha << (num == testPair[i].num) << std::endl;
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
