#pragma once

#include "Global.h"
#include <string>

namespace SSUtils
{
	namespace ChineseNumber
	{
		API_DECLSPEC std::wstring toChineseNumber(uint32 num);
		API_DECLSPEC uint32 fromChineseNumber(const std::wstring &str);
	};
};
