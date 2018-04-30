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
			typedef std::enable_if_t<Digits != 0, typename DecimalWrapper<Digits>::value_type> decimal_type;
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

			template<typename T>
			RationalWrapper(const T &ano)
				: value_type(0), m_numerator(0), m_denominator(0)
			{
				assign(ano);
				refresh();
			}
			template<>
			RationalWrapper(const std::string &str)
				: value_type(0)
			{
				if (RegexChecker(str))
				{
					value_type::assign(str);
				}
				refresh();
			}
			template<>
			RationalWrapper(const Block &block)
				: RationalWrapper(String::base64Decode(Data::toString(block)))
			{
				refresh();
			}
			template<>
			RationalWrapper(const base_type &ano)
				: value_type(ano)
			{
				refresh();
			}
			template<>
			RationalWrapper(const value_type &ano)
				: value_type(ano)
			{
				refresh();
			}
			template<bool Signed>
			RationalWrapper(const IntegerWrapper<Signed> &ano)
				: value_type(ano.value())
			{
				refresh();
			}

			template<typename T>
			RationalWrapper(const T &numerator, const T &denominator)
				: value_type(0), m_numerator(0), m_denominator(0)
			{
				refresh(numerator, denominator);
			}
			template<>
			RationalWrapper(const std::string &numerator, const std::string &denominator)
				: value_type(0), m_numerator(0), m_denominator(0)
			{
				auto r1(String::isInteger(numerator)), r2(String::isInteger(denominator));
				if (r1 && r2)
				{
					refresh(base_type(numerator), base_type(denominator));
				}
				else if (r1)
				{
					refresh(base_type(numerator), base_type(0));
				}
				else if (r2)
				{
					refresh(base_type(0), base_type(denominator));
				}
			}	
			template<>
			RationalWrapper(const Block &numerator, const Block &denominator)
				: RationalWrapper(String::HexStringSuffix + Data::toHexString(numerator), String::HexStringSuffix + Data::toHexString(denominator))
			{
			}
			template<>
			RationalWrapper(const base_type &numerator, const base_type &denominator)
				: value_type(0), m_numerator(0), m_denominator(0)
			{
				refresh(numerator, denominator);
			}
			template<bool Signed>
			RationalWrapper(const IntegerWrapper<Signed> &numerator, const IntegerWrapper<Signed> &denominator)
				: value_type(0), m_numerator(0), m_denominator(0)
			{
				refresh(numerator, denominator);
			}

			// destructor
			~RationalWrapper(void) = default;

			// generators
			template<typename T>
			static std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> generate(const T &value)
			{
				self_type ret(value);
				return ret;
			}
			template<typename T>
			static std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> generate(const T &value)
			{
				self_type ret(value);
				return ret;
			}
			template<>
			static self_type generate<std::string>(const std::string &value)
			{
				self_type ret(value);
				return ret;
			}
			template<>
			static self_type generate<Block>(const Block &value)
			{
				self_type ret(value);
				return ret;
			}
			template<bool Signed>
			static self_type generate(const IntegerWrapper<Signed> &value)
			{
				self_type ret(value.value());
				return ret;
			}
			template<typename T>
			static std::enable_if_t<Data::ConversionChecker<T, base_type>::value, self_type> generate(const T &numerator, const T &denominator)
			{
				self_type ret(numerator, denominator);
				return ret;
			}
			template<typename T>
			static std::enable_if_t<!Data::ConversionChecker<T, base_type>::value, self_type> generate(const T &numerator, const T &denominator)
			{
				self_type ret(static_cast<base_type>(numerator), static_cast<base_type>(denominator));
				return ret;
			}
			template<>
			static self_type generate<std::string>(const std::string &numerator, const std::string &denominator)
			{
				self_type ret(numerator, denominator);
				return ret;
			}
			template<>
			static self_type generate<Block>(const Block &numerator, const Block &denominator)
			{
				self_type ret(numerator, denominator);
				return ret;
			}
			template<bool Signed>
			static self_type generate(const IntegerWrapper<Signed> &numerator, const IntegerWrapper<Signed> &denominator)
			{
				self_type ret(numerator.value(), denominator.value());
				return ret;
			}

			// assign and swap
			self_type &assign(const self_type &ano)
			{
				value_type::assign(ano.value());
				refresh();
				return *this;
			}
			template<bool Signed>
			self_type &assign(const IntegerWrapper<Signed> &ano)
			{
				value_type::assign(ano.value());
				refresh();
				return *this;
			}
			template<bool Signed>
			self_type &assign(const IntegerWrapper<Signed> &numerator, const IntegerWrapper<Signed> &denominator)
			{
				refresh(numerator.value(), denominator.value());
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type>, self_type> &assign(const T &ano)
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
				assign(String::base64Decode(Data::toString(block)));
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type>, self_type> &assign(const T &numerator, const T &denominator)
			{
				refresh(numerator, denominator);
			}
			template<>
			self_type &assign<std::string>(const std::string &numerator, const std::string &denominator)
			{
				auto r1(String::isInteger(numerator)), r2(String::isInteger(denominator));
				if (r1 && r2)
				{
					refresh(base_type(numerator), base_type(denominator));
				}
				else if (r1)
				{
					refresh(base_type(numerator), base_type(0));
				}
				else if (r2)
				{
					refresh(base_type(0), base_type(denominator));
				}
			}
			template<>
			self_type &assign<Block>(const Block &numerator, const Block &denominator)
			{
				assign(String::HexStringSuffix + Data::toHexString(numerator), String::HexStringSuffix + Data::toHexString(denominator));
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

			// operator =
			self_type &operator=(const self_type &rhs) = default;
			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator=(const T &rhs)
			{
				value_type::operator=(rhs);
				refresh();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator=(const T &rhs)
			{
				value_type::assign(rhs);
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
				operator=(String::base64Decode(Data::toString(block)));
				return *this;
			}

			// other operators
			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator+=(const T &rhs)
			{
				value_type::operator+=(rhs);
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
			self_type &operator+=<std::string>(const std::string &rhs)
			{
				if (RegexChecker(rhs))
				{
					value_type::operator+=(value_type(rhs));
					refresh();
				}
				return *this;
			}
			template<>
			self_type &operator+=<Block>(const Block &rhs)
			{
				operator+=(String::base64Decode(Data::toString(block)));
				return *this;
			}

			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator-=(const T &rhs)
			{
				value_type::operator-=(rhs);
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
			self_type &operator-=<std::string>(const std::string &rhs)
			{
				if (RegexChecker(rhs))
				{
					value_type::operator-=(value_type(rhs));
					refresh();
				}
				return *this;
			}
			template<>
			self_type &operator-=<Block>(const Block &rhs)
			{
				operator-=(String::base64Decode(Data::toString(block)));
				return *this;
			}

			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator*=(const T &rhs)
			{
				value_type::operator*=(rhs);
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
			self_type &operator*=<std::string>(const std::string &rhs)
			{
				if (RegexChecker(rhs))
				{
					value_type::operator+*=(value_type(rhs));
					refresh();
				}
				return *this;
			}
			template<>
			self_type &operator*=<Block>(const Block &rhs)
			{
				operator*=(String::base64Decode(Data::toString(block)));
				return *this;
			}

			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> &operator/=(const T &rhs)
			{
				value_type::operator/=(rhs);
				refresh();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> &operator/=(const T &rhs)
			{
				value_type::operator/=(static_cast<value_type>(rhs));
				refresh();
				return *this;
			}
			template<>
			self_type &operator/=<std::string>(const std::string &rhs)
			{
				if (RegexChecker(rhs))
				{
					value_type::operator/=(value_type(rhs));
					refresh();
				}
				return *this;
			}
			template<>
			self_type &operator/=<Block>(const Block &rhs)
			{
				operator/=(String::base64Decode(Data::toString(block)));
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

			// set and get
			const bool valid(void) const { return denominator() != 0; }

			const base_type &getNumerator(void) const { return m_numerator; }
			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, base_type>::value, void> setNumerator(const T &numerator) { refresh(base_type(numerator), m_denominator); }
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, base_type>::value, void> setNumerator(const T &numerator) { refresh(static_cast<base_type>(numerator), m_denominator); }
			const base_type &getDenominator(void) const { return m_denominator; }
			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, base_type>::value, void> setDenominator(const T &denominator) { refresh(m_numerator, base_type(denominator)); }
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, base_type>::value, void> setDenominator(const T &denominator) { refresh(m_numerator, static_cast<base_type>(denominator)); }

			const value_type &value(void) const { return *this; }
			const decimal_type value_dec(void) const { return convert_to<decimal_type>(); }

			// translators
			std::string toString(const std::ios_base::fmtflags flags = 0) const { return str(0, flags); }
			Block toBlock(void) const { return Data::fromString(String::base64Encode(toString())); }
			float toFloat(void) const { return convert_to<float>(); }
			double toDouble(void) const { return convert_to<double>(); }
			float32 toFloat32(void) const { return convert_to<float32>(); }
			float64 toFloat64(void) const { return convert_to<float64>(); }
			float128 toFloat128(void) const { return convert_to<float128>(); }
			float256 toFloat256(void) const { return convert_to<float256>(); }
			dec50 toDec50(void) const { return convert_to<dec50>(); }
			dec100 toDec100(void) const { return convert_to<dec100>(); }
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, decimal<Digits>> toDecimal(void) const { return convert_to<decimal<Digits>>(); }
			template<typename T>
			T get(void) const { return convert_to<T>(); }

			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, decimal<Digits>> round(void) const
			{
				static const decimal_type offset = decimal_type(5) * pow(decimal_type(10), -(static_cast<int64>(Digits) + 1));
				return (value_dec() + offset).convert_to<decimal<Digits>>();
			}
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, decimal<Digits>> floor(void) const
			{
				return value_dec().convert_to<decimal<Digits>>();
			}
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, decimal<Digits>> ceil(void) const
			{
				static const decimal_type offset = pow(decimal_type(10), -static_cast<int64>(Digits));
				return (value_dec() + offset).convert_to<decimal<Digits>>();
			}

			Integer roundToInteger(void) const { return static_cast<Integer>(boost::math::round(value_dec())); }
			Integer ceilToInteger(void) const { return floorToInteger() + 1; }
			Integer floorToInteger(void) const { return static_cast<Integer>(value_dec()); }

		private:
			void clear(void)
			{
				m_numerator.assign(0);
				m_denominator.assign(0);
				value_type::assign(0);
			}
			void refresh(void)
			{
				m_numerator.assign(boost::multiprecision::numerator(*this));
				m_denominator.assign(boost::multiprecision::denominator(*this));
			}
			template<typename T>
			typename std::enable_if_t<Data::ConversionChecker<T, base_type>::value, void> refresh(const T &numerator, const T &denominator)
			{
				if (denominator != 0)
				{
					value_type::assign(numerator);
					value_type::operator/=(base_type(denominator));
					refresh();
				}
				else
				{
					clear();
				}
			}
			template<typename T>
			typename std::enable_if_t<!Data::ConversionChecker<T, base_type>::value, void> refresh(const T &numerator, const T &denominator)
			{
				if (denominator != 0)
				{
					value_type::assign(numerator);
					value_type::operator/=(static_cast<base_type>(denominator));
					refresh();
				}
				else
				{
					clear();
				}
			}
			template<>
			void refresh<base_type>(const base_type &numerator, const base_type &denominator)
			{
				if (denominator != 0)
				{
					value_type::assign(numerator);
					value_type::operator/=(denominator);
					refresh();
				}
				else
				{
					clear();
				}
			}
			template<bool Signed>
			void refresh(const IntegerWrapper<Signed> &numerator, const IntegerWrapper<Signed> &denominator)
			{
				refresh(numerator.value(), denominator.value());
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
