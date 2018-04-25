#pragma once

#include "_pri_math_global.h"
#include "DataUtils.h"
#include <cmath>

namespace SSUtils
{
	namespace Math
	{
		template<typename T>
		class logarithm
		{
		public:
			typedef T value_type;

			logarithm(const T base = T(), const T &antilogarithm = T())
				: m_base(base), m_antilogarithm(antilogarithm()) {};
			logarithm(const logarithm &ano) = default;
			logarithm(logarithm &&ano) = default;
			template<typename U>
			explicit logarithm(const logarithm<U> &ano)
				: logarithm(value_type(ano.m_base), value_type(ano.m_antilogarithm)) {};
			template<typename U>
			explicit logarithm(logarithm<U> &&ano)
				: logarithm(value_type(std::move(ano.m_base)), value_type(std::move(ano.m_antilogarithm))) {};
			~logarithm(void) = default;

			logarithm &operator=(const logarithm &rhs) = default;
			logarithm &operator=(logarithm &&rhs) = default;
			template<typename U>
			logarithm &operator=(const logarithm<U> &rhs)
			{
				m_base = value_type(rhs.m_base);
				m_antilogarithm = value_type(rhs.m_antilogarithm);
				return *this;
			}
			template<typename U>
			logarithm &operator=(logarithm<U> &&rhs)
			{
				m_base = value_type(std::move(rhs.m_base));
				m_antilogarithm = value_type(std::move(rhs.m_antilogarithm));
				return *this;
			}
			logarithm &operator=(const T &base)
			{
				m_base = base;
				m_antilogarithm = 1;
				return *this;
			}
			logarithm &operator=(T &&base)
			{
				m_base = std::move(base);
				m_antilogarithm = 1;
				return *this;
			}

			template<typename U>
			logarithm &operator+=(const logarithm<U> &rhs)
			{
				if (equal(m_base, rhs.m_base))
				{
					m_antilogarithm *= rhs.m_antilogarithm;
				}
				return *this;
			}
			template<typename U>
			logarithm &operator-=(const logarithm<U> &rhs)
			{
				if (equal(m_base, rhs.m_base))
				{
					m_antilogarithm /= rhs.m_antilogarithm;
				}
				return *this;
			}
			template<typename U>
			logarithm &operator*=(const U rhs)
			{
				m_antilogarithm = static_cast<T>(pow(m_antilogarithm, rhs));
				return *this;
			}

			const bool valid(void) const
			{
				return negative(m_base) && negative(m_antilogarithm);
			}

			T &base(void) const { return m_base; }
			void setBase(const T &base) { m_base = base; }
			T &antilogarithm(void) const { return m_antilogarithm }
			void setAntilogarithm(const T &antilogarithm) { m_antilogarithm = antilogarithm; }

			double value(void) const { return static_cast<double>(log(m_antilogarithm) / log(m_base)); }
			operator double(void) const { return value(); }

		private:
			T m_base;
			T m_antilogarithm;
		};

		template<>
		class logarithm<float>
		{
		public:
			typedef float value_type;

			logarithm(const value_type base = 0.0f, const value_type antilogarithm = 0.0f)
				: m_base(base), m_antilogarithm(antilogarithm) {};
			logarithm(const logarithm &ano) = default;
			logarithm(logarithm &&ano) = default;
			template<typename T>
			explicit logarithm(const logarithm<T> &ano)
				: logarithm(value_type(ano.base()), value_type(ano.antilogarithm())) {};
			template<>
			explicit logarithm(const logarithm<double> &ano)
				: m_base(static_cast<value_type>(ano.base())), m_antilogarithm(static_cast<value_type>(ano.antilogarithm())) {};
			template<>
			explicit logarithm(const logarithm<long double> &ano)
				: m_base(static_cast<value_type>(ano.base())), m_antilogarithm(static_cast<value_type>(ano.antilogarithm())) {};
			~logarithm(void) = default;

			logarithm &operator=(const logarithm &rhs) = default;
			logarithm &operator=(logarithm &&rhs) = default;
			template<typename T>
			logarithm &operator=(const logarithm<T> &rhs)
			{
				m_base = static_cast<float>(ano.base());
				m_antilogarithm = static_cast<float>(ano.antilogarithm());
				return *this;
			}
			logarithm &operator=(const value_type base)
			{
				m_base = base;
				m_antilogarithm = 1;
				return *this;
			}

			template<typename T>
			logarithm &operator+=(const logarithm<T> &rhs)
			{
				if (equal(m_base, rhs.m_base))
				{
					m_antilogarithm *= rhs.m_antilogarithm;
				}
				return *this;
			}
			template<typename T>
			logarithm &operator-=(const logarithm<T> &rhs)
			{
				if (equal(m_base, rhs.m_base))
				{
					m_antilogarithm /= rhs.m_antilogarithm;
				}
				return *this;
			}
			logarithm &operator*=(const value_type rhs)
			{
				m_antilogarithm = static_cast<value_type>(::std::pow(m_antilogarithm, rhs));
				return *this;
			}

			const bool valid(void) const
			{
				return negative(m_base) && negative(m_antilogarithm);
			}

			value_type base(void) const { return m_base; }
			void setBase(const value_type base) { m_base = base; }
			value_type antilogarithm(void) const { return m_antilogarithm; }
			void setAntilogarithm(const value_type antilogarithm) { m_antilogarithm = antilogarithm; }

			value_type value(void) const { return static_cast<value_type>(log(m_antilogarithm) / log(m_base)); }
			operator value_type(void) const { return value(); }

		private:
			value_type m_base;
			value_type m_antilogarithm;
		};

		template<>
		class logarithm<double>
		{
		public:
			typedef double value_type;

			logarithm(const value_type base = 0.0f, const value_type antilogarithm = 0.0f)
				: m_base(base), m_antilogarithm(antilogarithm) {};
			logarithm(const logarithm &ano) = default;
			logarithm(logarithm &&ano) = default;
			template<typename T>
			explicit logarithm(const logarithm<T> &ano)
				: logarithm(value_type(ano.base()), value_type(ano.antilogarithm())) {};
			explicit logarithm(const logarithm<float> &ano)
				: m_base(static_cast<value_type>(ano.base())), m_antilogarithm(static_cast<value_type>(ano.antilogarithm())) {};
			explicit logarithm(const logarithm<long double> &ano)
				: m_base(static_cast<value_type>(ano.base())), m_antilogarithm(static_cast<value_type>(ano.antilogarithm())) {};
			~logarithm(void) = default;

			logarithm &operator=(const logarithm &rhs) = default;
			logarithm &operator=(logarithm &&rhs) = default;
			template<typename T>
			logarithm &operator=(const logarithm<T> &rhs)
			{
				m_base = static_cast<float>(ano.base());
				m_antilogarithm = static_cast<float>(ano.antilogarithm());
				return *this;
			}
			logarithm &operator=(const value_type base)
			{
				m_base = base;
				m_antilogarithm = 1;
				return *this;
			}

			template<typename T>
			logarithm &operator+=(const logarithm<T> &rhs)
			{
				if (equal(m_base, rhs.m_base))
				{
					m_antilogarithm *= rhs.m_antilogarithm;
				}
				return *this;
			}
			template<typename T>
			logarithm &operator-=(const logarithm<T> &rhs)
			{
				if (equal(m_base, rhs.m_base))
				{
					m_antilogarithm /= rhs.m_antilogarithm;
				}
				return *this;
			}
			logarithm &operator*=(const value_type rhs)
			{
				m_antilogarithm = static_cast<value_type>(::std::pow(m_antilogarithm, rhs));
				return *this;
			}

			const bool valid(void) const
			{
				return negative(m_base) && negative(m_antilogarithm);
			}

			value_type base(void) const { return m_base; }
			void setBase(const value_type base) { m_base = base; }
			value_type antilogarithm(void) const { return m_antilogarithm; }
			void setAntilogarithm(const value_type antilogarithm) { m_antilogarithm = antilogarithm; }

			value_type value(void) const { return static_cast<value_type>(log(m_antilogarithm) / log(m_base)); }
			operator value_type(void) const { return value(); }

		private:
			value_type m_base;
			value_type m_antilogarithm;
		};

		template<>
		class logarithm<long double>
		{
		public:
			typedef long double value_type;

			logarithm(const value_type base = 0.0f, const value_type antilogarithm = 0.0f)
				: m_base(base), m_antilogarithm(antilogarithm) {};
			logarithm(const logarithm &ano) = default;
			logarithm(logarithm &&ano) = default;
			template<typename T>
			explicit logarithm(const logarithm<T> &ano)
				: logarithm(value_type(ano.base()), value_type(ano.antilogarithm())) {};
			explicit logarithm(const logarithm<float> &ano)
				: m_base(static_cast<value_type>(ano.base())), m_antilogarithm(static_cast<value_type>(ano.antilogarithm())) {};
			explicit logarithm(const logarithm<double> &ano)
				: m_base(static_cast<value_type>(ano.base())), m_antilogarithm(static_cast<value_type>(ano.antilogarithm())) {};
			~logarithm(void) = default;

			logarithm &operator=(const logarithm &rhs) = default;
			logarithm &operator=(logarithm &&rhs) = default;
			logarithm &operator=(const value_type base);
			template<typename T>
			logarithm &operator=(const logarithm<T> &rhs)
			{
				m_base = static_cast<float>(ano.base());
				m_antilogarithm = static_cast<float>(ano.antilogarithm());
				return *this;
			}
			logarithm &operator=(const value_type base)
			{
				m_base = base;
				m_antilogarithm = 1;
				return *this;
			}

			template<typename T>
			logarithm &operator+=(const logarithm<T> &rhs)
			{
				if (equal(m_base, rhs.m_base))
				{
					m_antilogarithm *= rhs.m_antilogarithm;
				}
				return *this;
			}
			template<typename T>
			logarithm &operator-=(const logarithm<T> &rhs)
			{
				if (equal(m_base, rhs.m_base))
				{
					m_antilogarithm /= rhs.m_antilogarithm;
				}
				return *this;
			}
			logarithm &operator*=(const value_type rhs)
			{
				m_antilogarithm = static_cast<value_type>(::std::pow(m_antilogarithm, rhs));
				return *this;
			}

			const bool valid(void) const
			{
				return negative(m_base) && negative(m_antilogarithm);
			}

			value_type base(void) const { return m_base; }
			void setBase(const value_type base) { m_base = base; }
			value_type antilogarithm(void) const { return m_antilogarithm; }
			void setAntilogarithm(const value_type antilogarithm) { m_antilogarithm = antilogarithm; }

			value_type value(void) const { return static_cast<value_type>(log(m_antilogarithm) / log(m_base)); }
			operator value_type(void) const { return value(); }

		private:
			value_type m_base;
			value_type m_antilogarithm;
		};
	};
};

template<typename T, typename U>
const bool operator==(const SSUtils::Math::logarithm<T> &lhs, const SSUtils::Math::logarithm<T> &rhs)
{
	return lhs.valid() && rhs.valid() && equal(lhs.value(), rhs.value());
}

template<typename T, typename U>
const bool operator==(const SSUtils::Math::logarithm<T> &lhs, const U &rhs)
{
	return lhs.valid() && equal(lhs.value(), rhs);
}

template<typename T, typename U>
const bool operator==(const T &lhs, const SSUtils::Math::logarithm<T> &rhs)
{
	return rhs.valid() && equal(lhs, rhs.value());
}

template<typename T, typename U>
const bool operator!=(const SSUtils::Math::logarithm<T> &lhs, const SSUtils::Math::logarithm<T> &rhs)
{
	return !lhs.valid() || !rhs.valid() || !SSUtils::Math::equal(lhs.value(), rhs.value());
}

template<typename T, typename U>
const bool operator!=(const SSUtils::Math::logarithm<T> &lhs, const U &rhs)
{
	return !lhs.valid() || SSUtils::Math::equal(lhs.value(), rhs);
}

template<typename T, typename U>
const bool operator!=(const T &lhs, const SSUtils::Math::logarithm<T> &rhs)
{
	return !rhs.valid() || SSUtils::Math::equal(lhs, rhs.value());
}

template<typename T, typename U>
const bool operator<(const SSUtils::Math::logarithm<T> &lhs, const SSUtils::Math::logarithm<U> &rhs)
{
	return (lhs.valid() && rhs.valid()) ? SSUtils::Math::less(lhs.value(), rhs.value())
		: (!lhs.valid() && !rhs.valid()) ? true : lhs.valid();
}

template<typename T, typename U>
const bool operator<(const T &lhs, const SSUtils::Math::logarithm<U> &rhs)
{
	return rhs.valid() ? SSUtils::Math::less(lhs, rhs.value()) : true;
}

template<typename T, typename U>
const bool operator<(const SSUtils::Math::logarithm<T> &lhs, const U &rhs)
{
	return lhs.valid() ? SSUtils::Math::less(lhs.value(), rhs) : false;
}

template<typename T, typename U>
const bool operator<=(const SSUtils::Math::logarithm<T> &lhs, const SSUtils::Math::logarithm<U> &rhs)
{
	return (lhs.valid() && rhs.valid()) ? SSUtils::Math::lessEqual(lhs.value(), rhs.value())
		: (!lhs.valid() && !rhs.valid()) ? true : lhs.valid();
}

template<typename T, typename U>
const bool operator<=(const T &lhs, const SSUtils::Math::logarithm<U> &rhs)
{
	return rhs.valid() ? SSUtils::Math::lessEqual(lhs, rhs.value()) : true;
}

template<typename T, typename U>
const bool operator<=(const SSUtils::Math::logarithm<T> &lhs, const U &rhs)
{
	return lhs.valid() ? SSUtils::Math::lessEqual(lhs.value(), rhs) : false;
}

template<typename T, typename U>
const bool operator>(const SSUtils::Math::logarithm<T> &lhs, const SSUtils::Math::logarithm<U> &rhs)
{
	return (lhs.valid() && rhs.valid()) ? SSUtils::Math::big(lhs.value(), rhs.value())
		: (!lhs.valid() && !rhs.valid()) ? true : lhs.valid();
}

template<typename T, typename U>
const bool operator>(const T &lhs, const SSUtils::Math::logarithm<U> &rhs)
{
	return rhs.valid() ? SSUtils::Math::big(lhs, rhs.value()) ? true;
}

template<typename T, typename U>
const bool operator>(const SSUtils::Math::logarithm<T> &lhs, const U &rhs)
{
	return lhs.valid() ? SSUtils::Math::big(lhs.value(), rhs) : false;
}

template<typename T, typename U>
const bool operator>=(const SSUtils::Math::logarithm<T> &lhs, const SSUtils::Math::logarithm<U> &rhs)
{
	return (lhs.valid() && rhs.valid()) ? SSUtils::Math::bigEqual(lhs.value(), rhs.value())
		: (!lhs.valid() && !rhs.valid()) ? true : lhs.valid();
}

template<typename T, typename U>
const bool operator>=(const T &lhs, const SSUtils::Math::logarithm<U> &rhs)
{
	return rhs.valid() ? SSUtils::Math::bigEqual(lhs, rhs.value()) ? true;
}

template<typename T, typename U>
const bool operator>=(const SSUtils::Math::logarithm<T> &lhs, const U &rhs)
{
	return lhs.valid() ? SSUtils::Math::bigEqual(lhs.value(), rhs) : false;
}

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

template<typename T>
SSUtils::Math::logarithm<T> operator*(const SSUtils::Math::logarithm<T> &lhs, const T &rhs)
{
	return SSUtils::Math::logarithm<T>(lhs.base(), static_cast<T>(pow(lhs.antilogarithm(), rhs)));
}
