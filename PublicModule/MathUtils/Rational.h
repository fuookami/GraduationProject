#pragma once

#include "Integer.h"
#include "Decimal.h"
#include "DataUtils.h"
#include "StringUtils.h"
#include <limits>

namespace SSUtils
{
	namespace Math
	{
		template<uint32 Digits>
		class RationalWrapper : public rational
		{
		public:
			typedef integer base_type;
			typedef rational value_type;
			typedef typename std::enable_if_t<Digits != 0, typename DecimalWrapper<Digits>::value_type> decimal_type;
			typedef RationalWrapper self_type;

			static const String::RegexChecker RegexChecker;

			// constructors
			RationalWrapper(void)
				: value_type(0)
			{
				refresh();
			}
			RationalWrapper(const self_type &ano) = default;
			RationalWrapper(self_type &&ano) = default;

			RationalWrapper(const base_type &ano)
				: value_type(ano)
			{
				refresh();
			}
			RationalWrapper(const value_type &ano)
				: value_type(ano)
			{
				refresh();
			}
			RationalWrapper(const std::string &str)
				: value_type(0)
			{
				if (RegexChecker(str))
				{
					value_type::assign(str);
				}
				else if (String::isInteger(str))
				{
					value_type::assign(base_type(str));
				}
				refresh();
			}
			RationalWrapper(const Block &block)
				: RationalWrapper(String::base64Decode(Data::toString(block)))
			{
				refresh();
			}
			template<typename T>
			RationalWrapper(const T &ano)
				: value_type(0)
			{
				value_type::assign(ano);
				refresh();
			}
			template<bool Signed>
			RationalWrapper(const IntegerWrapper<Signed> &ano)
				: value_type(ano.get<value_type>())
			{
				refresh();
			}
			template<uint32 _Digits>
			RationalWrapper(const RationalWrapper<_Digits> &ano)
				: RationalWrapper(ano.get<value_type>())
			{
				refresh();
			}

			RationalWrapper(const base_type &numerator, const base_type &denominator)
				: value_type(numerator, denominator), m_numerator(0), m_denominator(1)
			{
				refresh();
			}
			RationalWrapper(const std::string &numerator, const std::string &denominator)
				: value_type(0), m_numerator(0), m_denominator(1)
			{
				if (String::isInteger(numerator))
				{
					m_numerator.assign(numerator);
				}
				if (String::isInteger(denominator))
				{
					m_denominator.assign(denominator);
				}
				value_type::assign(value_type(m_numerator, m_denominator));
			}
			RationalWrapper(const Block &numerator, const Block &denominator)
				: RationalWrapper(String::HexStringPrefix + Data::toHexString(numerator), String::HexStringPrefix + Data::toHexString(denominator))
			{
			}
			template<typename T, typename U>
			RationalWrapper(const T &numerator, const U &denominator)
				: RationalWrapper(generate(numerator, denominator))
			{
			}
			template<bool Signed1, bool Signed2>
			RationalWrapper(const IntegerWrapper<Signed1> &numerator, const IntegerWrapper<Signed2> &denominator)
				: RationalWrapper(numerator.get<base_type>(), denominator.get<base_type>())
			{
			}

			// destructor
			~RationalWrapper(void) = default;

			// generators: to do
			template<typename T>
			static typename std::enable_if_t<!std::is_same_v<T, self_type> && Data::ConversionChecker<T, base_type>::value, self_type> generate(const T &value)
			{
				self_type ret = self_type(base_type(value));
				return ret;
			}
			template<typename T>
			static typename std::enable_if_t<!std::is_same_v<T, self_type> && !Data::ConversionChecker<T, base_type>::value, self_type> generate(const T &value)
			{
				self_type ret = self_type(static_cast<base_type>(value));
				return ret;
			}
			template<>
			static self_type generate<base_type>(const base_type &value)
			{
				self_type ret = self_type(value);
				return ret;
			}
			template<>
			static self_type generate<value_type>(const value_type &value)
			{
				self_type ret = self_type(value);
				return ret;
			}
			template<>
			static self_type generate<std::string>(const std::string &value)
			{
				self_type ret = self_type(value);
				return ret;
			}
			template<>
			static self_type generate<Block>(const Block &value)
			{
				self_type ret = self_type(value);
				return ret;
			}
			template<bool Signed>
			static self_type generate(const IntegerWrapper<Signed> &value)
			{
				self_type ret = self_type(value.get<base_type>());
				return ret;
			}

			template<typename T, typename U>
			static typename std::enable_if_t<!std::is_same_v<T, self_type> && !std::is_same_v<U, self_type> && !std::is_same_v<T, U> && Data::ConversionChecker<T, base_type>::value && Data::ConversionChecker<U, base_type>::value, self_type> generate(const T &numerator, const U &denominator)
			{
				self_type ret = self_type(base_type(numerator), base_type(denominator));
				return ret;
			}
			template<typename T>
			static typename std::enable_if_t<!std::is_same_v<T, self_type> && !std::is_same_v<T, value_type> && Data::ConversionChecker<T, base_type>::value, self_type> generate(const T &numerator, const T &denominator)
			{
				self_type ret = self_type(base_type(numerator), base_type(denominator));
				return ret;
			}
			template<typename T>
			static typename std::enable_if_t<!std::is_same_v<T, self_type> && !std::is_same_v<T, value_type> && !Data::ConversionChecker<T, base_type>::value, self_type> generate(const T &numerator, const T &denominator)
			{
				self_type ret = self_type(static_cast<base_type>(numerator), static_cast<base_type>(denominator));
				return ret;
			}
			template<>
			static self_type generate<base_type>(const base_type &numerator, const base_type &denominator)
			{
				self_type ret = self_type(numerator, denominator);
				return ret;
			}
			template<>
			static self_type generate<std::string>(const std::string &numerator, const std::string &denominator)
			{
				self_type ret = self_type(numerator, denominator);
				return ret;
			}
			template<>
			static self_type generate<Block>(const Block &numerator, const Block &denominator)
			{
				self_type ret = self_type(numerator, denominator);
				return ret;
			}
			template<bool Signed>
			static self_type generate(const IntegerWrapper<Signed> &numerator, const IntegerWrapper<Signed> &denominator)
			{
				self_type ret = self_type(numerator.get<base_type>(), denominator.get<base_type>());
				return ret;
			}

			// assign and swap
			self_type &assign(const self_type &ano)
			{
				value_type::assign(ano.value());
				refresh();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type>, self_type> &assign(const T &ano)
			{
				value_type::assign(ano);
				refresh();
				return *this;
			}
			template<>
			self_type &assign<base_type>(const base_type &ano)
			{
				value_type::assign(ano);
				refresh();
				return *this;
			}
			template<>
			self_type &assign<value_type>(const value_type &ano)
			{
				value_type::assign(ano);
				refresh();
				return *this;
			}
			template<>
			self_type &assign<std::string>(const std::string &ano)
			{
				if (RegexChecker(ano))
				{
					value_type::assign(ano);
				}
				else if (String::isInteger(ano))
				{
					value_type::assign(base_type(ano));
				}
				else
				{
					value_type::assign(0);
				}
				refresh();
				return *this;
			}
			template<>
			self_type &assign<Block>(const Block &ano)
			{
				assign(String::base64Decode(Data::toString(ano)));
				return *this;
			}
			template<bool Signed>
			self_type &assign(const IntegerWrapper<Signed> &ano)
			{
				value_type::assign(ano.get<base_type>());
				refresh();
				return *this;
			}
			template<uint32 _Digits>
			static typename std::enable_if_t<_Digits != Digits, self_type> &assign(const RationalWrapper<_Digits> &ano)
			{
				value_type::assign(ano.value());
				refresh();
				return *this;
			}
			
			template<typename T, typename U>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && !std::is_same_v<U, self_type> && !std::is_same_v<T, U> && Data::ConversionChecker<T, base_type>::value && Data::ConversionChecker<U, base_type>::value, self_type> &assign(const T &numerator, const U &denominator)
			{
				value_type::assign(value_type(base_type(numerator), base_type(denominator)));
				refresh();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && !std::is_same_v<T, value_type> && Data::ConversionChecker<T, base_type>::value, self_type> &assign(const T &numerator, const T &denominator)
			{
				value_type::assign(value_type(base_type(numerator), base_type(denominator)));
				refresh();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && !std::is_same_v<T, value_type> && !Data::ConversionChecker<T, base_type>::value, self_type> &assign(const T &numerator, const T &denominator)
			{
				value_type::assign(value_type(static_cast<base_type>(numerator), static_cast<base_type>(denominator)));
				refresh();
				return *this;
			}
			template<>
			self_type &assign<base_type>(const base_type &numerator, const base_type &denominator)
			{
				value_type::assign(value_type(numerator, denominator));
				refresh();
				return *this;
			}
			template<>
			self_type &assign<std::string>(const std::string &numerator, const std::string &denominator)
			{
				auto r1(String::isInteger(numerator)), r2(String::isInteger(denominator));
				if (r1 && r2)
				{
					value_type::assign(value_type(base_type(numerator), base_type(denominator)));
				}
				else if (r1)
				{
					value_type::assign(value_type(base_type(numerator), base_type(1)));
				}
				else if (r2)
				{
					value_type::assign(value_type(base_type(0), base_type(denominator)));
				}
				refresh();
				return *this;
			}
			template<>
			self_type &assign<Block>(const Block &numerator, const Block &denominator)
			{
				assign(String::HexStringPrefix + Data::toHexString(numerator), String::HexStringPrefix + Data::toHexString(denominator));
			}
			template<bool Signed1, bool Signed2>
			self_type &assign(const IntegerWrapper<Signed1> &numerator, const IntegerWrapper<Signed2> &denominator)
			{
				value_type::assign(value_type(numerator.get<base_type>(), denominator.get<base_type>()));
			}

			self_type &swap(value_type &ano)
			{
				value_type::swap(ano);
				refresh();
				return *this;
			}
			self_type &swap(self_type &ano)
			{
				value_type::swap(ano.value());
				refresh();
				return *this;
			}
			template<uint32 _Digits>
			typename std::enable_if_t<_Digits != Digits, self_type> &swap(RationalWrapper<_Digits> &ano)
			{
				value_type::swap(dynamic_cast<value_type &>(ano));
				refresh();
				ano.refresh();
				return *this;
			}

			// operator =
			self_type &operator=(const self_type &rhs) = default;
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && Data::ConversionChecker<T, base_type>::value, self_type> &operator=(const T &rhs)
			{
				value_type::operator=(base_type(rhs));
				refresh();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && !Data::ConversionChecker<T, base_type>::value, self_type> &operator=(const T &rhs)
			{
				value_type::assign(static_cast<base_type>(rhs));
				refresh();
				return *this;
			}
			template<>
			self_type &operator=<base_type>(const base_type &rhs)
			{
				value_type::operator=(rhs);
				refresh();
				return *this;
			}
			template<>
			self_type &operator=<value_type>(const value_type &rhs)
			{
				value_type::operator=(rhs);
				refresh();
				return *this;
			}
			template<>
			self_type &operator=<std::string>(const std::string &rhs)
			{
				if (RegexChecker(rhs))
				{
					value_type::assign(rhs);
				}
				else if (String::isInteger(rhs))
				{
					value_type::assign(base_type(rhs));
				}
				else
				{
					value_type::assign(0);
				}
				refresh();
				return *this;
			}
			template<>
			self_type &operator=<Block>(const Block &rhs)
			{
				operator=(String::base64Decode(Data::toString(rhs)));
				return *this;
			}
			template<bool Signed>
			self_type &operator=(const IntegerWrapper<Signed> &rhs)
			{
				value_type::operator=(rhs.get<base_type>());
				refresh();
				return *this;
			}
			template<uint32 _Digits>
			typename std::enable_if_t<Digits != _Digits, self_type> &operator=(const RationalWrapper<_Digits> &rhs)
			{
				value_type::operator=(rhs.value());
				refresh();
				return *this;
			}

			// other operators
			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator+=(const T &rhs)
			{
				value_type::operator+=(value_type(rhs));
				refresh();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator+=(const T &rhs)
			{
				value_type::operator+=(static_cast<value_type>(rhs));
				refresh();
				return *this;
			}
			template<>
			self_type &operator+=<base_type>(const base_type &rhs)
			{
				value_type::operator+=(rhs);
				refresh();
				return *this;
			}
			template<>
			self_type &operator+=<value_type>(const value_type &rhs)
			{
				value_type::operator+=(rhs);
				refresh();
				return *this;
			}
			template<>
			self_type &operator+=<std::string>(const std::string &rhs)
			{
				if (RegexChecker(rhs))
				{
					value_type::operator+=(value_type(rhs));
					refresh();
				}
				else if (String::isInteger(rhs))
				{
					value_type::operator+=(base_type(rhs));
					refresh();
				}
				return *this;
			}
			template<>
			self_type &operator+=<Block>(const Block &rhs)
			{
				operator+=(String::base64Decode(Data::toString(rhs)));
				return *this;
			}
			template<bool Signed>
			self_type &operator+=(const IntegerWrapper<Signed> &rhs)
			{
				operator+=(rhs.get<base_type>());
				return *this;
			}
			template<uint32 _Digits>
			self_type &operator+=(const RationalWrapper<_Digits> &rhs)
			{
				operator+=(rhs.get<value_type>());
				return *this;
			}

			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator-=(const T &rhs)
			{
				value_type::operator-=(value_type(rhs));
				refresh();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator-=(const T &rhs)
			{
				value_type::operator-=(static_cast<value_type>(rhs));
				refresh();
				return *this;
			}
			template<>
			self_type &operator-=<base_type>(const base_type &rhs)
			{
				value_type::operator-=(rhs);
				refresh();
				return *this;
			}
			template<>
			self_type &operator-=<value_type>(const value_type &rhs)
			{
				value_type::operator-=(rhs);
				refresh();
				return *this;
			}
			template<>
			self_type &operator-=<std::string>(const std::string &rhs)
			{
				if (RegexChecker(rhs))
				{
					value_type::operator-=(value_type(rhs));
					refresh();
				}
				else if (String::isInteger(rhs))
				{
					value_type::operator-=(base_type(rhs));
					refresh();
				}
				return *this;
			}
			template<>
			self_type &operator-=<Block>(const Block &rhs)
			{
				operator-=(String::base64Decode(Data::toString(rhs)));
				return *this;
			}
			template<bool Signed>
			self_type &operator-=(const IntegerWrapper<Signed> &rhs)
			{
				operator-=(rhs.get<base_type>());
				return *this;
			}
			template<uint32 _Digits>
			self_type &operator-=(const RationalWrapper<_Digits> &rhs)
			{
				operator-=(rhs.get<value_type>());
				return *this;
			}

			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator*=(const T &rhs)
			{
				value_type::operator*=(value_type(rhs));
				refresh();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator*=(const T &rhs)
			{
				value_type::operator*=(static_cast<value_type>(rhs));
				refresh();
				return *this;
			}
			template<>
			self_type &operator*=<base_type>(const base_type &rhs)
			{
				value_type::operator*=(rhs);
				refresh();
				return *this;
			}
			template<>
			self_type &operator*=<value_type>(const value_type &rhs)
			{
				value_type::operator*=(rhs);
				refresh();
				return *this;
			}
			template<>
			self_type &operator*=<std::string>(const std::string &rhs)
			{
				if (RegexChecker(rhs))
				{
					value_type::operator*=(value_type(rhs));
					refresh();
				}
				else if (String::isInteger(rhs))
				{
					value_type::operator*=(base_type(rhs));
					refresh();
				}
				return *this;
			}
			template<>
			self_type &operator*=<Block>(const Block &rhs)
			{
				operator*=(String::base64Decode(Data::toString(rhs)));
				return *this;
			}
			template<bool Signed>
			self_type &operator*=(const IntegerWrapper<Signed> &rhs)
			{
				operator*=(rhs.get<base_type>());
				return *this;
			}
			template<uint32 _Digits>
			self_type &operator*=(const RationalWrapper<_Digits> &rhs)
			{
				operator*=(rhs.get<value_type>());
				return *this;
			}

			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator/=(const T &rhs)
			{
				operator/=(value_type(rhs));
				refresh();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator/=(const T &rhs)
			{
				operator/=(static_cast<value_type>(rhs));
				refresh();
				return *this;
			}
			template<>
			self_type &operator/=<base_type>(const base_type &rhs)
			{
				if (rhs == 0)
				{
					clear();
				}
				else
				{
					value_type::operator/=(rhs);
					refresh();
				}
				return *this;
			}
			template<>
			self_type &operator/=<value_type>(const value_type &rhs)
			{
				if (rhs == 0)
				{
					clear();
				}
				else
				{
					value_type::operator/=(rhs);
					refresh();
				}
				return *this;
			}
			template<>
			self_type &operator/=<std::string>(const std::string &rhs)
			{
				if (RegexChecker(rhs))
				{
					operator/=(value_type(rhs));
					refresh();
				}
				else if (String::isInteger(rhs))
				{
					operator/=(base_type(rhs));
					refresh();
				}
				return *this;
			}
			template<>
			self_type &operator/=<Block>(const Block &rhs)
			{
				operator/=(String::base64Decode(Data::toString(rhs)));
				return *this;
			}
			template<bool Signed>
			self_type &operator/=(const IntegerWrapper<Signed> &rhs)
			{
				operator/=(rhs.get<base_type>());
				return *this;
			}
			template<uint32 _Digits>
			self_type &operator/=(const RationalWrapper<_Digits> &rhs)
			{
				operator/=(rhs.get<value_type>());
				return *this;
			}

			self_type &operator++(void)
			{
				value_type::operator++();
				refresh();
				return *this;
			}
			self_type &operator--(void)
			{
				value_type::operator--();
				refresh();
				return *this;
			}
			self_type operator++(int)
			{
				self_type ret = self_type(*this);
				++ret;
				return ret;
			}
			self_type operator--(int)
			{
				self_type ret = self_type(*this);
				--ret;
				return ret;
			}

			// set and get
			const bool valid(void) const { return denominator() != 0; }

			const base_type &getNumerator(void) const { return m_numerator; }
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && Data::ConversionChecker<T, base_type>::value, void> setNumerator(const T &numerator) 
			{
				assign(base_type(numerator), m_denominator);
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && !Data::ConversionChecker<T, base_type>::value, void> setNumerator(const T &numerator) 
			{ 
				assign(static_cast<base_type>(numerator), m_denominator); 
			}
			template<>
			void setNumerator<base_type>(const base_type &numerator)
			{
				assign(numerator, m_denominator);
			}
			template<>
			void setNumerator<std::string>(const std::string &numerator)
			{
				if (String::isInteger(numerator))
				{
					assign(base_type(numerator), m_denominator);
				}
				else
				{
					assign(base_type(0), m_denominator);
				}
			}
			template<>
			void setNumerator<Block>(const Block &numerator)
			{
				setNumerator(String::HexStringPrefix + Data::toHexString(numerator));
			}
			template<bool Signed>
			void setNumerator(const IntegerWrapper<Signed> &numerator)
			{
				assign(numerator.value(), m_denominator);
			}

			const base_type &getDenominator(void) const { return m_denominator; }
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && Data::ConversionChecker<T, base_type>::value, void> setDenominator(const T &denominator)
			{ 
				assign(m_numerator, base_type(denominator)); 
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && !Data::ConversionChecker<T, base_type>::value, void> setDenominator(const T &denominator) 
			{ 
				assign(m_numerator, static_cast<base_type>(denominator));
			}
			template<>
			void setDenominator<base_type>(const base_type &denominator)
			{
				assign(m_numerator, denominator);
			}
			template<>
			void setDenominator<std::string>(const std::string &denominator)
			{
				if (String::isInteger(denominator))
				{
					assign(m_numerator, base_type(denominator));
				}
				else
				{
					assign(m_numerator, 0);
				}
			}
			template<>
			void setDenominator<Block>(const Block &denominator)
			{
				setDenominator(String::HexStringPrefix + Data::toHexString(numerator));
			}
			template<bool Signed>
			void setDenominator(const IntegerWrapper<Signed> &denominator)
			{
				assign(m_numerator, denominator.value());
			}

			const value_type &value(void) const { return *this; }
			decimal_type value_dec(void) const { return convert_to<decimal_type>(); }
			DecimalWrapper<Digits> value_dec_wrapper(void) const { return DecimalWrapper<Digits>(value); }
			operator decimal_type(void) const { return value_dec(); }

			// translators
			std::string toString(const std::ios_base::fmtflags flags = 0) const { return str(0, flags); }
			Block toBlock(void) const { return Data::fromString(String::base64Encode(toString())); }

			int8 toInt8(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<int8>(); }
			uint8 toUInt8(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<uint8>(); }
			int16 toInt16(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<int16>(); }
			uint16 toUInt16(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<uint16>(); }
			int32 toInt32(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<int32>(); }
			uint32 toUInt32(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<uint32>(); }
			int64 toInt64(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<int64>(); }
			uint64 toUInt64(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<uint64>(); }
			int128 toInt128(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<int128>(); }
			uint128 toUInt128(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<uint128>(); }
			int256 toInt256(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<int256>(); }
			uint256 toUInt256(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<uint256>(); }
			int512 toInt512(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<int512>(); }
			uint512 toUInt512(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<uint512>(); }
			int1024 toInt1024(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<int1024>(); }
			uint1024 toUInt1024(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<uint1024>(); }

			template<uint32 bits>
			intx<bits> toIntx(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<intx<bits>>(); }
			template<uint32 bits>
			uintx<bits> toIntx(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<uintx<bits>>(); }
			integer toInteger(const ToIntegerFlag flag = ToIntegerFlag::round) const { return toInteger(flag).convert_to<integer>(); }

			float toFloat(void) const { return convert_to<float>(); }
			double toDouble(void) const { return convert_to<double>(); }
			float32 toFloat32(void) const { return convert_to<float32>(); }
			float64 toFloat64(void) const { return convert_to<float64>(); }
			float128 toFloat128(void) const { return convert_to<float128>(); }
			float256 toFloat256(void) const { return convert_to<float256>(); }

			dec50 toDec50(void) const { return convert_to<dec50>(); }
			dec100 toDec100(void) const { return convert_to<dec100>(); }

			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<_Digits != 0, decimal<_Digits>> toDecimal(void) const { return convert_to<decimal<_Digits>>(); }
			template<>
			decimal<Digits> toDecimal<Digits>(void) const { return value_dec(); }
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<_Digits != 0, DecimalWrapper<_Digits>> toDecimalWrapper(void) const { return DecimalWrapper<_Digits>(toDecimal<_Digits>()); }
			template<>
			DecimalWrapper<Digits> toDecimalWrapper<Digits>(void) const { return DecimalWrapper<Digits>(value()); }

			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, value_type>, T> get(void) const { return convert_to<T>(); }
			template<typename T>
			typename std::enable_if_t<std::is_same_v<T, value_type>, const T &> get(void) const { return *this; }

			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, decimal<_Digits>> round(void) const
			{
				static const value_type offset = value_type(5) * pow(value_type(10), -(static_cast<int64>(_Digits) + 1));
				return (value() + offset).convert_to<decimal<_Digits>>();
			}
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, decimal<_Digits>> floor(void) const
			{
				return value().convert_to<decimal<_Digits>>();
			}
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, decimal<_Digits>> ceil(void) const
			{
				static const value_type offset = pow(value_type(10), -static_cast<int64>(_Digits));
				return (value() + offset).convert_to<decimal<_Digits>>();
			}

			integer toInteger(const ToIntegerFlag flag = ToIntegerFlag::round) { return flag == ToIntegerFlag::round ? roundToInteger() : ToIntegerFlag::ceil ? ceilToInteger() : floorToInteger(); }
			integer roundToInteger(void) const { return static_cast<integer>(boost::math::round(value_dec())); }
			integer ceilToInteger(void) const { return floorToInteger() + 1; }
			integer floorToInteger(void) const { return static_cast<integer>(value_dec()); }

			void clear(void)
			{
				value_type::assign(0);
				m_numerator.assign(0);
				m_denominator.assign(0);
			}
			void refresh(void)
			{
				m_numerator.assign(boost::multiprecision::numerator(*this));
				m_denominator.assign(boost::multiprecision::denominator(*this));
			}

		private:
			base_type m_numerator;
			base_type m_denominator;
		};

		template<uint32 Digits>
		const String::RegexChecker RationalWrapper<Digits>::RegexChecker(std::string("^-?(0|[1-9]\\d*)(.-?(0|[1-9]\\d*))?$"));
	};
};

namespace std
{
	template<SSUtils::uint32 Digits>
	class numeric_limits<SSUtils::Math::RationalWrapper<Digits>>
		: public numeric_limits<SSUtils::rational>
	{};
};
