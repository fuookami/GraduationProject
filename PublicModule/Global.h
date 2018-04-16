#pragma once

#include <vector>
#include <cstdint>

namespace SSUtils
{
	using wchar = wchar_t;
	using byte = unsigned char;
	using Data = std::vector<byte>;

	using int8 = std::int8_t;
	using uint8 = std::uint8_t;
	using int16 = std::int16_t;
	using uint16 = std::uint16_t;
	using int32 = std::int32_t;
	using uint32 = std::uint32_t;
	using int64 = std::int64_t;
	using uint64 = std::uint64_t;

	static const unsigned int CPUIdLength = 8;
};
