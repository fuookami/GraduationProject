#pragma once

#include <vector>
#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

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
	using int128 = boost::multiprecision::int128_t;
	using uint128 = boost::multiprecision::uint128_t;
	using int256 = boost::multiprecision::int256_t;
	using uint256 = boost::multiprecision::uint256_t;
	using int512 = boost::multiprecision::int512_t;
	using uint512 = boost::multiprecision::uint512_t;
	using int1024 = boost::multiprecision::int1024_t;
	using uint1024 = boost::multiprecision::uint1024_t;

	using bigInt = boost::multiprecision::cpp_int;
	using bigUint = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<0, 0, boost::multiprecision::cpp_integer_type::unsigned_magnitude>>;

	using float32 = std::float_t;
	using float64 = std::double_t;
	using float128 = boost::multiprecision::cpp_bin_float_double_extended;
	using float256 = boost::multiprecision::cpp_bin_float_quad;

	using dec50 = boost::multiprecision::cpp_dec_float_50;
	using dec100 = boost::multiprecision::cpp_dec_float_100;
};
