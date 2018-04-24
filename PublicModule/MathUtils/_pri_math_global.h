#pragma once

#include "Global.h"

namespace SSUtils
{
	namespace Math
	{
		class real;

		template<typename T> class power;
		template<> class power<float>;
		template<> class power<double>;
		template<> class power<long double>

		template<typename T> class logarithm;
		template<> class logarithm<float>;
		template<> class logarithm<double>;
		template<> class logarithm<long double>;
	};
};
