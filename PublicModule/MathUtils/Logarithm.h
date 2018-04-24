#pragma once

#include "_pri_math_global.h"

namespace SSUtils
{
	namespace Math
	{
		template<typename T>
		class logarithm
		{
		public:
			typedef T value_type;

			logarithm(const T &base = T(), const T &antilogarithm = T())
				: m_base(base), m_antilogarithm(antilogarithm()) {};
			logarithm(const logarithm &ano) = default;
			logarithm(logarithm &&ano) = default;
			~logarithm(void) = default;

			logarithm &operator=(const logarithm &rhs) = default;
			logarithm &operator=(logarithm &&rhs) = default;
			logarithm &operator=(const T &base);
			logarithm &operator=(T &&base);

			template<typename U>
			logarithm &operator+=(const logarithm &rhs);
			template<typename U>
			logarithm &operator-=(const logarithm &rhs);

			const bool valid(void) const;

			T base(void) const;
			void setBase(const T &base);
			T antilogarithm(void) const;
			void setAntilogarithm(const T &antilogarithm);

			T value(void) const;
			operator T(void) const;

		private:
			T m_base;
			T m_antilogarithm;
		};

		template<>
		class logarithm<float>
		{
		public:
			typedef float value_type;

			logarithm(const value_type base = 0.0f, const value_type antilogarithm = 0.0f);
			logarithm(const logarithm &ano) = default;
			logarithm(logarithm &&ano) = default;
			explicit logarithm(const logarithm<double> &ano);
			explicit logarithm(logarithm<double> &&ano);
			explicit logarithm(const logarithm<long double> &ano);
			explicit logarithm(logarithm<double> &&ano);
			~logarithm(void) = default;

			logarithm &operator=(const logarithm &rhs) = default;
			logarithm &operator=(logarithm &&rhs) = default;
			logarithm &operator=(const value_type base);
			template<typename T>
			logarithm &operator=(const logarithm<T> &rhs);
			template<typename T>
			logarithm &operator=(logarithm<T> &&rhs);

			template<typename T>
			logarithm &operator+=(const logarithm &rhs);
			template<typename T>
			logarithm &operator-=(const logarithm &rhs);

			const bool valid(void) const;

			value_type base(void) const;
			void setBase(const value_type base);
			value_type antilogarithm(void) const;
			void setAntilogarithm(const value_type antilogarithm);

			value_type value(void) const;
			operator value_type(void) const;

		private:
			value_type m_base;
			value_type m_antilogarithm;
		};

		template<>
		class logarithm<double>
		{
		public:
			typedef double value_type;

			logarithm(const value_type base = 0.0f, const value_type antilogarithm = 0.0f);
			logarithm(const logarithm &ano) = default;
			logarithm(logarithm &&ano) = default;
			explicit logarithm(const logarithm<float> &ano);
			explicit logarithm(logarithm<float> &&ano);
			explicit logarithm(const logarithm<long double> &ano);
			explicit logarithm(logarithm<long double> &&ano);
			~logarithm(void) = default;

			logarithm &operator=(const logarithm &rhs) = default;
			logarithm &operator=(logarithm &&rhs) = default;
			logarithm &operator=(const value_type base);
			template<typename T>
			logarithm &operator=(const logarithm<T> &rhs);
			template<typename T>
			logarithm &operator=(logarithm<T> &&rhs);

			template<typename T>
			logarithm &operator+=(const logarithm &rhs);
			template<typename T>
			logarithm &operator-=(const logarithm &rhs);

			const bool valid(void) const;

			value_type base(void) const;
			void setBase(const value_type base);
			value_type antilogarithm(void) const;
			void setAntilogarithm(const value_type antilogarithm);

			value_type value(void) const;
			operator value_type(void) const;

		private:
			value_type m_base;
			value_type m_antilogarithm;
		};

		template<>
		class logarithm<long double>
		{
		public:
			typedef long double value_type;

			logarithm(const value_type base = 0.0f, const value_type antilogarithm = 0.0f);
			logarithm(const logarithm &ano) = default;
			logarithm(logarithm &&ano) = default;
			explicit logarithm(const logarithm<float> &ano);
			explicit logarithm(logarithm<float> &&ano);
			explicit logarithm(const logarithm<double> &ano);
			explicit logarithm(logarithm<double> &&ano);
			~logarithm(void) = default;

			logarithm &operator=(const logarithm &rhs) = default;
			logarithm &operator=(logarithm &&rhs) = default;
			logarithm &operator=(const value_type base);
			template<typename T>
			logarithm &operator=(const logarithm<T> &rhs);
			template<typename T>
			logarithm &operator=(logarithm<T> &&rhs);

			template<typename T>
			logarithm &operator+=(const logarithm &rhs);
			template<typename T>
			logarithm &operator-=(const logarithm &rhs);

			const bool valid(void) const;

			value_type base(void) const;
			void setBase(const value_type base);
			value_type antilogarithm(void) const;
			void setAntilogarithm(const value_type antilogarithm);

			value_type value(void) const;
			operator value_type(void) const;

		private:
			value_type m_base;
			value_type m_antilogarithm;
		};
	};
};

template<typename T, typename U>
SSUtils::Math::logarithm<T> operator+(const SSUtils::Math::logarithm<T> &lhs, const SSUtils::Math::logarithm<T> &rhs)
{
	return SSUtils::Math::equal(lhs.base(), rhs.base()) 
		: SSUtils::Math::logarithm<T>(lhs.base(), static_cast<T>(lhs.antilogarithm() * rhs.antilogarithm())) 
		? SSUtils::Math::logarithm<T>();
}

template<typename T, typename U>
SSUtils::Math::logarithm<T> operator-(const SSUtils::Math::logarithm<T> &lhs, const SSUtils::Math::logarithm<T> &rhs)
{
	return SSUtils::Math::equal(lhs.base(), rhs.base())
		: SSUtils::Math::logarithm<T>(lhs.base(), static_cast<T>(lhs.antilogarithm() / rhs.antilogarithm()))
		? SSUtils::Math::logarithm<T>();
}
