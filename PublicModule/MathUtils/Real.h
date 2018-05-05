#pragma once

#include "_pri_math_global.h"
#include "Power.h"
#include "Logarithm.h"

#include <boost/bimap.hpp>
#include <boost/variant.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/rational.hpp>

#include <ostream>
#include <sstream>
#include <typeinfo>
#include <map>
#include <set>
#include <functional>
#include <utility>
#include <exception>
#include <cstdint>
#include <complex>


namespace SSUtils
{
	namespace Math
	{
		template<uint32 Digits>
		class RealWrapper
		{
		public:
			enum class SpecialValue
			{
				NegativeInfinity,
				PositiveInfinity,	
				NaN,
				Empty
			};

			enum class TranscendentalValue
			{
				pi,
				e
			};

			enum class Type
			{
				Boolean = 0,
				Integer,
				UInteger,
				Decimal,
				Rational,
				Power,
				Logarithm,
				Transcendental,
				Sepcial
			};

			typedef typename RealTypeGroup<Digits>::integer_type integer_type;
			typedef typename RealTypeGroup<Digits>::uinteger_type uinteger_type;
			typedef typename RealTypeGroup<Digits>::decimal_type decimal_type;
			typedef typename RealTypeGroup<Digits>::rational_type rational_type;
			typedef typename RealTypeGroup<Digits>::power_type power_type;
			typedef typename RealTypeGroup<Digits>::logarithm_type logarithm_type;
			typedef boost::variant<bool, integer_type, uinteger_type, decimal_type, rational_type, power_type, logarithm_type, TranscendentalValue, SpecialValue> value_type;
			typedef RealWrapper self_type;

			static const self_type pi;
			static const self_type e;
			static const self_type root_2;
			static const self_type root_3;
			static const self_type ln_2;
			static const self_type lg_2;

		private:
			template<typename visitor_t, uint32 _Digits>
			auto visit(const typename RealWrapper<_Digits>::value_type &value)
				-> typename std::enable_if_t<Digits != _Digits && _Digits != 0, typename visitor_t::result_type>
			{
				return boost::apply_visitor(visitor_t(), value);
			}
			template<typename visitor_t>
			auto visit(void) -> typename visitor_t::result_type
			{
				return boost::apply_visitor(visitor_t(), m_value);
			}

			template<uint32 _Digits, typename U = std::enable_if_t<Digits != _Digits && _Digits != 0>>
			struct differnet_digits_value_type_translator : public boost::static_visitor<value_type>
			{
				template<typename T>
				value_type operator()(const T &value) const
				{
					return value_type(value);
				}
				
				value_type operator()(const typename RealWrapper<_Digits>::decimal_type &decimal_value) const
				{
					return value_type(decimal_type(decimal_value));
				}

				value_type operator()(const typename RealWrapper<_Digits>::rational_type &rational_value) const
				{
					return value_type(rational_type(rational_value));
				}

				value_type operator()(const typename RealWrapper<_Digits>::power_type &power_value) const
				{
					return value_type(power_type(power_value));
				}

				value_type operator()(const typename RealWrapper<_Digits>::logarithm_type &logarithm_value) const
				{
					return value_type(logarithm_type(logarithm_value));
				}
			};

			struct positive_infinity_visitor : public boost::static_visitor<bool>
			{
				template<typename T>
				bool operator()(const T &value) const
				{
					return false;
				}

				bool operator()(const decimal_type &decimal_value) const
				{
					return check(decimal_value);
				}

				bool operator()(const rational_type &rational_value) const
				{
					return check(rational_value.value());
				}

				bool operator()(const power_type &power_value) const
				{
					return check(power_value.value());
				}

				bool operator()(const logarithm_type &logarithm_value) const
				{
					return check(logarithm_value.value());
				}

				bool operator()(const SpecialValue &special_value) const
				{
					return special_value == SpecialValue::PositiveInfinity;
				}

				bool check(const typename decimal_type::value_type &decimal_value) const
				{
					return boost::math::isinf(decimal_value) && decimal_value > 0;
				}
			};

			static const boost::bimap<std::string, Type> TypeName2Type;
			static const std::map<TranscendentalValue, typename decimal_type::value_type> TranscendentalValue2Decimal;

		public:
			// constructors
			RealWrapper(void)
				: m_value(SpecialValue::Empty) {};
			RealWrapper(const self_type &ano) = default;
			RealWrapper(self_type &&ano) = default;

			RealWrapper(const bool value)
				: m_value(value) {};
			RealWrapper(const integer_type &value)
				: m_value(value) {};
			RealWrapper(const uinteger_type &value)
				: m_value(value) {};
			RealWrapper(const decimal_type &value)
				: m_value(value) {};
			RealWrapper(const rational_type &value)
				: m_value(value) {};
			RealWrapper(const power_type &value)
				: m_value(value) {};
			RealWrapper(const logarithm_type &value)
				: m_value(value) {};
			RealWrapper(const TranscendentalValue value)
				: m_value(value) {};
			RealWrapper(const SpecialValue value)
				: m_value(value) {};
			RealWrapper(const std::string &str)
				: RealWrapper(generate(str)) {};
				RealWrapper(const Block &data)
				: RealWrapper(generate(data)) {};
			RealWrapper(const value_type &value)
				: m_value(value) {};
			template<typename T>
			RealWrapper(const T &value)
				: RealWrapper(generate(value)) {};

			// destructor
			~RealWrapper(void) = default;

			// generators
			static self_type generate(const value_type &value)
			{
				return self_type(value);
			}
			template<typename T>
			static typename std::enable_if_t<std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed && Data::ConversionChecker<T, typename integer_type::value_type>::value, self_type> generate(const T &integer_value)
			{
				return self_type(integer_type(typename integer_type::value_type(integer_value)));
			}
			template<typename T>
			static typename std::enable_if_t<std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed && !Data::ConversionChecker<T, typename integer_type::value_type>::value, self_type> generate(const T &integer_value)
			{
				return self_type(integer_type(static_cast<typename integer_type::value_type>(integer_value)));
			}
			template<>
			static self_type generate<integer_type>(const integer_type &integer_value)
			{
				return self_type(integer_value);
			}
			template<>
			static self_type generate<integer>(const integer &integer_value)
			{
				return self_type(integer_type(integer_value));
			}
			template<>
			static self_type generate<rational_type>(const rational_type &rational_value)
			{
				return self_type(rational_value);
			}
			template<>
			static self_type generate<rational>(const rational &rational_value)
			{
				return self_type(rational_type(rational_value));
			}
			template<uint32 _Digits>
			static typename std::enable_if_t<_Digits != Digits, self_type> generate(const RationalWrapper<_Digits> &rational_value)
			{
				return self_type(rational_type(rational_value));
			}

			template<typename T>
			static typename std::enable_if_t<std::numeric_limits<T>::is_integer && !std::numeric_limits<T>::is_signed && Data::ConversionChecker<T, typename uinteger_type::value_type>::value, self_type> generate(const T &uinteger_value)
			{
				return self_type(uinteger_type(typename uinteger_type::value_type(uinteger_value)));
			}
			template<typename T>
			static typename std::enable_if_t<std::numeric_limits<T>::is_integer && !std::numeric_limits<T>::is_signed && !Data::ConversionChecker<T, typename uinteger_type::value_type>::value, self_type> generate(const T &uinteger_value)
			{
				return self_type(uinteger_type(static_cast<typename uinteger_type::value_type>(uinteger_value)));
			}
			template<>
			static self_type generate<uinteger_type>(const uinteger_type &uinteger_value)
			{
				return self_type(uinteger_value);
			}
			template<>
			static self_type generate<bool>(const bool boolean_value)
			{
				return self_type(boolean_value);
			}

			template<typename T>
			static typename std::enable_if_t<std::numeric_limits<T>::is_specialized && !std::numeric_limits<T>::is_integer && Data::ConversionChecker<T, typename decimal_type::value_type>::value, self_type> generate(const T &decimal_value)
			{
				return self_type(decimal_type(typename decimal_type::value_type(decimal_value)));
			}
			template<typename T>
			static typename std::enable_if_t<std::numeric_limits<T>::is_specialized && !std::numeric_limits<T>::is_integer && !Data::ConversionChecker<T, typename decimal_type::value_type>::value, self_type> generate(const T &decimal_value)
			{
				return self_type(decimal_type(static_cast<typename decimal_type::value_type>(decimal_value)));
			}
			template<>
			static self_type generate<decimal_type>(const decimal_type &decimal_value)
			{
				return self_type(decimal_value);
			}
			template<>
			static self_type generate<power_type>(const power_type &power_value)
			{
				return self_type(power_value);
			}
			template<>
			static self_type generate<logarithm_type>(const logarithm_type &logarithm_value)
			{
				return self_type(logarithm_value);
			}
			template<uint32 _Digits>
			static typename std::enable_if_t<_Digits != Digits, self_type> generate(const decimal<_Digits> &decimal_value)
			{
				return self_type(decimal_type(decimal_value));
			}
			template<uint32 _Digits>
			static typename std::enable_if_t<_Digits != Digits, self_type> generate(const DecimalWrapper<_Digits> &decimal_value)
			{
				return self_type(decimal_type(decimal_value));
			}
			template<uint32 _Digits>
			static typename std::enable_if_t<_Digits != Digits, self_type> generate(const PowerWrapper<_Digits> &decimal_value)
			{
				return self_type(decimal_type(decimal_value));
			}
			template<uint32 _Digits>
			static typename std::enable_if_t<_Digits != Digits, self_type> generate(const LogarithmWrapper<_Digits> &decimal_value)
			{
				return self_type(decimal_type(decimal_value));
			}

			template<typename T>
			static typename std::enable_if_t<!std::is_same_v<T, self_type> && !std::numeric_limits<T>::is_specialized && Data::ConversionChecker<T, typename decimal_type::value_type>::value, self_type> generate(const T &value)
			{
				return self_type(decimal_type(typename decimal_type::value_type(value)));
			}
			template<typename T>
			static typename std::enable_if_t<!std::is_same_v<T, self_type> && !std::numeric_limits<T>::is_specialized && !Data::ConversionChecker<T, typename decimal_type::value_type>::value, self_type> generate(const T &value)
			{
				return self_type(decimal_type(static_cast<typename decimal_type::value_type>(value)));
			}
			template<>
			static self_type generate<TranscendentalValue>(const TranscendentalValue value)
			{
				return self_type(value);
			}
			template<>
			static self_type generate<SpecialValue>(const SpecialValue value)
			{
				return self_type(value);
			}
			template<>
			static self_type generate<std::string>(const std::string &str)
			{
				self_type ret;
				// to do;
				return ret;
			}
			template<>
			static self_type generate<Block>(const Block &block)
			{
				self_type ret;
				// to do
				return ret;
			}

			// assign and swap
			self_type &assign(const self_type &ano)
			{
				m_value.assign(ano.m_value);
				return *this;
			}
			self_type &assign(const value_type &ano)
			{
				m_value.assign(ano);
				return *this;
			}
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits != _Digits && _Digits != 0, self_type> &assign(const RealWrapper<_Digits> &ano)
			{
				m_value.assign(visit<differnet_digits_value_type_translator>(ano.value()));
				return *this;
			}

			self_type &swap(self_type &ano)
			{
				m_value.swap(ano.m_value);
				return *this;
			}
			self_type &swap(value_type &ano)
			{
				m_value.swap(ano);
				return *this;
			}
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits != _Digits && _Digits != 0, self_type> &swap(RealWrapper<_Digits> &ano)
			{
				value_type temp(m_value);
				m_value.assign(visit<differnet_digits_value_type_translator>(ano.value()));
				ano.assign(temp);
				return *this;
			}

			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed && Data::ConversionChecker<T, typename integer_type::value_type>::value, self_type> &assign(const T &integer_value);
			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed && !Data::ConversionChecker<T, typename integer_type::value_type>::value, self_type> &assign(const T &integer_value);
			template<>
			self_type &assign<integer_type>(const integer_type &integer_value);
			template<>
			self_type &assign<integer>(const integer &integer_value);
			template<>
			self_type &assign<rational_type>(const rational_type &rational_value);
			template<>
			self_type &assign<rational>(const rational &rational_value);
			template<uint32 _Digits>
			typename std::enable_if_t<_Digits != Digits, self_type> &assign(const RationalWrapper<_Digits> &rational_value);

			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_integer && !std::numeric_limits<T>::is_signed && Data::ConversionChecker<T, typename uinteger_type::value_type>::value, self_type> &assign(const T &uinteger_value);
			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_integer && !std::numeric_limits<T>::is_signed && !Data::ConversionChecker<T, typename uinteger_type::value_type>::value, self_type> &assign(const T &uinteger_value);
			template<>
			self_type &assign<uinteger_type>(const uinteger_type &uinteger_value);
			template<>
			self_type &assign<bool>(const bool &boolean_value);

			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_specialized && !std::numeric_limits<T>::is_integer && Data::ConversionChecker<T, typename decimal_type::value_type>::value, self_type> &assign(const T &decimal_value);
			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_specialized && !std::numeric_limits<T>::is_integer && !Data::ConversionChecker<T, typename decimal_type::value_type>::value, self_type> &assign(const T &decimal_value);
			template<>
			self_type &assign<decimal_type>(const decimal_type &decimal_value);
			template<>
			self_type &assign<power_type>(const power_type &power_value);
			template<>
			self_type &assign<logarithm_type>(const logarithm_type &logarithm_value);
			template<uint32 _Digits>
			typename std::enable_if_t<_Digits != Digits, self_type> &assign(const decimal<_Digits> &decimal_value);
			template<uint32 _Digits>
			typename std::enable_if_t<_Digits != Digits, self_type> &assign(const DecimalWrapper<_Digits> &decimal_value);

			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && !std::numeric_limits<T>::is_specialized && Data::ConversionChecker<T, typename decimal_type::value_type>::value, self_type> &assign(const T &value);
			self_type &assign(const std::string &str);
			self_type &assign(const Block &block);
			self_type &assign(const TranscendentalValue value);
			self_type &assign(const SpecialValue value);

			// operator =
			self_type &operator=(const self_type &rhs) = default;
			self_type &operator=(const value_type &rhs);

			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed && Data::ConversionChecker<T, typename integer_type::value_type>::value, self_type> &operator=(const T &integer_value);
			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed && !Data::ConversionChecker<T, typename integer_type::value_type>::value, self_type> &operator=(const T &integer_value);
			template<>
			self_type &operator=<integer_type>(const integer_type &integer_value);
			template<>
			self_type &operator=<integer>(const integer &integer_value);
			template<>
			self_type &operator=<rational_type>(const rational_type &rational_value);
			template<>
			self_type &operator=<rational>(const rational &rational_value);
			template<uint32 _Digits>
			typename std::enable_if_t<_Digits != Digits, self_type> &operator=(const RationalWrapper<_Digits> &rational_value);

			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_integer && !std::numeric_limits<T>::is_signed && Data::ConversionChecker<T, typename uinteger_type::value_type>::value, self_type> &operator=(const T &uinteger_value);
			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_integer && !std::numeric_limits<T>::is_signed && !Data::ConversionChecker<T, typename uinteger_type::value_type>::value, self_type> &operator=(const T &uinteger_value);
			template<>
			self_type &operator=<uinteger_type>(const uinteger_type &uinteger_value);
			template<>
			self_type &operator=<bool>(const bool &boolean_value);

			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_specialized && !std::numeric_limits<T>::is_integer && Data::ConversionChecker<T, typename decimal_type::value_type>::value, self_type> &operator=(const T &decimal_value);
			template<typename T>
			typename std::enable_if_t<std::numeric_limits<T>::is_specialized && !std::numeric_limits<T>::is_integer && !Data::ConversionChecker<T, typename decimal_type::value_type>::value, self_type> &operator=(const T &decimal_value);
			template<>
			self_type &operator=<decimal_type>(const decimal_type &decimal_value);
			template<>
			self_type &operator=<power_type>(const power_type &power_value);
			template<>
			self_type &operator=<logarithm_type>(const logarithm_type &logarithm_value);
			template<uint32 _Digits>
			typename std::enable_if_t<_Digits != Digits, self_type> &operator=(const decimal<_Digits> &decimal_value);
			template<uint32 _Digits>
			typename std::enable_if_t<_Digits != Digits, self_type> &operator=(const DecimalWrapper<_Digits> &decimal_value);

			template<typename T>
			typename std::enable_if_t<!std::is_same_v<T, self_type> && !std::numeric_limits<T>::is_specialized && Data::ConversionChecker<T, typename decimal_type::value_type>::value, self_type> &operator=(const T &value);
			self_type &operator=(const std::string &str);
			self_type &operator=(const Block &block);
			self_type &operator=(const TranscendentalValue value);
			self_type &operator=(const SpecialValue value);

			// set and get
			const value_type &value(void) const { return m_value; }
			void setValue(const value_type &value);
			operator decimal<Digits>(void) const;

			Type type(void) const { return static_cast<Type>(m_value.what()); }

			// translators
			std::string toString(void) const;
			Block toBlock(void) const;

			bool toBoolean(void) const;

			std::pair<bool, int8> toInt8(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, uint8> toUInt8(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, int16> toInt16(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, uint16> toUInt16(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, int32> toInt32(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, uint32> toUInt32(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, int64> toInt64(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, uint64> toUInt64(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, int128> toInt128(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, uint128> toUInt128(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, int256> toInt256(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, uint256> toUInt256(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, int512> toInt512(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, uint512> toUInt512(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, int1024> toInt1024(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, uint1024> toUInt1024(const ToIntegerFlag flag = ToIntegerFlag::round) const;

			template<uint32 bits>
			std::pair<bool, intx<bits>> toIntx(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			template<uint32 bits>
			std::pair<bool, uintx<bits>> toUIntx(const ToIntegerFlag flag = ToIntegerFlag::round) const;
			std::pair<bool, integer> toInteger(const ToIntegerFlag flag = ToIntegerFlag::round) const;

			std::pair<bool, float> toFloat(void) const;
			std::pair<bool, double> toDouble(void) const;
			std::pair<bool, float32> toFloat32(void) const;
			std::pair<bool, float64> toFloat64(void) const;
			std::pair<bool, float128> toFloat128(void) const;
			std::pair<bool, float256> toFloat256(void) const;

			std::pair<bool, dec50> toDec50(void) const;
			std::pair<bool, dec100> toDec100(void) const;
			std::pair<bool, real> toReal(void) const;
			template<uint32 Digits = DefaultDigits>
			std::pair<bool, decimal<Digits>> toDecimal(void) const;
			template<uint32 Digits = DefaultDigits>
			std::pair<bool, DecimalWrapper<Digits>> toDecimalWrapper(void) const;

 			template<typename T>
 			typename std::enable_if_t<std::numeric_limits<T>::is_specialized || std::is_same_v<T, std::string> || std::is_same_v<T, Block> || std::is_same_v<T, TranscendentalValue> || std::is_same_v<T, SpecialValue>, T> get(void) const;

			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, std::pair<bool, RealWrapper<_Digits>>> round(void) const;
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, std::pair<bool, RealWrapper<_Digits>>> floor(void) const;
			template<uint32 _Digits = DefaultDigits>
			typename std::enable_if_t<Digits >= _Digits && _Digits != 0, std::pair<bool, RealWrapper<_Digits>>> ceil(void) const;

			self_type roundToInteger(void) const;
			self_type ceilToInteger(void) const;
			self_type floorToInteger(void) const;

		private:
			value_type m_value;
		};

		template<uint32 Digits>
		const boost::bimap<std::string, typename RealWrapper<Digits>::Type> TypeName2Type = 
			[]() -> boost::bimap<std::string, typename RealWrapper<Digits>::Type>
		{
			typedef boost::bimap<std::string, typename RealWrapper<Digits>::Type>::value_type pair_type;

			boost::bimap<std::string, typename RealWrapper<Digits>::Type> ret;
			ret.insert(pair_type(typeid(bool).name(), RealWrapper<Digits>::Type::Boolean));
			ret.insert(pair_type(typeid(typename RealWrapper<Digits>::integer_type).name(), RealWrapper<Digits>::Type::Integer));
			ret.insert(pair_type(typeid(typename RealWrapper<Digits>::uinteger_type).name(), RealWrapper<Digits>::Type::UInteger));
			ret.insert(pair_type(typeid(typename RealWrapper<Digits>::decimal_type).name(), RealWrapper<Digits>::Type::Decimal));
			ret.insert(pair_type(typeid(typename RealWrapper<Digits>::rational_type).name(), RealWrapper<Digits>::Type::Rational));
			ret.insert(pair_type(typeid(typename RealWrapper<Digits>::power_type).name(), RealWrapper<Digits>::Type::Power));
			ret.insert(pair_type(typeid(typename RealWrapper<Digits>::logarithm_type).name(), RealWrapper<Digits>::Type::Logarithm));
			ret.insert(pair_type(typeid(typename RealWrapper<Digits>::TranscendentalValue).name(), RealWrapper<Digits>::Type::Transcendental));
			ret.insert(pair_type(typeid(typename RealWrapper<Digits>::SpecialValue).name(), RealWrapper<Digits>::Type::Sepcial));

			return ret;
		}();

		template<uint32 Digits>
		const std::map<typename RealWrapper<Digits>::TranscendentalValue, typename RealWrapper<Digits>::decimal_type::value_type> RealWrapper<Digits>::TranscendentalValue2Decimal = 
		{
			std::make_pair(TranscendentalValue::e, Constant::e<Digits>),
			std::make_pair(TranscendentalValue::pi, Constant::pi<Digits>)
		};

		template<uint32 Digits>
		const RealWrapper<Digits> RealWrapper<Digits>::pi = RealWrapper<Digits>(RealWrapper<Digits>::TranscendentalValue::pi);
		template<uint32 Digits>
		const RealWrapper<Digits> RealWrapper<Digits>::e = RealWrapper<Digits>(RealWrapper<Digits>::TranscendentalValue::e);
		template<uint32 Digits>
		const RealWrapper<Digits> RealWrapper<Digits>::root_2 = RealWrapper<Digits>(RealWrapper<Digits>::power_type(2, 0.5));
		template<uint32 Digits>
		const RealWrapper<Digits> RealWrapper<Digits>::root_3 = RealWrapper<Digits>(RealWrapper<Digits>::power_type(3, 0.5));
		template<uint32 Digits>
		const RealWrapper<Digits> RealWrapper<Digits>::ln_2 = RealWrapper<Digits>(RealWrapper<Digits>::logarithm_type(RealWrapper<Digits>::TranscendentalValue2Decimal.find(RealWrapper<Digits>::TranscendentalValue::e)->second(), 2));
		template<uint32 Digits>
		const RealWrapper<Digits> RealWrapper<Digits>::lg_2 = RealWrapper<Digits>(RealWrapper<Digits>::logarithm_type(RealWrapper<Digits>::TranscendentalValue2Decimal.find(RealWrapper<Digits>::TranscendentalValue::e)->second(), 2));

		template<uint32 Digits>
		integer round(const RealWrapper<Digits> &value)
		{
			return value.roundToInteger().toInteger();
		}
		template<uint32 Digits>
		integer ceil(const RealWrapper<Digits> &value)
		{
			return value.ceilToInteger().toInteger();
		}
		template<uint32 Digits>
		integer floor(const RealWrapper<Digits> &value)
		{
			return value.floorToInteger().toInteger();
		}
	}
};
