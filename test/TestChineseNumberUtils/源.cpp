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
	{ SSUtils::Math::integer(0), L"��" },
	{ SSUtils::Math::integer(1), L"һ" },
	{ SSUtils::Math::integer(2), L"��" },
	{ SSUtils::Math::integer(3), L"��" },
	{ SSUtils::Math::integer(4), L"��" },
	{ SSUtils::Math::integer(5), L"��" },
	{ SSUtils::Math::integer(6), L"��" },
	{ SSUtils::Math::integer(7), L"��" },
	{ SSUtils::Math::integer(8), L"��" },
	{ SSUtils::Math::integer(9), L"��" },
	{ SSUtils::Math::integer(10), L"һʮ" },
	{ SSUtils::Math::integer(11), L"һʮһ" },
	{ SSUtils::Math::integer(110), L"һ��һʮ" },
	{ SSUtils::Math::integer(111), L"һ��һʮһ" },
	{ SSUtils::Math::integer(100), L"һ��" },
	{ SSUtils::Math::integer(102), L"һ�����" },
	{ SSUtils::Math::integer(1020), L"һǧ���ʮ" },
	{ SSUtils::Math::integer(1001), L"һǧ��һ" },
	{ SSUtils::Math::integer(1015), L"һǧ��һʮ��" },
	{ SSUtils::Math::integer(1000), L"һǧ" },
	{ SSUtils::Math::integer(10000), L"һ��" },
	{ SSUtils::Math::integer(20010), L"������һʮ" },
	{ SSUtils::Math::integer(20001), L"������һ" },
	{ SSUtils::Math::integer(100000), L"һʮ��" },
	{ SSUtils::Math::integer(1000000), L"һ����" },
	{ SSUtils::Math::integer(10000000), L"һǧ��" },
	{ SSUtils::Math::integer(100000000), L"һ��" },
	{ SSUtils::Math::integer(1000000000), L"һʮ��" },
	{ SSUtils::Math::integer(1000001000), L"һʮ��һǧ" },
	{ SSUtils::Math::integer(1000000100), L"һʮ����һ��" },
	{ SSUtils::Math::integer(200010), L"��ʮ����һʮ" },
	{ SSUtils::Math::integer(2000105), L"��������һ������" },
	{ SSUtils::Math::integer(20001007), L"��ǧ��һǧ����" },
	{ SSUtils::Math::integer(2000100190), L"��ʮ����һʮ����һ�پ�ʮ" },
	{ SSUtils::Math::integer(1040010000), L"һʮ����ǧ��һ��" },
	{ SSUtils::Math::integer(200012301), L"������һ���ǧ������һ" },
	{ SSUtils::Math::integer(2005010010), L"��ʮ���������һ����һʮ" },
	{ SSUtils::Math::integer(4009060200), L"��ʮ����Ű������������" },
	{ SSUtils::Math::integer(4294967295), L"��ʮ���ھ�ǧ�İپ�ʮ������ǧ���پ�ʮ��" }
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
