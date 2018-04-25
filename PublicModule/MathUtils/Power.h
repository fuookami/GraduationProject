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

			power(const T &base = T(), const T &index = T())
				: m_base(base), m_index(index) {};
			power(const power &ano) = default;
			power(power &&ano) = default;
			template<typename U>
			explicit power(const power<U> &ano)
				: power(value_type(ano.base()), value_type(ano.index())) {};
			~power(void) = default;

			power &operator=(const power &rhs) = default;
			power &operator=(power &&rhs) = default;
			template<typename U>
			power &operator=(const power<U> &rhs)
			{
				m_base = value_type(rhs.base());
				m_index = value_type(rhs.index());
				return *this;
			}
			power &operator=(const T &base)
			{
				m_base = base;
				m_index = 1;
				return *this;
			}
			power &operator=(T &&base)
			{
				m_base = std::move(base);
				m_index = 1;
				return *this;
			}
			template<typename U>
			power &powEqual(const U &index)
			{
				m_index *= static_cast<T>(index);
				return *this;
			}

			const bool valid(void) { return !(zero(m_base) && zero(m_index)); }

			const T &base(void) const { return m_base; }
			void setBase(const T &base) { m_base = base; }
			void setBase(T &&base) { m_base = std::move(base); }
			T index(void) const { return m_index; }
			void setIndex(const T &index) { m_index = index; }
			void setIndex(T &&index) { m_index = std::move(index); }

			double value(void) const { return pow(static_cast<double>(m_base), static_cast<double>(m_index)); }
			operator double(void) const { return value(); }

		private:
			T m_base;
			T m_index;
		};

		template<>
		class power<float>
		{
		public:
			typedef float value_type;
			
			power(const value_type base = 0.0f, const value_type index = 0.0f)
				: m_base(base), m_index(index) {};
			power(const power &ano) = default;
			power(power &&ano) = default;
			template<typename T>
			explicit power(const power<T> &ano)
				: power(static_cast<value_type>(ano.base()), static_cast<value_type>(ano.index())) {};
			~power(void) = default;

			power &operator=(const power &rhs) = default;
			power &operator=(power &&rhs) = default;
			template<typename T>
			power &operator=(const power<T> &rhs)
			{
				m_base = static_cast<value_type>(rhs.base());
				m_index = static_cast<value_type>(rhs.index());
				return *this;
			}
			power &operator=(const value_type rhs)
			{
				m_base = rhs;
				m_index = 1.0f;
				return *this;
			}
			power &powEqual(const value_type rhs)
			{
				m_index *= rhs;
				return *this;
			}

			const bool valid(void) { return !(zero(m_base) && zero(m_index)); }

			const value_type base(void) const { return m_base; }
			void setBase(const value_type base) { m_base = base; }
			const value_type index(void) const { return m_index; }
			void setIndex(const value_type index) { m_index = index; }

			value_type value(void) const { return pow(m_base, m_index); }
			operator value_type(void) const { return value(); }

		private:
			value_type m_base;
			value_type m_index;
		};

		template<>
		class power<double>
		{
		public:
			typedef double value_type;

			power(const value_type base = 0.0f, const value_type index = 0.0f)
				: m_base(base), m_index(index) {};
			power(const power &ano) = default;
			power(power &&ano) = default;
			template<typename T>
			explicit power(const power<T> &ano)
				: power(static_cast<value_type>(ano.base()), static_cast<value_type>(ano.index())) {};
			~power(void) = default;

			power &operator=(const power &rhs) = default;
			power &operator=(power &&rhs) = default;
			template<typename T>
			power &operator=(const power<T> &rhs)
			{
				m_base = static_cast<value_type>(rhs.base());
				m_index = static_cast<value_type>(rhs.index());
				return *this;
			}
			power &operator=(const value_type rhs)
			{
				m_base = rhs;
				m_index = 1.0f;
				return *this;
			}
			power &powEqual(const value_type rhs)
			{
				m_index *= rhs;
				return *this;
			}

			const bool valid(void) { return !(zero(m_base) && zero(m_index)); }

			const value_type base(void) const { return m_base; }
			void setBase(const value_type base) { m_base = base; }
			const value_type index(void) const { return m_index; }
			void setIndex(const value_type index) { m_index = index; }

			value_type value(void) const { return pow(m_base, m_index); }
			operator value_type(void) const { return value(); }

		private:
			value_type m_base;
			value_type m_index;
		};

		template<>
		class power<long double>
		{
		public:
			typedef long double value_type;

			power(const value_type base = 0.0f, const value_type index = 0.0f)
				: m_base(base), m_index(index) {};
			power(const power &ano) = default;
			power(power &&ano) = default;
			template<typename T>
			explicit power(const power<T> &ano)
				: power(static_cast<value_type>(ano.base()), static_cast<value_type>(ano.index())) {};
			~power(void) = default;

			power &operator=(const power &rhs) = default;
			power &operator=(power &&rhs) = default;
			template<typename T>
			power &operator=(const power<T> &rhs)
			{
				m_base = static_cast<value_type>(rhs.base());
				m_index = static_cast<value_type>(rhs.index());
				return *this;
			}
			power &operator=(const value_type rhs)
			{
				m_base = rhs;
				m_index = 1.0f;
				return *this;
			}
			power &powEqual(const value_type rhs)
			{
				m_index *= rhs;
				return *this;
			}

			const bool valid(void) { return !(zero(m_base) && zero(m_index)); }

			const value_type base(void) const { return m_base; }
			void setBase(const value_type base) { m_base = base; }
			const value_type index(void) const { return m_index; }
			void setIndex(const value_type index) { m_index = index; }

			value_type value(void) const { return pow(m_base, m_index); }
			operator value_type(void) const { return value(); }

		private:
			value_type m_base;
			value_type m_index;
		};
	};
};

template<typename T>
SSUtils::Math::power<T> pow(const SSUtils::Math::power<T> &base, const T &index)
{
	return SSUtils::Math::power<T>(base.base(), base.index() * index);
}
