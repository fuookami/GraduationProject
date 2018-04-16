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
	{ 0, L"��" },
	{ 1, L"һ" },
	{ 2, L"��" },
	{ 3, L"��" },
	{ 4, L"��" },
	{ 5, L"��" },
	{ 6, L"��" },
	{ 7, L"��" },
	{ 8, L"��" },
	{ 9, L"��" },
	{ 10, L"һʮ" },
	{ 11, L"һʮһ" },
	{ 110, L"һ��һʮ" },
	{ 111, L"һ��һʮһ" },
	{ 100, L"һ��" },
	{ 102, L"һ�����" },
	{ 1020, L"һǧ���ʮ" },
	{ 1001, L"һǧ��һ" },
	{ 1015, L"һǧ��һʮ��" },
	{ 1000, L"һǧ" },
	{ 10000, L"һ��" },
	{ 20010, L"������һʮ" },
	{ 20001, L"������һ" },
	{ 100000, L"һʮ��" },
	{ 1000000, L"һ����" },
	{ 10000000, L"һǧ��" },
	{ 100000000, L"һ��" },
	{ 1000000000, L"һʮ��" },
	{ 1000001000, L"һʮ��һǧ" },
	{ 1000000100, L"һʮ����һ��" },
	{ 200010, L"��ʮ����һʮ" },
	{ 2000105, L"��������һ������" },
	{ 20001007, L"��ǧ��һǧ����" },
	{ 2000100190, L"��ʮ����һʮ����һ�پ�ʮ" },
	{ 1040010000, L"һʮ����ǧ��һ��" },
	{ 200012301, L"������һ���ǧ������һ" },
	{ 2005010010, L"��ʮ���������һ����һʮ" },
	{ 4009060200, L"��ʮ����Ű������������" },
	{ 4294967295, L"��ʮ���ھ�ǧ�İپ�ʮ������ǧ���پ�ʮ��" }
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
