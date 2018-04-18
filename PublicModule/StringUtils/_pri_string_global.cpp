#include "_pri_string_global.h"

#include <cctype>

namespace SSUtils
{
	namespace String
	{
		const std::string EmptyString("");

		const std::string Empty("empty");
		const std::string Null("null");
		const std::string None("none");

		const std::string Right("right");
		const std::string Error("error");
		const std::string Wrong("wrong");

		const std::string Enabled("enabled");
		const std::string Disabled("disabled");

		const std::string True("true");
		const std::string False("false");

		const std::map<CharType, std::string> CharTypeCode =
		{
			std::make_pair(CharType::UTF8, std::string("UTF-8")), 
			std::make_pair(CharType::UTF16, std::string("UTF-16")),
			std::make_pair(CharType::BIG5, std::string("BIG5")), 
			std::make_pair(CharType::GBK, std::string("GBK")), 
			std::make_pair(CharType::GB2312, std::string("GB2312"))
		};

		const std::string SpaceCharacters = []()
		{
			std::string ret;
			if (ret.empty())
			{
				for (int i(0); i != INT8_MAX; ++i)
				{
					if (isspace(i))
					{
						ret.push_back(static_cast<char>(i));
					}
				}
			}

			return ret;
		}();

#ifdef _WIN32
		const CharType LocalCharType = CharType::GB2312;
#else
		const CharType LocalCharType = CharType::UTF8;
#endif

		const std::string LocalCharTypeCode = CharTypeCode.find(LocalCharType)->second;
	};
};
