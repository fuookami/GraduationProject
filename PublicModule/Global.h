#pragma once

#include <vector>
#include <cstdint>

namespace SSUtils
{
	using wchar = wchar_t;
	using byte = unsigned char;
	using Block = std::vector<byte>;

	using int8 = std::int8_t;
	using uint8 = std::uint8_t;
	using int16 = std::int16_t;
	using uint16 = std::uint16_t;
	using int32 = std::int32_t;
	using uint32 = std::uint32_t;
	using int64 = std::int64_t;
	using uint64 = std::uint64_t;

	template<typename T, typename U, 
		typename std::enable_if<std::is_integral_v<T>, T>::type* = nullptr, 
		typename std::enable_if<std::is_integral_v<U>, U>::type* = nullptr>
	inline const U mod(const T lhs, const U rhs)
	{
		U ret(lhs % rhs);
		return ret >= 0 ? ret : (ret + rhs);
	}
};
