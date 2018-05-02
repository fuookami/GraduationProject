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
			typename = std::enable_if_t<std::numeric_limits<T>::is_integer>,
			typename = std::enable_if_t<std::numeric_limits<U>::is_integer>>
			const U mod(const T &lhs, const U &rhs)
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
			return static_cast<T>(log(antilogarithm) / log(base));
		}
	};
};
