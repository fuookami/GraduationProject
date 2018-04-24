#pragma once

#include "Global.h"
#include <cmath>

namespace SSUtils
{
	namespace Math
	{
		extern const double DefaultPrecision;
		template<typename T, typename U>
		const bool equal(const T &lhs, const U &rhs)
		{
			static_assert(std::numeric_limits<T>::is_specialized && std::numeric_limits<U>::is_specialized);
			return abs(lhs - rhs) < DefaultPrecision;
		}

		class real;

		template<typename T> class power;
		template<> class power<float>;
		template<> class power<double>;
		template<> class power<long double>;

		template<typename T> class logarithm;
		template<> class logarithm<float>;
		template<> class logarithm<double>;
		template<> class logarithm<long double>;
	};
};
