#pragma once

#include "_pri_math_global.h"

namespace SSUtils
{
	namespace Math
	{
		template<typename T>
		class logarithm
		{
		};

		template<>
		class logarithm<float>
		{
		};

		template<>
		class logarithm<double>
		{
		};
	};
};
