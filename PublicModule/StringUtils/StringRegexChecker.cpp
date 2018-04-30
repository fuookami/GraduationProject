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

		const bool RegexChecker::operator()(const std::string & src) const
		{
			std::smatch result;
			return std::regex_match(src, result, reg);
		}

		RegexMatcher::RegexMatcher(const std::string & _pattern)
			: pattern(_pattern), reg(pattern)
		{
		}

		RegexMatcher::RegexMatcher(std::string && _pattern)
			: pattern(std::move(_pattern)), reg(pattern)
		{
		}

		std::vector<std::string> RegexMatcher::operator()(const std::string & src) const
		{
			std::vector<std::string> ret;
			for (std::sregex_iterator curr(src.cbegin(), src.cend(), reg), ed; curr != ed; ++curr)
			{
				ret.push_back(curr->str());
			}
			return ret;
		}

		namespace RegexPatterns
		{
			const std::string PatternPrefix("^");
			const std::string PatternSuffix("$");
			const std::string NaturalNumberPattern("(0|[1-9]\\d*)");
			const std::string IntegerPattern("-?(0|[1-9]\\d*)");
			const std::string PositiveIntegerPattern("[1-9]\\d*");
			const std::string DecimalPattern("-?(0|[1-9]\\d*).\\d*");
		};

		namespace RegexCheckers
		{
#define pattern_join(pattern) (RegexPatterns::PatternPrefix + pattern + RegexPatterns::PatternSuffix)
			const RegexChecker NaturalNumberChecker(pattern_join(RegexPatterns::NaturalNumberPattern));
			const RegexChecker IntegerChecker(pattern_join(RegexPatterns::IntegerPattern));
			const RegexChecker PositiveIntegerChecker(pattern_join(RegexPatterns::PositiveIntegerPattern));
			const RegexChecker DecimalChecker(pattern_join(RegexPatterns::DecimalPattern));
#undef pattern_join
		};

		namespace RegexMatchers
		{
			const RegexMatcher NaturalNumberMatcher(RegexPatterns::NaturalNumberPattern);
			const RegexMatcher IntegerMatcher(RegexPatterns::IntegerPattern);
			const RegexMatcher PositiveIntegerMatcher(RegexPatterns::PositiveIntegerPattern);
			const RegexMatcher DecimalMatcher(RegexPatterns::DecimalPattern);
		};

		const bool isNaturalNumber(const std::string & src)
		{
			return RegexCheckers::NaturalNumberChecker(src);
		}

		std::vector<std::string> matchNaturalNumber(const std::string & src)
		{
			return RegexMatchers::NaturalNumberMatcher(src);
		}

		const bool isInteger(const std::string & src)
		{
			return RegexCheckers::IntegerChecker(src);
		}

		std::vector<std::string> mathchInteger(const std::string & src)
		{
			return RegexMatchers::IntegerMatcher(src);
		}

		const bool isPositiveInteger(const std::string & src)
		{
			return RegexCheckers::PositiveIntegerChecker(src);
		}

		std::vector<std::string> matchPositiveInteger(const std::string & src)
		{
			return RegexMatchers::PositiveIntegerMatcher(src);
		}

		const bool isDecimal(const std::string & src)
		{
			return RegexCheckers::DecimalChecker(src);
		}

		std::vector<std::string> matchDecimal(const std::string & src)
		{
			return RegexMatchers::DecimalMatcher(src);
		}
	};
};
