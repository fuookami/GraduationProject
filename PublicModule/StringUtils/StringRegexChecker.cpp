#include "StringRegexChecker.h"

namespace SSUtils
{
	namespace String
	{
		RegexChecker::RegexChecker(const std::string & _pattern)
			: pattern(_pattern), reg(pattern)
		{
		}

		RegexChecker::RegexChecker(std::string && _pattern)
			: pattern(std::move(_pattern)), reg(pattern)
		{
		}

		namespace RegexPatterns
		{
			const std::string NaturalNumberPattern("^(0|[1-9]\\d*)$");
			const std::string IntegerPattern("^-?(0|[1-9]\\d*)$");
			const std::string PositiveIntegerPattern("^[1-9]\\d*$");
		};

		namespace RegexCheckers
		{
			const RegexChecker NaturalNumberChecker(RegexPatterns::NaturalNumberPattern);
			const RegexChecker IntegerChecker(RegexPatterns::IntegerPattern);
			const RegexChecker PositiveIntegerChecker(RegexPatterns::PositiveIntegerPattern);
		};

		const bool isNaturalNumber(const std::string & src)
		{
			return RegexCheckers::NaturalNumberChecker(src);
		}

		const bool isInteger(const std::string & src)
		{
			return RegexCheckers::IntegerChecker(src);
		}

		const bool isPositiveInteger(const std::string & src)
		{
			return RegexCheckers::PositiveIntegerChecker(src);
		}
	};
};
