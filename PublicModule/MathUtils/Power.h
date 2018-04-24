#pragma once

#include "_pri_math_global.h"

namespace SSUtils
{
	namespace Math
	{
		template<typename T>
		class power
		{
		public:
			typedef T value_type;

			power(const T &base = T(), const T &index = T());
			power(const power &ano) = default;
			power(power &&ano) = default;
			template<typename U>
			explicit power(const power<U> &ano);
			template<typename U>
			explicit power(power<U> &&ano);
			~power(void) = default;

			power &operator=(const power &rhs) = default;
			power &operator=(power &&rhs) = default;
			power &operator=(const T &base);
			power &operator=(T &&base);

			T base(void) const;
			void setBase(const T &base);
			T index(void) const;
			void setIndex(const T &index);

			T value(void) const;
			operator T(void) const;

		private:
			T m_base;
			T m_index;
		};

		template<typename T>
		power<T> pow(const power<T> &base, const T &index); 
	};
};
