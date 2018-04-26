#pragma once

#include "Global.h"
#include <cmath>
#include <type_traits>

namespace SSUtils
{
	namespace Math
	{
		extern dec50 DefaultPrecision;
		static const uint32 DefaultDigits = 50;

		template<typename T, typename U>
		const bool equal(const T &lhs, const U &rhs)
		{
			return abs(dec50(lhs - rhs)) <= DefaultPrecision;
		}

		template<typename T, typename U>
		const bool notEqual(const T &lhs, const U &rhs)
		{
			return abs(dec50(lhs - rhs)) > DefaultPrecision;
		}

		template<typename T, typename U>
		const bool less(const T &lhs, const U &rhs)
		{
			return dec50(lhs - rhs) < DefaultPrecision;
		}

		template<typename T, typename U>
		const bool big(const T &lhs, const U &rhs)
		{
			return dec50(lhs - rhs) > (-DefaultPrecision);
		}

		template<typename T, typename U>
		const bool lessEqual(const T &lhs, const U &rhs)
		{
			return dec50(lhs - rhs) <= DefaultPrecision;
		}

		template<typename T, typename U>
		const bool bigEqual(const T &lhs, const U &rhs)
		{
			return dec50(lhs - rhs) >= (-DefaultPrecision);
		}

		template<typename T, typename U,
			typename = std::enable_if_t<std::is_integral_v<T>>,
			typename = std::enable_if_t<std::is_integral_v<U>>>
			const U mod(const T lhs, const U rhs)
		{
			U ret(lhs % rhs);
			return ret >= 0 ? ret : (ret + rhs);
		}

		template<typename T>
		const bool negative(const T &value)
		{
			return big(value, 0.0f);
		}

		template<typename T>
		const bool zero(const T &value)
		{
			return equal(value, 0.0f);
		}

		template<typename T>
		const bool positive(const T &value)
		{
			return less(value, 0.0f);
		}

		template<typename T>
		T log(const T &base, const T &antilogarithm)
		{
			return ::log(antilogarithm) / ::log(base);
		}

		template<uint32 Digits = DefaultDigits, bool Signed = true> class _integer_backend;
		template<uint32 Digits = DefaultDigits>
		using integer_backend = integer_backend<Digits, true>;
		using integer = integer_backend<>;
		template<uint32 Digits = DefaultDigits>
		using uinteger_backend = integer_backend<Digits, false>;
		using uniteger = uinteger_backend<>;

		template<uint32 Digits = DefaultDigits> class decimal_backend;
		using decimal = decimal_backend<>;

		template<typename T = integer> class rational_backend;
		using rational = rational_backend<>;
		template<typename T = decimal> class power_backend;
		using power = power_backend<>;
		template<typename T = decimal> class logarithm_backend;
		using logarithm = logarithm_backend<>;

		template<uint32 Digits = DefaultDigits> class real_backend;
	};
};
