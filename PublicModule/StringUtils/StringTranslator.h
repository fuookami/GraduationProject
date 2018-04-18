#pragma once

#include "StringConverter.h"
#include <string>
#include <sstream>

namespace SSUtils
{
	namespace String
	{
		inline std::string toString(const bool val);
		inline const bool toBoolean(const std::string &src);

		struct StringTranslator
		{
			StringTranslator(void) = default;
			StringTranslator(const StringTranslator &ano) = delete;
			StringTranslator(StringTranslator &&ano) = delete;
			StringTranslator &operator=(const StringTranslator &ano) = delete;
			StringTranslator &operator=(StringTranslator &&ano) = delete;
			~StringTranslator(void) = default;

			template<typename T>
			inline std::string operator()(const T &val) const
			{
				std::ostringstream sout;
				sout << val;
				return sout.str();
			};

			template<>
			inline std::string operator()(const std::string &val) const
			{
				return val;
			}

			template<>
			inline std::string operator()(const std::wstring &val) const
			{
				return toString(val);
			}

			template<>
			inline std::string operator()(const bool &val) const
			{
				return toString(val);
			}
		};
	};
};
