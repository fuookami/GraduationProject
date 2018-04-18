#pragma once

#include "_pri_string_global.h"

namespace SSUtils
{
	namespace String
	{
		inline std::wstring toWString(const std::string &src, const CharType charType = LocalCharType);
		inline std::string toString(const std::wstring &src, const CharType charType = LocalCharType);

		struct Converter
		{
			CharType srcCharType;
			CharType destCharType;

			Converter(const CharType _srcCharType, const CharType _destCharType = LocalCharType);
			Converter(const Converter &ano) = delete;
			Converter(Converter &&ano) = delete;
			Converter &operator=(const Converter &rhs) = delete;
			Converter &operator=(Converter &&rhs) = delete;
			~Converter(void) = default;

			inline std::string operator()(const std::string &src) const;
			inline std::wstring operator()(const std::wstring &src) const;
		};

		inline std::string fromLocal(const CharType srcCharType, const std::string &src);
		inline std::wstring fromLocal(const CharType srcCharType, const std::wstring &src);
		inline std::string toLocal(const CharType targetCharType, const std::string &src);
		inline std::wstring toLocal(const CharType targetCharType, const std::wstring &src);

		inline std::string toDBS(const std::string &src, const CharType charType = LocalCharType);
		inline std::string toQBS(const std::string &src, const CharType charType = LocalCharType);
	};
};