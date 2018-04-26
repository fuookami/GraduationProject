#pragma once

#include "_pri_math_global.h"
#include "DataUtils.h"
#include <limits>

namespace SSUtils
{
	namespace Math
	{
		template<bool Signed>
		class integer_wrapper
		{
		public:
			typedef bigInt value_type;

			integer_wrapper(void)
				: m_value(0) 
			{
				setDigit(DefaultDigits);
			};
			integer_wrapper(const integer_wrapper &ano) = default;
			integer_wrapper(integer_wrapper &&ano) = default;
			integer_wrapper(const value_type &ano, const uint32 digits = DefaultDigits)
				: m_value(ano)
			{
				setDigit(digits);
			};
			integer_wrapper(value_type &&ano, const uint32 digits = DefaultDigits)
				: m_value(std::move(ano))
			{
				setDigit(digits);
			};
			template<typename U, typename = std::enable_if_t<!std::is_same_v<U, value_type> && ConversionChecker<U, value_type>::value>>
			integer_wrapper(const U &ano, const uint32 digits = DefaultDigits)
				: m_value(ano)
			{
				setDigit(digits);
			}
			template<typename T, typename = std::enable_if_t<!std::is_same_v<T, value_type> && ConversionChecker<T, value_type>::value>>
			integer_wrapper(T &&ano, const uint32 digits = DefaultDigits)
				: m_value(std::move(ano))
			{
				setDigit(digits);
			}
			integer_wrapper &operator=(const integer_wrapper &rhs) = default;
			integer_wrapper &operator=(integer_wrapper &&rhs) = default;
			integer_wrapper &operator=(const value_type &rhs)
			{
				m_value = rhs;
				limit();
				return *this;
			}
			integer_wrapper &operator=(value_type &&rhs)
			{
				m_value = std::move(rhs);
				limit();
				return *this;
			}
			template<typename T, typename = std::enable_if_t<!std::is_same_v<T, value_type> && ConversionChecker<T, value_type>::value>>
			integer_wrapper &operator=(const T &rhs)
			{
				m_value = rhs;
				limit();
				return *this;
			}
			template<typename T, typename = std::enable_if_t<!std::is_same_v<T, value_type> && ConversionChecker<T, value_type>::value>>
			integer_wrapper &operator=(T &&rhs)
			{
				m_value = std::move(rhs);
				limit();
				return *this;
			}
			~integer_wrapper(void) = default;

			template<typename T>
			integer_wrapper &operator+=(const T &rhs)
			{
				m_value += rhs;
				limit();
				return *this;
			}
			template<typename T>
			integer_wrapper &operator-=(const T &rhs)
			{
				m_value -= rhs;
				limit();
				return *this;
			}
			template<typename T>
			integer_wrapper &operator*=(const T &rhs)
			{
				m_value *= rhs;
				limit();
				return *this;
			}
			template<typename T>
			integer_wrapper &operator/=(const T &rhs)
			{
				m_value /= rhs;
				limit();
				return *this;
			}
			integer_wrapper &operator++(void)
			{
				m_value++;
				limit();
				return *this;
			}
			integer_wrapper &operator--(void)
			{
				m_value--;
				limit();
				return *this;
			}
			integer_wrapper operator++(int)
			{
				integer_wrapper ret(*this);
				++ret;
				return ret;
			}
			integer_wrapper operator--(int)
			{
				integer_wrapper ret(*this);
				--ret;
				return ret;
			}

			template<typename T>
			integer_wrapper& operator%=(const T &rhs)
			{
				m_value %= rhs;
				limit();
				return *this;
			}
			template<typename T>
			integer_wrapper& operator&=(const T &rhs)
			{
				m_value &= rhs;
				limit();
				return *this;
			}
			template<typename T>
			integer_wrapper& operator|=(const T &rhs)
			{
				m_value |= rhs;
				limit();
				return *this;
			}
			template<typename T>
			integer_wrapper& operator^=(const T &rhs)
			{
				m_value ^= rhs;
				limit();
				return *this;
			}
			template<typename T>
			integer_wrapper& operator<<=(const T &rhs)
			{
				m_value <<= rhs;
				limit();
				return *this;
			}
			template<typename T>
			integer_wrapper& operator>>=(const T &rhs)
			{
				m_value >>= rhs;
				limit();
				return *this;
			}

			void setDigit(const uint32 digits)
			{
				if (digits == 0)
				{
					m_maxValue = m_minValue = 0;
				}
				else
				{
					m_maxValue = pow(value_type(10), digits);
					m_minValue = Signed ? (-m_maxValue) : value_type(-1);
				}
				limit();
			}

			value_type &value(void) { return m_value; }
			const value_type &value(void) const { return m_value; }
			operator value_type(void) const { return m_value; }

			int8 getInt8(void) { return m_value.convert_to<int8>(); }
			uint8 getUInt8(void) { return m_value.convert_to<uint8>(); }
			int16 getInt16(void) { return m_value.convert_to<int16>(); }
			uint16 getUInt16(void) { return m_value.convert_to<uint16>(); }
			int32 getInt32(void) { return m_value.convert_to<int32>(); }
			uint32 getUInt32(void) { return m_value.convert_to<uint32>(); }
			int64 getInt64(void) { return m_value.convert_to<int64>(); }
			uint64 getUInt64(void) { return m_value.convert_to<uint64>(); }
			int128 getInt128(void) { return m_value.convert_to<int128>(); }
			uint128 getUInt128(void) { return m_value.convert_to<uint128>(); }
			int256 getInt256(void) { return m_value.convert_to<int256>(); }
			uint256 getUInt256(void) { return m_value.convert_to<uint256>(); }
			int512 getInt512(void) { return m_value.convert_to<int512>(); }
			uint512 getUInt512(void) { return m_value.convert_to<uint512>(); }
			int1024 getInt1024(void) { return m_value.convert_to<int1024>(); }
			uint1024 getUInt1024(void) { return m_value.convert_to<uint1024>(); }
			bigInt getBigInt(void) { return m_value.convert_to<bigInt>(); }
			template<typename T>
			T get(void) { return m_value.convert_to<T>(); }

		private:
			void limit(void)
			{
				if (m_maxValue != 0 && m_minValue != 0)
				{
					const value_type range(m_maxValue - m_minValue);
					if (value() >= m_maxValue)
					{
						m_value -= (range * (value() / range));
					}
					if (value() <= m_minValue)
					{
						m_value += (range * (value() / range));
					}
				}
			}

		private:
			value_type m_value;
			value_type m_maxValue;
			value_type m_minValue;
		};
	};
};
