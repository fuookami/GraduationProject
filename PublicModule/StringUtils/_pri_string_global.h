#pragma once

#include "Global.h"
#include <map>

namespace SSUtils
{
	enum class CharType
	{
		UTF8,
		UTF16,
		BIG5,
		GBK,
		GB2312
	};

	namespace String
	{
		extern API_DECLSPEC const std::string EmptyString;

		extern API_DECLSPEC const std::string Empty;
		extern API_DECLSPEC const std::string Null;
		extern API_DECLSPEC const std::string None;

		extern API_DECLSPEC const std::string Right;
		extern API_DECLSPEC const std::string Error;
		extern API_DECLSPEC const std::string Wrong;

		extern API_DECLSPEC const std::string Enabled;
		extern API_DECLSPEC const std::string Disabled;

		extern API_DECLSPEC const std::string True;
		extern API_DECLSPEC const std::string False;

		extern API_DECLSPEC const std::string Infinity;
		extern API_DECLSPEC const std::string NegativeInfinity;
		extern API_DECLSPEC const std::string PositiveInfinity;
		extern API_DECLSPEC const std::string NotANumber;

		extern API_DECLSPEC const std::string SpaceCharacters;

		extern API_DECLSPEC const std::string HexStringPrefix;

		extern API_DECLSPEC const std::map<CharType, std::string> CharTypeCode;

		extern API_DECLSPEC const CharType LocalCharType;
		extern API_DECLSPEC const std::string LocalCharTypeCode;
	};
};
