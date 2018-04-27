#pragma once

#include "_pri_real_global.h"
#include "DataUtils.h"
#include <limits>

namespace SSUtils
{
	namespace Math
	{
		template<bool Signed>
		class IntegerWrapper
		{
		public:
			typedef integer value_type;

			IntegerWrapper(void)
				: m_value(0) 
			{
				setDigit(DefaultDigits);
			};
			IntegerWrapper(const IntegerWrapper &ano) = default;
			IntegerWrapper(IntegerWrapper &&ano) = default;
			IntegerWrapper(const value_type &ano, const uint32 digits = DefaultDigits)
				: m_value(ano)
			{
				setDigit(digits);
			};
			IntegerWrapper(value_type &&ano, const uint32 digits = DefaultDigits)
				: m_value(std::move(ano))
			{
				setDigit(digits);
			};
			template<typename T, typename = std::enable_if_t<!std::is_same_v<T, value_type> && Data::ConversionChecker<T, value_type>::value>>
			IntegerWrapper(const T &ano, const uint32 digits = DefaultDigits)
				: m_value(ano)
			{
				setDigit(digits);
			}
			template<typename T, typename = std::enable_if_t<!std::is_same_v<T, value_type> && Data::ConversionChecker<T, value_type>::value>>
			IntegerWrapper(T &&ano, const uint32 digits = DefaultDigits)
				: m_value(std::move(ano))
			{
				setDigit(digits);
			}
			IntegerWrapper &operator=(const IntegerWrapper &rhs) = default;
			IntegerWrapper &operator=(IntegerWrapper &&rhs) = default;
			IntegerWrapper &operator=(const value_type &rhs)
			{
				m_value = rhs;
				limit();
				return *this;
			}
			IntegerWrapper &operator=(value_type &&rhs)
			{
				m_value = std::move(rhs);
				limit();
				return *this;
			}
			template<typename T, typename = std::enable_if_t<!std::is_same_v<T, value_type> && Data::ConversionChecker<T, value_type>::value>>
			IntegerWrapper &operator=(const T &rhs)
			{
				m_value = rhs;
				limit();
				return *this;
			}
			template<typename T, typename = std::enable_if_t<!std::is_same_v<T, value_type> && Data::ConversionChecker<T, value_type>::value>>
			IntegerWrapper &operator=(T &&rhs)
			{
				m_value = std::move(rhs);
				limit();
				return *this;
			}
			~IntegerWrapper(void) = default;

			template<typename T>
			IntegerWrapper &operator+=(const T &rhs)
			{
				m_value += rhs;
				limit();
				return *this;
			}
			template<typename T>
			IntegerWrapper &operator-=(const T &rhs)
			{
				m_value -= rhs;
				limit();
				return *this;
			}
			template<typename T>
			IntegerWrapper &operator*=(const T &rhs)
			{
				m_value *= rhs;
				limit();
				return *this;
			}
			template<typename T>
			IntegerWrapper &operator/=(const T &rhs)
			{
				m_value /= rhs;
				limit();
				return *this;
			}
			IntegerWrapper &operator++(void)
			{
				m_value++;
				limit();
				return *this;
			}
			IntegerWrapper &operator--(void)
			{
				m_value--;
				limit();
				return *this;
			}
			IntegerWrapper operator++(int)
			{
				IntegerWrapper ret(*this);
				++ret;
				return ret;
			}
			IntegerWrapper operator--(int)
			{
				IntegerWrapper ret(*this);
				--ret;
				return ret;
			}

			template<typename T>
			IntegerWrapper& operator%=(const T &rhs)
			{
				m_value %= rhs;
				limit();
				return *this;
			}
			template<typename T>
			IntegerWrapper& operator&=(const T &rhs)
			{
				m_value &= rhs;
				limit();
				return *this;
			}
			template<typename T>
			IntegerWrapper& operator|=(const T &rhs)
			{
				m_value |= rhs;
				limit();
				return *this;
			}
			template<typename T>
			IntegerWrapper& operator^=(const T &rhs)
			{
				m_value ^= rhs;
				limit();
				return *this;
			}
			template<typename T>
			IntegerWrapper& operator<<=(const T &rhs)
			{
				m_value <<= rhs;
				limit();
				return *this;
			}
			template<typename T>
			IntegerWrapper& operator>>=(const T &rhs)
			{
				m_value >>= rhs;
				limit();
				return *this;
			}

			void setDigit(const uint32 digits)
			{
				auto value = getMaxAndMin<Signed>(digits);
				m_maxValue = value.first;
				m_minValue = value.second;
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
			integer getInteger(void) { return m_value.convert_to<integer>(); }
			template<typename T>
			T get(void) { return m_value.convert_to<T>(); }

		private:
			template<bool _Signed>
			static std::pair<value_type, value_type> getMaxAndMin(const uint32 digits)
			{
				return std::pair<value_type, value_type>();
			}
			template<>
			static std::pair<value_type, value_type> getMaxAndMin<true>(const uint32 digits)
			{
				if (digits == 0)
				{
					return std::make_pair(value_type(0), value_type(0));
				}
				else
				{
					auto value = pow(value_type(10), digits);
					return std::make_pair(value, -value);
				}
			}
			template<>
			static std::pair<value_type, value_type> getMaxAndMin<false>(const uint32 digits)
			{
				if (digits == 0)
				{
					return std::make_pair(value_type(0), value_type(-1));
				}
				else
				{
					auto value = pow(value_type(10), digits);
					return std::make_pair(value, value_type(-1));
				}
			}

			void limit(void)
			{
				const value_type range(m_maxValue - m_minValue);
				if (m_maxValue != 0)
				{
					if (value() >= m_maxValue)
					{
						m_value = mod(value(), range);
					}
				}
				else if (m_minValue != 0)
				{
					if (value() <= m_minValue)
					{
						m_value = mod(value(), range);
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

namespace std
{
	namespace std
	{
		template<bool Signed>
		class numeric_limits<SSUtils::Math::IntegerWrapper<Signed>>
			: public numeric_limits<typename SSUtils::Math::IntegerWrapper<Signed>::value_type>
		{};
	};
};
