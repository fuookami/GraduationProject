#pragma once

#include "StringUtils/_pri_string_global.h"
#include "StringUtils/StringConverter.h"
#include "StringUtils/StringRegexChecker.h"
#include "StringUtils/StringTranslator.h"
#include <numeric>

namespace SSUtils
{
	namespace String
	{
		API_DECLSPEC std::string getVersion(const int major, const int sub, const int modify);

		API_DECLSPEC std::string base64Encode(const std::string &str, const char fillCharacter = '=');
		API_DECLSPEC std::string base64Decode(const std::string &str);

		API_DECLSPEC std::vector<std::string> split(const std::string &source, const std::string &tokens, const bool removeSpace = true);
		API_DECLSPEC std::vector<std::wstring> split(const std::wstring &source, const std::wstring &tokens, const bool removeSpace = true);

		template<typename iter, typename translator_t = StringTranslator>
		typename std::enable_if_t<std::is_same_v<typename iter::value_type, std::string>, std::string> join(const iter bgIt, const iter edIt, const std::string &seperator = std::string(""),
			const translator_t &translator = translator_t())
		{
			try {
				return std::accumulate(std::next(bgIt), edIt,
					*bgIt, [&seperator]
					(const std::string &lhs, const typename iter::value_type &rhs) -> std::string
				{
					return lhs + seperator + rhs;
				});
			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
				return EmptyString;
			}
		}

		template<typename iter, typename translator_t = StringTranslator>
		typename std::enable_if_t<!std::is_same_v<typename iter::value_type, std::string>, std::string> join(const iter bgIt, const iter edIt, const std::string &seperator = std::string(""),
			const translator_t &translator = translator_t())
		{
			try {
				return std::accumulate(std::next(bgIt), edIt,
					translator(*bgIt), [&seperator, &translator]
					(const std::string &lhs, const typename iter::value_type &rhs) -> std::string
				{
					return lhs + seperator + translator(rhs);
				});
			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
				return EmptyString;
			}
		}

		template<typename container, typename translator_t = StringTranslator>
		std::string join(const container &cont, const std::string &seperator = std::string(""),
			const translator_t &translator = translator_t())
		{
			return join(cont.cbegin(), cont.cend(), seperator, translator);
		}
	};
};

namespace std
{
	API_DECLSPEC string to_string(const bool value);
	API_DECLSPEC bool stoboolean(const std::string &str);
};
