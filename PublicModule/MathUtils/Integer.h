#pragma once

#include "_pri_math_global.h"
#include "DataUtils.h"
#include <limits>

namespace SSUtils
{
	namespace Math
	{
		template<uint32 Digits, bool Signed = true>
		class _integer_backend : public bigInt
		{
		public:
			typedef bigInt value_type;
			static const _integer_backend max_value = pow(value_type(10), Digits);
			static const _integer_backend min_value = Signed ? (-max_value) ? -1;

			_integer_backend(void)
				: value_type(0) {};
			_integer_backend(const integer_backend &ano) = default;
			_integer_backend(integer_backend &&ano) = default;
			_integer_backend(const value_type &ano)
				: value_type(ano) {
				limit();
			};
			_integer_backend(value_type &&ano)
				: value_type(std::move(ano)) {
				limit();
			};
			template<typename T, typename = std::enable_if_t<Data::ConversionChecker<T, value_type>::value>>
			_integer_backend(const T &ano)
				: value_type(ano) {
				limit();
			};
			template<typename T, typename = std::enable_if_t<Data::ConversionChecker<T, value_type>::value>>
			_integer_backend(T &&ano)
				: value_type(std::move(ano)) {
				limit();
			};
			_integer_backend &operator=(const integer_backend &rhs) = default;
			_integer_backend &operator=(integer_backend &&rhs) = default;
			_integer_backend &operator=(const value_type &rhs)
			{
				value_type::operator=(rhs);
				limit();
				return *this;
			}
			_integer_backend &operator=(value_type &&rhs)
			{
				value_type::operator=(std::move(rhs));
				limit();
				return *this;
			}
			template<typename T, typename = std::enable_if_t<Data::ConversionChecker<T, value_type>::value>>
			_integer_backend &operator=(const T &ano)
			{
				value_type::operator=(ano);
				limit();
				return *this;
			}
			template<typename T, typename = std::enable_if_t<Data::ConversionChecker<T, value_type>::value>>
			_integer_backend &operator=(T &&ano)
			{
				value_type::operator=(std::move(ano));
				limit();
				return *this;
			}
			~_integer_backend(void) = default;

			template<typename T>
			_integer_backend &operator+=(const T &rhs)
			{
				value_type::operator+=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			_integer_backend &operator-=(const T &rhs)
			{
				value_type::operator-=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			_integer_backend &operator*=(const T &rhs)
			{
				value_type::operator*=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			_integer_backend &operator/=(const T &rhs)
			{
				value_type::operator/=(rhs);
				limit();
				return *this;
			}
			_integer_backend &operator++(void)
			{
				value_type::operator++();
				limit();
				return *this;
			}
			_integer_backend &operator--(void)
			{
				value_type::operator--();
				limit();
				return *this;
			}
			_integer_backend operator++(int)
			{
				_integer_backend ret(*this);
				++ret;
				return ret;
			}
			_integer_backend operator--(int)
			{
				_integer_backend ret(*this);
				--ret;
				return ret;
			}

			template<typename T>
			_integer_backend& operator%=(const T &rhs)
			{
				value_type::operator%=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			_integer_backend& operator&=(const T &rhs)
			{
				value_type::operator&=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			_integer_backend& operator|=(const T &rhs)
			{
				value_type::operator|=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			_integer_backend& operator^=(const T &rhs)
			{
				value_type::operator^=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			_integer_backend& operator<<=(const T &rhs)
			{
				value_type::operator<<=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			_integer_backend& operator>>=(const T &rhs)
			{
				value_type::operator>>=(rhs);
				limit();
				return *this;
			}

			value_type &value(void) { return *this; }
			const value_type &value(void) const { return *this; }
			operator value_type(void) const { return value_type(*this); }

		private:
			void limit(void)
			{
				static const bigInt range(max_value - min_value);
				if (value() >= max_value)
				{
					bigInt::operator-=(range * (value() / range));
				}
				if (value() <= min_value)
				{
					bigInt::operator+=(range * (value() / range));
				}
			}
		};
	};
};

namespace std
{
	template<uint32 Digits, bool Signed>
	class numeric_limits<SSUtils::Math::_integer_backend<Digits, Signed>>
		: public _Num_int_base
	{
	public:
		typedef SSUtils::Math::_integer_backend<Digits, Signed> type;

		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = Signed;
		static constexpr int digits = SSUtils::Math::log(2, Digits) + 1;
		static constexpr int digits10 = Digits;

		static constexpr type min() noexcept { return 0; }
		static constexpr type max() noexcept { return type::max_value; }
		static constexpr type lowest() noexcept { return type::min_value; }
		static constexpr type epsilon() noexcept { return 0; }
		static constexpr type round_error() noexcept { return 0; }
		static constexpr type denorm_min() noexcept { return 0; }
		static constexpr type infinity() noexcept { return 0; }
		static constexpr type quiet_NaN() noexcept { return 0; }
		static constexpr type signaling_NaN() noexcept { return 0; }
	};
};
