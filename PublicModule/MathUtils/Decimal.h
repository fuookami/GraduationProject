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

			DecimalWrapper(const value_type &ano, const int32 index = 0)
				: value_type(0), m_base(ano), m_index(0), m_offset(1)
			{
				refresh(index);
			}
			DecimalWrapper(const std::string &str, const int32 index = 0)
				: value_type(0), m_base(0), m_index(0), m_offset(1)
			{
				if (String::isDecimal(str))
				{
					m_base.assign(str);
				}
				refresh(index);
			}
			DecimalWrapper(const Block &block, const int32 index = 0)
				: DecimalWrapper(String::base64Decode(Data::toString(block)), index)
			{
			}

			template<typename T>
			DecimalWrapper(const std::enable_if_t<!std::is_same_v<T, self_type>, T> &ano, const int32 index = 0)
				: value_type(0), m_base(0), m_index(0), m_offset(1)
			{
				m_base.assign(ano);
				refresh(index);
			}
			template<bool Signed>
			DecimalWrapper(const IntegerWrapper<Signed> &ano, const int32 index = 0)
				: DecimalWrapper(ano.get<value_type>())
			{
			}
			template<uint32 _Digits>
			DecimalWrapper(const std::enable_if_t<_Digits != Digits, DecimalWrapper<_Digits>> &ano)
				: value_type(0), m_base(ano.get<value_type>()), m_index(0), m_offset(1)
			{
				refresh(ano.m_index);
			}

			// destructor
			~DecimalWrapper(void) = default;

			// generators
			template<typename T>
			static std::enable_if_t<!std::is_same_v<T, self_type>, self_type> generate(const T &value, const int32 index = 1)
			{
				self_type ret(value, index);
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
			template<bool Signed>
			static self_type generate(const IntegerWrapper<Signed> &value, const int32 index)
			{
				self_type ret(value, index);
				return ret;
			}

			// assign and swap
			self_type &assign(const self_type &ano)
			{
				value_type::assign(ano.value());
				m_base.assign(ano.m_base);
				m_index = ano.m_index;
				m_offset.assign(ano.m_offset);
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
				assign(String::base64Decode(Data::toString(ano)), index);
				return *this;
			}
			template<bool Signed>
			self_type &assign(const IntegerWrapper<Signed> &ano, const int32 index = 0)
			{
				assign(ano.get<value_type>());
				return *this;
			}
			template<uint32 _Digits>
			typename std::enable_if_t<_Digits != Digits, self_type> &assign(const DecimalWrapper<_Digits> &ano)
			{
				m_base.assign(ano.get<value_type>());
				refresh(ano.m_base);
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
				m_base.swap(ano.m_base);
				std::swap(m_index, ano.m_index);
				m_offset.swap(ano.m_offset);
				refresh(m_index);
				ano.refresh(ano.m_index);
				return *this;
			}
			template<uint32 _Digits>
			typename std::enable_if_t<_Digits != Digits, self_type> &swap(DecimalWrapper<_Digits> &ano)
			{
				m_base.assign(ano.get<value_type>());
				ano.m_base.assign(get<DecimalWrapper<_Digits>::value_type>());
				std::swap(m_index, ano.m_index);
				refresh(m_index);
				ano.refresh(ano.m_index);
				return *this;
			}

			// operator =
			self_type &operator=(const self_type &rhs) = default;
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && Data::ConversionChecker<T, value_type>::value, self_type> &operator=(const T &rhs)
			{
				value_type::operator=(rhs);
				refresh();
				return *this;
			}
			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && !Data::ConversionChecker<T, value_type>::value, self_type> &operator=(const T &rhs)
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
				operator=(String::base64Decode(Data::toString(rhs)));
				return *this;
			}
			template<bool Signed>
			self_type &operator=(const IntegerWrapper<Signed> &rhs)
			{
				operator=(rhs.get<value_type>());
				return *this;
			}
			template<uint32 _Digits>
			self_type &operator=(const std::enable_if_t<Digits != _Digits, DecimalWrapper<_Digits>> &rhs)
			{
				operator=(rhs.get<value_type>());
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
				if (String::isDecimal(rhs))
				{
					operator+=(value_type(rhs));
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
				operator+=(rhs.get<value_type>());
				return *this;
			}
			template<uint32 _Digits>
			self_type &operator+=(const DecimalWrapper<_Digits> &rhs)
			{
				operator+=(rhs.get<value_type>());
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
				if (String::isDecimal(rhs))
				{
					operator-=(value_type(rhs));
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
				operator-=(rhs.get<value_type>());
				return *this;
			}
			template<uint32 _Digits>
			self_type &operator-=(const DecimalWrapper<_Digits> &rhs)
			{
				operator-=(rhs.get<value_type>());
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
				if (String::isDecimal(rhs))
				{
					operator*=(value_type(rhs));
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
				operator*=(rhs.get<value_type>());
				return *this;
			}
			template<uint32 _Digits>
			self_type &operator*=(const DecimalWrapper<_Digits> &rhs)
			{
				operator*=(rhs.get<value_type>());
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
				if (String::isDecimal(rhs))
				{
					operator/=(value_type(rhs));
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
				operator/=(rhs.get<value_type>());
				return *this;
			}
			template<uint32 _Digits>
			self_type &operator/=(const DecimalWrapper<_Digits> &rhs)
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
			std::enable_if_t<!std::is_same_v<T, value_type>, T> get(void) const { return convert_to<T>(); }
			template<typename T>
			std::enable_if_t<std::is_same_v<T, value_type>, const T &> get(void) const { return *this; }

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

			integer roundToInteger(void) const { return static_cast<integer>(boost::math::round(value())); }
			integer ceilToInteger(void) const { return floorToInteger() + 1; }
			integer floorToInteger(void) const { return static_cast<integer>(value()); }

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
