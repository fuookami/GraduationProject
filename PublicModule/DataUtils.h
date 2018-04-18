#pragma once

#include "Global.h"
#include "DataUtils/DataTranslator.h"
#include <array>
#include <string>

#include <algorithm>

namespace SSUtils
{
	namespace Data
	{
		template<uint32 size>
		inline Block fromArray(const std::array<byte, size> &data)
		{
			return Block(data.cbegin(), data.cend());
		}
		template<uint32 size>
		inline std::array<byte, size> toArray(const Block &data)
		{
			std::array<byte, size> ret;
			std::copy(data.cbegin(), size < data.size() ? (data.cbegin() + size) : data.cend(), ret.begin());
			return ret;
		}

		template<typename T, typename U>
		class ConversionChecker
		{
		private:
			static char Test(U);
			static int Test(...);
			static T MakeT();
		public:
			static const bool value = sizeof(Test(MakeT())) == sizeof(char);
		};

		std::string toHexString(const Block &data, const std::string seperator = "");
		Block fromHexString(const std::string &str, const std::string seperator = "");

		std::string toBase64String(const Block &data, const char fillCharacter = '=');
		Block fromBase64String(const std::string &str);

		std::string toString(const Block &data);
		Block fromString(const std::string &str);
		std::wstring toWString(const Block &data);
		Block fromWString(const std::wstring &str);

		Block generateRandomBlock(const uint32 length = 8);
	};
};
