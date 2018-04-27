#pragma once

#include "Integer.h"
#include "DataUtils.h"
#include <limits>

namespace SSUtils
{
	namespace Math
	{
		template<uint32 Digits> 
		class RationalWrapper
		{
		public:
			typedef rational data_type;
			typedef Integer integer_type;
			typedef DecimalWrapper<Digits> value_type;

			RationalWrapper(void);
			const bool valid(void) { return denominator() != 0; }

			const integer_type numerator(void) const { return m_numerator; }
			const integer_type denominator(void) const { return m_denominator; }

		private:
			static data_type generate(const integer_type &numerator, const integer_type &denominator)
			{
				data_type i;
				if (denominator.value() != 0)
				{

				}
			}

		private:
			integer_type m_numerator;
			integer_type m_denominator;
		};
	};
};
