#pragma once

#include "_pri_real_global.h"
#include "DataUtils.h"
#include "StringUtils.h"
#include <limits>
#include <boost/math/special_functions.hpp>

namespace SSUtils
{
	namespace Math
	{
		template<uint32 Digits> 
		class DecimalWrapper : public decimal<Digits>
		{
		public:
			typedef std::enable_if_t<Digits != 0, decimal<Digits>> value_type;
			typedef DecimalWrapper self_type;

			// constructors
			DecimalWrapper(void)
				: value_type(0), m_base(0), m_index(0), m_offset(1) {};
			DecimalWrapper(const self_type &ano) = default;
			DecimalWrapper(self_type &&ano) = default;

			template<typename T>
			DecimalWrapper(const T &ano, const int32 index = 0)
				: value_type(0), m_base(0), m_index(index), m_offset(0)
			{
				m_base.assign(ano);
				refresh(index);
			}
			template<>
			DecimalWrapper(const std::string &str, const int32 index)
				: value_type(0), m_base(0), m_index(index), m_offset(0)
			{
				if (String::isDecimal(str))
				{
					m_base.assign(str);
				}
				refresh(index);
			}
			template<>
			DecimalWrapper(const Block &block, const int32 index)
				: DecimalWrapper(String::base64Decode(Data::toString(block)), index)
			{
			}
			template<>
			DecimalWrapper(const value_type &ano, const int32 index)
				: value_type(0), m_base(ano), m_index(index), m_offset(0)
			{
				refresh(index);
			}

			// destructor
			~DecimalWrapper(void) = default;

			// generators
			template<typename T>
			static std::enable_if_t<Data::ConversionChecker<T, value_type>::value, self_type> generate(const T &value, const int32 index = 1)
			{
				self_type ret(value, index);
				return ret;
			}
			template<typename T>
			static std::enable_if_t<!Data::ConversionChecker<T, value_type>::value, self_type> generate(const T &value, const int32 index = 1)
			{
				self_type ret;
				ret.m_base.assign(value);
				ret.refresh(index);
				return ret;
			}
			template<>
			static self_type generate<std::string>(const std::string &value, const int32 index)
			{
				self_type ret(value, index);
				return ret;
			}
			template<>
			static self_type generate<Block>(const Block &value, const int32 index)
			{
				self_type ret(value, index);
				return ret;
			}

			// assign and swap
			self_type &assign(const self_type &ano)
			{
				value_type::assign(ano.value());
				m_base.assign(ano.m_base);
				refresh(ano.m_index);
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type>, self_type> &assign(const T &ano, const int32 index = 0)
			{
				m_base.assign(ano);
				refresh(index);
				return *this;
			}
			template<>
			self_type &assign<std::string>(const std::string &ano, const int32 index)
			{
				if (String::isDecimal(ano))
				{
					m_base.assign(ano);
				}
				else
				{
					m_base.assign(0);
				}
				refresh(index);
				return *this;
			}
			template<>
			self_type &assign<Block>(const Block &ano, const int32 index)
			{
				assign(String::base64Decode(Data::toString(block)), index);
				return *this;
			}
			self_type &swap(value_type &ano)
			{
				value_type::swap(ano);
				refresh();
				return *this;
			}
			self_type &swap(self_type &ano)
			{
				value_type::swap(ano);
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
				if (String::isDecimal(rhs))
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
			self_type &operator+=<Block>(const Block &rhs)
			{
				value_type::operator+=(value_type(String::base64Decode(Data::toString(block))));
				refresh();
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
			self_type &operator-=<Block>(const Block &rhs)
			{
				value_type::operator-=(value_type(String::base64Decode(Data::toString(block))));
				refresh();
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
			self_type &operator*=<Block>(const Block &rhs)
			{
				value_type::operator*=(value_type(String::base64Decode(Data::toString(block))));
				refresh();
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
			self_type &operator/=<Block>(const Block &rhs)
			{
				value_type::operator/=(value_type(String::base64Decode(Data::toString(block))));
				refresh();
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
			const int32 index(void) const { return m_index; }
			const value_type &offset(void) const { return m_offset; }
			void setIndex(const int32 index) { refresh(); refresh(index); }

			const value_type &base(void) const { return m_base; }
			void setBase(const value_type &base) { refresh(base); }

			const value_type &value(void) const { return *this; }

			// translators
			std::string toString(const std::ios_base::fmtflags flags = std::ios::fixed) const { return this->str(Digits, flags); }
			Block toBlock(const std::ios_base::fmtflags flags = std::ios::fixed) const { return Data::fromString(String::base64Encode(toString(flags))); }
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
				static const value_type offset = value_type(5) * pow(value_type(10), -(static_cast<int64>(Digits) + 1));
				return (value() + offset).convert_to<decimal<Digits>>();
			}
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, decimal<Digits>> floor(void) const
			{
				return value().convert_to<decimal<Digits>>();
			}
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, decimal<Digits>> ceil(void) const
			{
				static const value_type offset = pow(value_type(10), -static_cast<int64>(Digits));
				return (value() + offset).convert_to<decimal<Digits>>();
			}

			Integer roundToInteger(void) const { return static_cast<Integer>(boost::math::round(value())); }
			Integer ceilToInteger(void) const { return floorToInteger() + 1; }
			Integer floorToInteger(void) const { return static_cast<Integer>(value()); }

		private:
			void refresh(void)
			{
				m_base = value() / m_offset;
			}
			void refresh(const value_type &base)
			{
				value_type::assign(base * offset);
				m_base.assign(base);
			}
			void refresh(const int32 index)
			{
				m_offset = pow(value_type(10), index);
				value_type::assign(m_base * m_offset);
				m_index = index;
			}

		private:
			value_type m_base;
			int32 m_index;
			value_type m_offset;
		};
	};
};

namespace std
{
	template<SSUtils::uint32 Digits>
	class numeric_limits<SSUtils::Math::DecimalWrapper<Digits>>
		: public numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_dec_float<Digits>>>
	{};
};
