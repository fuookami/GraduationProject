#pragma once

#include "_pri_math_global.h"
#include "DataUtils.h"
#include <limits>

namespace SSUtils
{
	namespace Math
	{
		template<uint32 Digits> 
		class decimal_wrapper
		{
		public:
			typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<Digits>> value_type;

			decimal_wrapper(void);

		private:
			value_type value;
		};
	};
};
