#pragma once

#include "_pri_real_global.h"
#include "DataUtils.h"
#include "StringUtils.h"
#include <limits>

namespace SSUtils
{
	namespace Math
	{
		template<bool Signed>
		class IntegerWrapper : public integer
		{
		public:
			typedef integer value_type;
			typedef IntegerWrapper self_type;

			// constructors
			IntegerWrapper(void)
				: value_type(0) 
			{
				setDigit(DefaultDigits);
			};
			IntegerWrapper(const self_type &ano) = default;
			IntegerWrapper(self_type &&ano) = default;

			template<typename T>
			IntegerWrapper(const T &ano, const uint32 digits = 0)
				: value_type(0)
			{
				assign(ano);
				setDigit(digits);
			};
			template<>
			IntegerWrapper(const std::string &str, const uint32 digits)
				: value_type(str)
			{
				setDigit(digits);
			};
			template<>
			IntegerWrapper(const Block &block, const uint32 digits)
				: value_type(String::HexStringSuffix + Data::toHexString(block))
			{
				setDigit(digits);
			}
			template<>
			IntegerWrapper(const value_type &ano, const uint32 digits)
				: value_type(ano)
			{
				setDigit(digits);
			};

			IntegerWrapper(value_type &&ano, const uint32 digits = 0)
				: value_type(std::move(ano))
			{
				setDigit(digits);
			};

			// destructor
			~IntegerWrapper(void) = default;

			// generators
			template<typename T>
			static std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> generate(const T &value)
			{
				IntegerWrapper ret(value);
				return ret;
			}
			template<typename T>
			static std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> generate(const T &value)
			{
				IntegerWrapper ret;
				ret.assign(value);
				return ret;
			}
			template<>
			static IntegerWrapper generate<Block>(const Block &value)
			{
				IntegerWrapper ret(value);
				return ret;
			}

			// operator =
			self_type &operator=(const self_type &rhs) = default;
			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator=(const T &rhs)
			{
				value_type::operator=(rhs);
				setDigit(0);
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator=(const T &rhs)
			{
				assign(rhs);
				setDigit(0);
				return *this;
			}
			template<>
			self_type &operator=<Block>(const Block &rhs)
			{
				assign(String::HexStringSuffix + Data::toHexString(rhs));
				setDigit(0);
				return *this;
			}

			// other operators
			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator+=(const T &rhs)
			{
				value_type::operator+=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator+=(const T &rhs)
			{
				value_type::operator+=(static_cast<value_type>(rhs));
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator-=(const T &rhs)
			{
				value_type::operator-=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator-=(const T &rhs)
			{
				value_type::operator-=(static_cast<value_type>(rhs));
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator*=(const T &rhs)
			{
				value_type::operator*=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator*=(const T &rhs)
			{
				value_type::operator*=(static_cast<value_type>(rhs));
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator/=(const T &rhs)
			{
				value_type::operator/=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator/=(const T &rhs)
			{
				value_type::operator/=(static_cast<value_type>(rhs));
				limit();
				return *this;
			}
			self_type &operator++(void)
			{
				value_type::operator++();
				limit();
				return *this;
			}
			self_type &operator--(void)
			{
				value_type::operator--();
				limit();
				return *this;
			}
			self_type operator++(int)
			{
				self_type ret(*this);
				++ret;
				return ret;
			}
			self_type operator--(int)
			{
				self_type ret(*this);
				--ret;
				return ret;
			}

			template<typename T, typename = std::enable_if_t<Data::ConversionChecker<T, value_type>::value>>
			self_type &operator%=(const T &rhs)
			{
				assign(mod(*this, rhs));
				limit();
				return *this;
			}
			template<typename T, typename = std::enable_if_t<Data::ConversionChecker<T, value_type>::value>>
			self_type &operator&=(const T &rhs)
			{
				value_type::operator&=(rhs);
				limit();
				return *this;
			}
			template<typename T, typename = std::enable_if_t<Data::ConversionChecker<T, value_type>::value>>
			self_type &operator|=(const T &rhs)
			{
				value_type::operator|=(rhs);
				limit();
				return *this;
			}
			template<typename T, typename = std::enable_if_t<Data::ConversionChecker<T, value_type>::value>>
			self_type &operator^=(const T &rhs)
			{
				value_type::operator^=(rhs);
				limit();
				return *this;
			}
			template<typename T, typename = std::enable_if_t<Data::ConversionChecker<T, value_type>::value>>
			self_type &operator<<=(const T &rhs)
			{
				value_type::operator<<=(rhs);
				limit();
				return *this;
			}
			template<typename T, typename = std::enable_if_t<Data::ConversionChecker<T, value_type>::value>>
			self_type &operator>>=(const T &rhs)
			{
				value_type::operator>>=(rhs);
				limit();
				return *this;
			}

			void setDigit(const uint32 digits)
			{
				m_digits = digits;
				auto value = getMaxAndMin<Signed>(digits);
				m_maxValue = value.first;
				m_minValue = value.second;
				limit();
			}

			value_type &value(void) { return *this; }
			const value_type &value(void) const { return *this; }

			std::string toString(const std::ios_base::fmtflags flags = 0) { return str(m_digits, flags); }
			Block toBlock(void) { return Data::fromHexString(toString(std::ios_base::hex)); }
			int8 toInt8(void) { return convert_to<int8>(); }
			uint8 toUInt8(void) { return convert_to<uint8>(); }
			int16 toInt16(void) { return convert_to<int16>(); }
			uint16 toUInt16(void) { return convert_to<uint16>(); }
			int32 toInt32(void) { return convert_to<int32>(); }
			uint32 toUInt32(void) { return convert_to<uint32>(); }
			int64 toInt64(void) { return convert_to<int64>(); }
			uint64 toUInt64(void) { return convert_to<uint64>(); }
			int128 toInt128(void) { return convert_to<int128>(); }
			uint128 toUInt128(void) { return convert_to<uint128>(); }
			int256 toInt256(void) { return convert_to<int256>(); }
			uint256 toUInt256(void) { return convert_to<uint256>(); }
			int512 toInt512(void) { return convert_to<int512>(); }
			uint512 toUInt512(void) { return convert_to<uint512>(); }
			int1024 toInt1024(void) { return convert_to<int1024>(); }
			uint1024 toUInt1024(void) { return convert_to<uint1024>(); }
			integer toInteger(void) { return convert_to<integer>(); }
			dec50 toDec50(void) { return convert_to<dec50>(); }
			dec100 toDec100(void) { return convert_to<dec100>(); }
			template<uint32 Digits>
			decimal<Digits> toDecimal(void) { return convert_to<decimal<Digits>>(); }
			template<typename T>
			T get(void) { return convert_to<T>(); }

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
						assign(mod(value(), range));
					}
				}
				else if (m_minValue != 0)
				{
					if (value() <= m_minValue)
					{
						assign(mod(value(), range));
					}
				}
			}

		private:
			uint32 m_digits;
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
