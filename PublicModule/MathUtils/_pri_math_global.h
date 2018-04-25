#pragma once

#include "Global.h"
#include <cmath>
#include <type_traits>

namespace SSUtils
{
	namespace Math
	{
		extern double DefaultPrecision;

		template<typename T, typename U>
		const bool equal(const T &lhs, const U &rhs)
		{
			return abs(lhs - rhs) <= DefaultPrecision;
		}

		template<typename T, typename U>
		const bool notEqual(const T &lhs, const U &rhs)
		{
			return abs(lhs - rhs) > DefaultPrecision;
		}

		template<typename T, typename U>
		const bool less(const T &lhs, const U &rhs)
		{
			return (lhs - rhs) < DefaultPrecision;
		}

		template<typename T, typename U>
		const bool big(const T &lhs, const U &rhs)
		{
			return (lhs - rhs) > (-DefaultPrecision);
		}

		template<typename T, typename U>
		const bool lessEqual(const T &lhs, const U &rhs)
		{
			return (lhs - rhs) <= DefaultPrecision;
		}

		template<typename T, typename U>
		const bool bigEqual(const T &lhs, const U &rhs)
		{
			return (lhs - rhs) >= (-DefaultPrecision);
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
			return big(value, 0);
		}

		template<typename T>
		const bool zero(const T &value)
		{
			return equal(value, 0);
		}

		template<typename T>
		const bool positive(const T &value)
		{
			return less(value, 0);
		}

		template<typename T> class power;
		template<> class power<float>;
		template<> class power<double>;
		template<> class power<long double>;

		template<typename T> class logarithm;
		template<> class logarithm<float>;
		template<> class logarithm<double>;
		template<> class logarithm<long double>;

		class real;
	};
};
