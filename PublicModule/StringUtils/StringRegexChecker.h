#pragma once

#include "Global.h"
#include <string>
#include <regex>

namespace SSUtils
{
	namespace String
	{
		struct API_DECLSPEC RegexChecker
		{
			const std::string pattern;
			const std::regex reg;

			RegexChecker(const std::string &_pattern);
			RegexChecker(std::string &&_pattern);
			RegexChecker(const RegexChecker &ano) = delete;
			RegexChecker(RegexChecker &&ano) = delete;
			RegexChecker &operator=(const RegexChecker &rhs) = delete;
			RegexChecker &operator=(RegexChecker &&rhs) = delete;
			~RegexChecker(void) = default;

			const bool operator()(const std::string &src) const;
		};

		struct API_DECLSPEC RegexCatcher
		{
			const std::string pattern;
			const std::regex reg;

			RegexCatcher(const std::string &_pattern);
			RegexCatcher(std::string &&_pattern);
			RegexCatcher(const RegexCatcher &ano) = delete;
			RegexCatcher(RegexCatcher &&ano) = delete;
			RegexCatcher &operator=(const RegexCatcher &ano) = delete;
			RegexCatcher &operator=(RegexCatcher &&ano) = delete;
			~RegexCatcher(void) = default;

			std::vector<std::string> operator()(const std::string &src) const;
		};

		struct API_DECLSPEC RegexMatcher
		{
			const std::string pattern;
			const std::regex reg;

			RegexMatcher(const std::string &_pattern);
			RegexMatcher(std::string &&_pattern);
			RegexMatcher(const RegexMatcher &ano) = delete;
			RegexMatcher(RegexMatcher &&ano) = delete;
			RegexMatcher &operator=(const RegexMatcher &ano) = delete;
			RegexMatcher &operator=(RegexMatcher &&ano) = delete;
			~RegexMatcher(void) = default;

			std::vector<std::string> operator()(const std::string &src) const;
		};

		namespace RegexPatterns
		{
			extern API_DECLSPEC const std::string PatternPrefix;
			extern API_DECLSPEC const std::string PatternSuffix;
			extern API_DECLSPEC const std::string NaturalNumberPattern;
			extern API_DECLSPEC const std::string DecIntegerPattern;
			extern API_DECLSPEC const std::string PositiveDecIntegerPattern;
			extern API_DECLSPEC const std::string HexIntegerPattern;
			extern API_DECLSPEC const std::string DecimalPattern;
		};

		namespace RegexCheckers
		{
			extern API_DECLSPEC const RegexChecker NaturalNumberChecker;
			extern API_DECLSPEC const RegexChecker DecIntegerChecker;
			extern API_DECLSPEC const RegexChecker PositiveDecIntegerChecker;
			extern API_DECLSPEC const RegexChecker HexIntegerChecker;
			extern API_DECLSPEC const RegexChecker DecimalChecker;
		};

		namespace RegexMatchers
		{
			extern API_DECLSPEC const RegexMatcher NaturalNumberMatcher;
			extern API_DECLSPEC const RegexMatcher DecIntegerMatcher;
			extern API_DECLSPEC const RegexMatcher PositiveDecIntegerMatcher;
			extern API_DECLSPEC const RegexMatcher HexIntegerMatcher;
			extern API_DECLSPEC const RegexMatcher DecimalMatcher;
		};

		API_DECLSPEC const bool isNaturalNumber(const std::string &src);
		API_DECLSPEC std::vector<std::string> matchNaturalNumber(const std::string &src);

		API_DECLSPEC const bool isInteger(const std::string &src);
		API_DECLSPEC std::vector<std::string> matchInteger(const std::string &src);

		API_DECLSPEC const bool isDecInteger(const std::string &src);
		API_DECLSPEC std::vector<std::string> mathchDecInteger(const std::string &src);

		API_DECLSPEC const bool isPositiveDecInteger(const std::string &src);
		API_DECLSPEC std::vector<std::string> matchPositiveDecInteger(const std::string &src);

		API_DECLSPEC const bool isHexInteger(const std::string &src);
		API_DECLSPEC std::vector<std::string> matchHexInteger(const std::string &src);

		API_DECLSPEC const bool isDecimal(const std::string &src);
		API_DECLSPEC std::vector<std::string> matchDecimal(const std::string &src);
	};
};
