#pragma once

#include <string>
#include <regex>

namespace SSUtils
{
	namespace String
	{
		struct RegexChecker
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

			const bool operator()(const std::string &src) const
			{
				std::smatch result;
				return std::regex_match(src, result, reg);
			}
		};

		namespace RegexPatterns
		{
			extern const std::string NaturalNumberPattern;
			extern const std::string IntegerPattern;
			extern const std::string PositiveIntegerPattern;
		};

		namespace RegexCheckers
		{
			extern const RegexChecker NaturalNumberChecker;
			extern const RegexChecker IntegerChecker;
			extern const RegexChecker PositiveIntegerChecker;
		};

		const bool isNaturalNumber(const std::string &src);
		const bool isInteger(const std::string &src);
		const bool isPositiveInteger(const std::string &src);
	};
};
