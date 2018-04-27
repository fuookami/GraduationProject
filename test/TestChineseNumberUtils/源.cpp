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
	{ SSUtils::Math::UInteger(0), L"��" },
	{ SSUtils::Math::UInteger(1), L"һ" },
	{ SSUtils::Math::UInteger(2), L"��" },
	{ SSUtils::Math::UInteger(3), L"��" },
	{ SSUtils::Math::UInteger(4), L"��" },
	{ SSUtils::Math::UInteger(5), L"��" },
	{ SSUtils::Math::UInteger(6), L"��" },
	{ SSUtils::Math::UInteger(7), L"��" },
	{ SSUtils::Math::UInteger(8), L"��" },
	{ SSUtils::Math::UInteger(9), L"��" },
	{ SSUtils::Math::UInteger(10), L"һʮ" },
	{ SSUtils::Math::UInteger(11), L"һʮһ" },
	{ SSUtils::Math::UInteger(110), L"һ��һʮ" },
	{ SSUtils::Math::UInteger(111), L"һ��һʮһ" },
	{ SSUtils::Math::UInteger(100), L"һ��" },
	{ SSUtils::Math::UInteger(102), L"һ�����" },
	{ SSUtils::Math::UInteger(1020), L"һǧ���ʮ" },
	{ SSUtils::Math::UInteger(1001), L"һǧ��һ" },
	{ SSUtils::Math::UInteger(1015), L"һǧ��һʮ��" },
	{ SSUtils::Math::UInteger(1000), L"һǧ" },
	{ SSUtils::Math::UInteger(10000), L"һ��" },
	{ SSUtils::Math::UInteger(20010), L"������һʮ" },
	{ SSUtils::Math::UInteger(20001), L"������һ" },
	{ SSUtils::Math::UInteger(100000), L"һʮ��" },
	{ SSUtils::Math::UInteger(1000000), L"һ����" },
	{ SSUtils::Math::UInteger(10000000), L"һǧ��" },
	{ SSUtils::Math::UInteger(100000000), L"һ��" },
	{ SSUtils::Math::UInteger(1000000000), L"һʮ��" },
	{ SSUtils::Math::UInteger(1000001000), L"һʮ��һǧ" },
	{ SSUtils::Math::UInteger(1000000100), L"һʮ����һ��" },
	{ SSUtils::Math::UInteger(200010), L"��ʮ����һʮ" },
	{ SSUtils::Math::UInteger(2000105), L"��������һ������" },
	{ SSUtils::Math::UInteger(20001007), L"��ǧ��һǧ����" },
	{ SSUtils::Math::UInteger(2000100190), L"��ʮ����һʮ����һ�پ�ʮ" },
	{ SSUtils::Math::UInteger(1040010000), L"һʮ����ǧ��һ��" },
	{ SSUtils::Math::UInteger(200012301), L"������һ���ǧ������һ" },
	{ SSUtils::Math::UInteger(2005010010), L"��ʮ���������һ����һʮ" },
	{ SSUtils::Math::UInteger(4009060200), L"��ʮ����Ű������������" },
	{ SSUtils::Math::UInteger(4294967295), L"��ʮ���ھ�ǧ�İپ�ʮ������ǧ���پ�ʮ��" }
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
