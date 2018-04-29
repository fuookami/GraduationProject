#pragma once

#include "_pri_math_global.h"

namespace SSUtils
{
	namespace Math
	{
		template<bool Signed = true> class IntegerWrapper;
		using Integer = IntegerWrapper<>;
		using UInteger = IntegerWrapper<false>;

		template<uint32 Digits = DefaultDigits> class DecimalWrapper;
		using Decimal = DecimalWrapper<>;

		template<uint32 Digtis = DefaultDigits> class RationalWrapper;
		using Rational = RationalWrapper<>;
		template<uint32 Digits = DefaultDigits> class PowerWrapper;
		using Power = PowerWrapper<>;
		template<uint32 Digits = DefaultDigits> class LogarithmWrapper;
		using Logarithm = LogarithmWrapper<>;

		template<uint32 Digits = DefaultDigits> class RealWrapper;
		using Real = RealWrapper<>;
	};
};
