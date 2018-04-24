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

		template<>
		class power<float>
		{
		public:
			typedef float value_type;

			power(const value_type base = 0.0f, const value_type index = 0.0f);
			power(const power &ano) = default;
			power(power &&ano) = default;
			explicit power(const power<double> &ano);
			explicit power(power<double> &&ano);
			explicit power(const power<long double> &ano);
			explicit power(power<double> &&ano);
			~power(void) = default;

			power &operator=(const power &rhs) = default;
			power &operator=(power &&rhs) = default;
			power &operator=(const value_type base);
			template<typename T>
			power &operator=(const power<T> &rhs);
			template<typename T>
			power &operator=(power<T> &&rhs);

			value_type base(void) const;
			void setBase(const value_type base);
			value_type index(void) const;
			void setIndex(const value_type index);

			value_type value(void) const;
			operator value_type(void) const;

		private:
			value_type m_base;
			value_type m_index;
		};

		template<>
		class power<double>
		{
		public:
			typedef double value_type;

			power(const value_type base = 0.0f, const value_type index = 0.0f);
			power(const power &ano) = default;
			power(power &&ano) = default;
			explicit power(const power<float> &ano);
			explicit power(power<float> &&ano);
			explicit power(const power<long double> &ano);
			explicit power(power<long double> &&ano);
			~power(void) = default;

			power &operator=(const power &rhs) = default;
			power &operator=(power &&rhs) = default;
			power &operator=(const value_type base);
			template<typename T>
			power &operator=(const power<T> &rhs);
			template<typename T>
			power &operator=(power<T> &&rhs);

			value_type base(void) const;
			void setBase(const value_type base);
			value_type index(void) const;
			void setIndex(const value_type index);

			value_type value(void) const;
			operator value_type(void) const;

		private:
			value_type m_base;
			value_type m_index;
		};

		template<>
		class power<long double>
		{
		public:
			typedef long double value_type;

			power(const value_type base = 0.0f, const value_type index = 0.0f);
			power(const power &ano) = default;
			power(power &&ano) = default;
			explicit power(const power<float> &ano);
			explicit power(power<float> &&ano);
			explicit power(const power<double> &ano);
			explicit power(power<double> &&ano);
			~power(void) = default;

			power &operator=(const power &rhs) = default;
			power &operator=(power &&rhs) = default;
			power &operator=(const value_type base);
			template<typename T>
			power &operator=(const power<T> &rhs);
			template<typename T>
			power &operator=(power<T> &&rhs);

			value_type base(void) const;
			void setBase(const value_type base);
			value_type index(void) const;
			void setIndex(const value_type index);

			value_type value(void) const;
			operator value_type(void) const;

		private:
			value_type m_base;
			value_type m_index;
		};

		template<typename T>
		power<T> pow(const power<T> &base, const T &index); 
	};
};
