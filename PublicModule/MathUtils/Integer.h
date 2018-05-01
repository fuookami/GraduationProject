#pragma once

#include "_pri_real_global.h"
#include "DataUtils.h"
#include "StringUtils.h"
#include <limits>
#include <algorithm>

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

			IntegerWrapper(const value_type &ano, const uint32 digits = 0)
				: value_type(ano)
			{
				setDigit(digits);
			}
			IntegerWrapper(const std::string &str, const uint32 digits = 0)
				: value_type(0)
			{
				if (String::isInteger(str))
				{
					value_type::assign(str);
				}
				setDigit(digits);
			}
			IntegerWrapper(const Block &block, const uint32 digits = 0)
				: IntegerWrapper(String::HexStringSuffix + Data::toHexString(block), digits)
			{
			}

			template<typename T>
			IntegerWrapper(const T &ano, const uint32 digits = 0)
				: value_type(0)
			{
				value_type::assign(ano);
				setDigit(digits);
			}

			// destructor
			~IntegerWrapper(void) = default;

			// generators
			template<typename T>
			static std::enable_if_t<!std::is_same_v<T, self_type>, self_type> generate(const T &value, const uint32 digits = 0)
			{
				self_type ret(value, digits);
				return ret;
			}
			template<>
			static self_type generate<std::string>(const std::string &value, const uint32 digits)
			{
				self_type ret(value, digits);
				return ret;
			}
			template<>
			static self_type generate<Block>(const Block &value, const uint32 digits)
			{
				self_type ret(value, digits);
				return ret;
			}

			// assign and swap
			self_type &assign(const self_type &ano)
			{
				value_type::assign(ano.value());
				setDigit(ano.m_digits);
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type>, self_type> &assign(const T &ano, const uint32 digits = 0)
			{
				value_type::assign(ano);
				setDigit(digits);
				return *this;
			}
			template<>
			self_type &assign<std::string>(const std::string &str, const uint32 digits)
			{
				if (String::isInteger(str))
				{
					value_type::assign(str);
				}
				else
				{
					value_type::assign(0);
				}
				setDigit(digits);
				return *this;
			}
			template<>
			self_type &assign<Block>(const Block &ano, const uint32 digits)
			{
				assign(String::HexStringSuffix + Data::toHexString(ano), digits);
				return *this;
			}
			self_type &swap(value_type &ano)
			{
				value_type::swap(ano);
				limit();
				return *this;
			}
			self_type &swap(self_type &ano)
			{
				value_type::swap(ano);
				std::swap(m_digits, ano.m_digits);
				refresh();
				return *this;
			}

			// operator =
			self_type &operator=(const self_type &rhs) = default;
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && Data::ConversionChecker<T, value_type>::value, self_type> &operator=(const T &rhs)
			{
				value_type::operator=(rhs);
				setDigit(0);
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && !Data::ConversionChecker<T, value_type>::value, self_type> &operator=(const T &rhs)
			{
				value_type::assign(rhs);
				setDigit(0);
				return *this;
			}
			template<>
			self_type &operator=<std::string>(const std::string &rhs)
			{
				if (String::isInteger(rhs))
				{
					value_type::assign(rhs);
				}
				else
				{
					value_type::assign(0);
				}
				setDigit(0);
				return *this;
			}
			template<>
			self_type &operator=<Block>(const Block &rhs)
			{
				operator=(String::HexStringSuffix + Data::toHexString(rhs));
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
			template<bool _Signed>
			self_type &operator+=(const IntegerWrapper<_Signed> &rhs)
			{
				value_type::operator+=(rhs.value());
				limit();
				return *this;
			}
			template<>
			self_type &operator+=<std::string>(const std::string &rhs)
			{
				if (String::isInteger(rhs))
				{
					value_type::operator+=(value_type(rhs));
					limit();
				}
				return *this;
			}
			template<>
			self_type &operator+=<Block>(const Block &rhs)
			{
				operator+=(String::HexStringSuffix + Data::toHexString(rhs));
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
			template<bool _Signed>
			self_type &operator-=(const IntegerWrapper<_Signed> &rhs)
			{
				value_type::operator-=(rhs.value());
				limit();
				return *this;
			}
			template<>
			self_type &operator-=<std::string>(const std::string &rhs)
			{
				if (String::isInteger(rhs))
				{
					value_type::operator-=(value_type(rhs));
					limit();
				}
				return *this;
			}
			template<>
			self_type &operator-=<Block>(const Block &rhs)
			{
				operator+=(String::HexStringSuffix + Data::toHexString(rhs));
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
			template<bool _Signed>
			self_type &operator*=(const IntegerWrapper<_Signed> &rhs)
			{
				value_type::operator*=(rhs.value());
				limit();
				return *this;
			}
			template<>
			self_type &operator*=<std::string>(const std::string &rhs)
			{
				if (String::isInteger(rhs))
				{
					value_type::operator*=(value_type(rhs));
					limit();
				}
				return *this;
			}
			template<>
			self_type &operator*=<Block>(const Block &rhs)
			{
				operator*=(String::HexStringSuffix + Data::toHexString(rhs));
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
			template<bool _Signed>
			self_type &operator/=(const IntegerWrapper<_Signed> &rhs)
			{
				value_type::operator/=(rhs.value());
				limit();
				return *this;
			}
			template<>
			self_type &operator/=<std::string>(const std::string &rhs)
			{
				if (String::isInteger(rhs))
				{
					value_type::operator/=(value_type(rhs));
					limit();
				}
				return *this;
			}
			template<>
			self_type &operator/=<Block>(const Block &rhs)
			{
				operator/=(String::HexStringSuffix + Data::toHexString(rhs));
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

			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator%=(const T &rhs)
			{
				assign(mod(*this, rhs));
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator%=(const T &rhs)
			{
				value_type::operator&=(rhs);
				limit();
				return *this;
			}
			template<bool _Signed>
			self_type &operator%=(const IntegerWrapper<_Signed> &rhs)
			{
				value_type::assign(mod(*this, rhs.value()));
				limit();
				return *this;
			}
			template<>
			self_type &operator%=<std::string>(const std::string &rhs)
			{
				if (String::isInteger(rhs))
				{
					value_type::operator%=(value_type(rhs));
					limit();
				}
				return *this;
			}
			template<>
			self_type &operator%=<Block>(const Block &rhs)
			{
				operator%=(String::HexStringSuffix + Data::toHexString(rhs));
				return *this;
			}

			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator|=(const T &rhs)
			{
				value_type::operator|=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator|=(const T &rhs)
			{
				value_type::operator|=(static_cast<value_type>(rhs));
				limit();
				return *this;
			}
			template<bool _Signed>
			self_type &operator|=(const IntegerWrapper<_Signed> &rhs)
			{
				value_type::operator|=(rhs.value());
				limit();
				return *this;
			}
			template<>
			self_type &operator|=<std::string>(const std::string &rhs)
			{
				if (String::isInteger(rhs))
				{
					value_type::operator|=(value_type(rhs));
					limit();
				}
				return *this;
			}
			template<>
			self_type &operator|=<Block>(const Block &rhs)
			{
				operator|=(String::HexStringSuffix + Data::toHexString(rhs));
				return *this;
			}

			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator^=(const T &rhs)
			{
				value_type::operator^=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator^=(const T &rhs)
			{
				value_type::operator^=(static_cast<value_type>(rhs));
				limit();
				return *this;
			}
			template<bool _Signed>
			self_type &operator^=(const IntegerWrapper<_Signed> &rhs)
			{
				value_type::operator^=(rhs.value());
				limit();
				return *this;
			}
			template<>
			self_type &operator^=<std::string>(const std::string &rhs)
			{
				if (String::isInteger(rhs))
				{
					value_type::operator^=(value_type(rhs));
					limit();
				}
				return *this;
			}
			template<>
			self_type &operator^=<Block>(const Block &rhs)
			{
				operator^=(String::HexStringSuffix + Data::toHexString(rhs));
				return *this;
			}

			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator<<=(const T &rhs)
			{
				value_type::operator<<=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator<<=(const T &rhs)
			{
				value_type::operator<<=(static_cast<value_type>(rhs));
				limit();
				return *this;
			}
			template<bool _Signed>
			self_type &operator<<=(const IntegerWrapper<_Signed> &rhs)
			{
				value_type::operator<<=(rhs.value());
				limit();
				return *this;
			}
			template<>
			self_type &operator<<=<std::string>(const std::string &rhs)
			{
				if (String::isInteger(rhs))
				{
					value_type::operator<<=(value_type(rhs));
					limit();
				}
				return *this;
			}
			template<>
			self_type &operator<<=<Block>(const Block &rhs)
			{
				operator<<=(String::HexStringSuffix + Data::toHexString(rhs));
				return *this;
			}

			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator>>=(const T &rhs)
			{
				value_type::operator>>=(rhs);
				limit();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator>>=(const T &rhs)
			{
				value_type::operator>>=(static_cast<value_type>(rhs));
				limit();
				return *this;
			}
			template<bool _Signed>
			self_type &operator>>=(const IntegerWrapper<_Signed> &rhs)
			{
				value_type::operator>>=(rhs.value());
				limit();
				return *this;
			}
			template<>
			self_type &operator>>=<std::string>(const std::string &rhs)
			{
				if (String::isInteger(rhs))
				{
					value_type::operator>>=(value_type(rhs));
					limit();
				}
				return *this;
			}
			template<>
			self_type &operator>>=<Block>(const Block &rhs)
			{
				operator>>=(String::HexStringSuffix + Data::toHexString(rhs));
				return *this;
			}

			// set and get
			void setDigit(const uint32 digits)
			{
				m_digits = digits;
				refresh();
				limit();
			}
			const uint32 getDigits(void) { return m_digits; }
			const value_type &getMinValue(void) { return m_minValue; }
			const value_type &getMaxValue(void) { return m_maxValue; }

			const value_type &value(void) const { return *this; }

			// translators
			std::string toString(const std::ios_base::fmtflags flags = 0) const { return str(m_digits, flags); }
			Block toBlock(void) const { return Data::fromHexString(toString(std::ios_base::hex)); }
			int8 toInt8(void) const { return convert_to<int8>(); }
			uint8 toUInt8(void) const { return convert_to<uint8>(); }
			int16 toInt16(void) const { return convert_to<int16>(); }
			uint16 toUInt16(void) const { return convert_to<uint16>(); }
			int32 toInt32(void) const { return convert_to<int32>(); }
			uint32 toUInt32(void) const { return convert_to<uint32>(); }
			int64 toInt64(void) const { return convert_to<int64>(); }
			uint64 toUInt64(void) const { return convert_to<uint64>(); }
			int128 toInt128(void) const { return convert_to<int128>(); }
			uint128 toUInt128(void) const { return convert_to<uint128>(); }
			int256 toInt256(void) const { return convert_to<int256>(); }
			uint256 toUInt256(void) const { return convert_to<uint256>(); }
			int512 toInt512(void) const { return convert_to<int512>(); }
			uint512 toUInt512(void) const { return convert_to<uint512>(); }
			int1024 toInt1024(void) const { return convert_to<int1024>(); }
			uint1024 toUInt1024(void) const { return convert_to<uint1024>(); }
			integer toInteger(void) const { return convert_to<integer>(); }
			dec50 toDec50(void) const { return convert_to<dec50>(); }
			dec100 toDec100(void) const { return convert_to<dec100>(); }
			template<uint32 Digits = DefaultDigits>
			decimal<Digits> toDecimal(void) const { return convert_to<decimal<Digits>>(); }
			template<typename T>
			std::enable_if_t<!std::is_same_v<T, value_type>, T> get(void) const { return convert_to<T>(); }
			template<typename T>
			std::enable_if_t<std::is_same_v<T, value_type>, const T &> get(void) const { return *this; }

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

			void refresh(void)
			{
				auto pair = getMaxAndMin<Signed>(m_digits);
				m_maxValue = pair.first;
				m_minValue = pair.second;
			}
			void limit(void)
			{
				const value_type range(m_maxValue - m_minValue);
				if (m_maxValue != 0 && value() >= m_maxValue)
				{
					value_type::assign(mod(value(), range));
				}
				else if (m_minValue != 0 && value() <= m_minValue)
				{
					value_type::assign(m_minValue == -1 ? abs(value()) : mod(value(), range));
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
	template<bool Signed>
	class numeric_limits<SSUtils::Math::IntegerWrapper<Signed>>
		: public numeric_limits<typename SSUtils::Math::IntegerWrapper<Signed>::value_type>
	{};
};
