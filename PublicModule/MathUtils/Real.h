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
		class real
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
				Bool = 1,
				Int8,
				UInt8,
				Int16,
				UInt16,
				Int32,
				UInt32,
				Int64,
				UInt64,
				Float,
				Double,
				Rational,
				Power,
				Logarithm,
				Transcendental,
				Special
			};

			enum class Classfication
			{
				Boolean,
				Integer,
				Unsigned,
				Rational,
				Irrational,
				Special
			};

			enum class TransformationFlag
			{
				AllErrors,
				NoLimitErros,
				NoClassficationErros,
				NoAnyErrors
			};

			using rational = boost::rational<int64>;
			using power = power<double>;
			using logarithm = logarithm<double>;

			template<Type t> struct TypeTransform { typedef void type; };
			template<> struct TypeTransform<Type::Bool> { typedef bool type; };
			template<> struct TypeTransform<Type::Int8> { typedef int8 type; };
			template<> struct TypeTransform<Type::UInt8> { typedef uint8 type; };
			template<> struct TypeTransform<Type::Int16> { typedef int16 type; };
			template<> struct TypeTransform<Type::UInt16> { typedef uint16 type; };
			template<> struct TypeTransform<Type::Int32> { typedef int32 type; };
			template<> struct TypeTransform<Type::UInt32> { typedef uint32 type; };
			template<> struct TypeTransform<Type::Int64> { typedef int64 type; };
			template<> struct TypeTransform<Type::UInt64> { typedef uint64 type; };
			template<> struct TypeTransform<Type::Float> { typedef float type; };
			template<> struct TypeTransform<Type::Double> { typedef double type; };
			template<> struct TypeTransform<Type::Rational> { typedef rational type; };
			template<> struct TypeTransform<Type::Power> { typedef power type; };
			template<> struct TypeTransform<Type::Logarithm> { typedef logarithm type; };
			template<> struct TypeTransform<Type::Transcendental> { typedef TranscendentalValue type; };
			template<> struct TypeTransform<Type::Special> { typedef SpecialValue type; };

			using value_type = boost::variant<bool, int8, uint8, int16, uint16, int32, uint32, int64, uint64, float, double, rational, power, logarithm, TranscendentalValue, SpecialValue>;

		public:
			static const real pi;
			static const real e;
			static const real root_2;
			static const real root_3;
			static const real ln_2;
			static const real lg_2;

		private:
			static const uint32 DefaultPrecisionDigit;
			static const boost::bimap<std::string, Type> TypeName2Type;
			static const std::map<Type, Classfication> Type2Classfication;

			static const std::map<Type, std::map<TransformationFlag, std::set<Type>>> TypeTransformation;

		public:
			real(const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const bool value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const int8 value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const uint8 value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const int16 value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const uint16 value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const int32 value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const uint32 value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const int64 value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const uint64 value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const float value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const double value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const rational value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const power value, const TransformationFlag flag = TransformationFlag::NoClassficationErros);
			real(const logarithm value, const TransformationFlag flag = TransformationFlag::NoClassficationErros);
			real(const TranscendentalValue value, const TransformationFlag flag = TransformationFlag::NoClassficationErros);
			real(const SpecialValue value, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const std::string &str, const TransformationFlag falg = TransformationFlag::NoClassficationErros);
			real(const Block &data);
			real(const real &ano) = default;
			real(real &&ano) = default;
			~real(void) = default;

			real &operator=(const real &rhs) = default;
			real &operator=(real &&rhs) = default;
			real &operator=(const bool value);
			real &operator=(const int8 value);
			real &operator=(const uint8 value);
			real &operator=(const int16 value);
			real &operator=(const uint16 value);
			real &operator=(const int32 value);
			real &operator=(const uint32 value);
			real &operator=(const int64 value);
			real &operator=(const uint64 value);
			real &operator=(const float value);
			real &operator=(const double value);
			real &operator=(const rational value);
			real &operator=(const power value);
			real &operator=(const logarithm value);
			real &operator=(const TranscendentalValue value);
			real &operator=(const SpecialValue value);

			real &operator+=(const real &ano);
			template<typename T>
			real &operator+=(const T value);

			real &operator-=(const real &ano);
			template<typename T>
			real &operator-=(const T value);

			real &operator*=(const real &ano);
			template<typename T>
			real &operator*=(const T value);

			real &operator/=(const real &ano);
			template<typename T>
			real &operator/=(const T value);

			real &operator++(void);
			real operator++(const int i);

			real &operator--(void);
			real operator--(const int i);

			static real fromFormatString(const std::string &str);
			std::string toFormatString(void) const;
			static real fromString(const std::string &str);
			std::string toString(void) const;

			static real fromData(const Block &data);
			Block toData(void) const;

			void assign(const real &value);
			void assign(real &&value);
			void swap(real &ano);
			void fit(void);

			const bool empty(void) const;
			void clear(void);
			const bool isSpecialValue(void) const;
			const bool isNegativeInfinity(void) const;
			void setNegativeInfinity(void);
			const bool isPositiveInfinity(void) const;
			void setPositiveInfinity(void);
			const bool isNotANumber(void) const;
			void setNotANumber(void);

			const Type type(void) const;
			const Classfication classfication(void) const;
			
			const TransformationFlag transformationFlag(void) const;
			void setTransformationFlag(const TransformationFlag flag);
			
			const uint32 precisionDigit(void) const;
			void setPrecisionDigit(const uint32 digit);

			template<typename T>
			const bool set(const T value);
			template<Type t, typename T>
			const bool set(const T value);
			const bool set(const bool value);
			const bool set(const int8 value);
			const bool set(const uint8 value);
			const bool set(const int16 value);
			const bool set(const uint16 value);
			const bool set(const int32 value);
			const bool set(const uint32 value);
			const bool set(const int64 value);
			const bool set(const uint64 value);
			const bool set(const float value);
			const bool set(const double value);
			const bool set(const rational value);
			const bool set(const power value);
			const bool set(const logarithm value);
			const bool set(const TranscendentalValue value);
			const bool set(const SpecialValue value);
			const bool set(const std::string &str);
			const bool set(const Block &data);

			template<typename T>
			std::pair<bool, T> get(void);
			template<Type t>
			auto get(void) -> std::pair<bool, typename TypeTransform<t>::type>;
			std::pair<bool, bool> getBool(void) const;
			std::pair<bool, int8> getInt8(void) const;
			std::pair<bool, uint8> getUInt8(void) const;
			std::pair<bool, int16> getInt16(void) const;
			std::pair<bool, uint16> getUInt16(void) const;
			std::pair<bool, int32> getInt32(void) const;
			std::pair<bool, uint32> getUInt32(void) const;
			std::pair<bool, int64> getInt64(void) const;
			std::pair<bool, uint64> getUInt64(void) const;
			std::pair<bool, float> getFloat(void) const;
			std::pair<bool, double> getDouble(void) const;
			std::pair<bool, rational> getRational(void) const;
			std::pair<bool, power> getPower(void) const;
			std::pair<bool, logarithm> getLogarithm(void) const;
			std::pair<bool, TranscendentalValue> getTranscendentalValue(void) const;
			std::pair<bool, SpecialValue> getSpecialValue(void) const;

		private:
			Type m_type;
			Classfication m_class;
			TransformationFlag m_flag;
			value_type m_value;

			uint32 m_precisionDigit;
			double m_precision;
		};
	};
};

const bool operator==(const SSUtils::Math::real &lhs, const SSUtils::Math::real &rhs);
template<typename T>
const bool operator==(const SSUtils::Math::real &lhs, const T &rhs);
template<typename T>
const bool operator==(const T &lhs, const SSUtils::Math::real &rhs);

const bool operator!=(const SSUtils::Math::real &lhs, const SSUtils::Math::real &rhs);
template<typename T>
const bool operator!=(const SSUtils::Math::real &lhs, const T &rhs);
template<typename T>
const bool operator!=(const T &lhs, const SSUtils::Math::real &rhs);

const bool operator<(const SSUtils::Math::real &lhs, const SSUtils::Math::real &rhs);
template<typename T>
const bool operator<(const SSUtils::Math::real &lhs, const T &rhs);
template<typename T>
const bool operator<(const T &lhs, const SSUtils::Math::real &rhs);

const bool operator<=(const SSUtils::Math::real &lhs, const SSUtils::Math::real &rhs);
template<typename T>
const bool operator<=(const SSUtils::Math::real &lhs, const T &rhs);
template<typename T>
const bool operator<=(const T &lhs, const SSUtils::Math::real &rhs);

const bool operator>(const SSUtils::Math::real &lhs, const SSUtils::Math::real &rhs);
template<typename T>
const bool operator>(const SSUtils::Math::real &lhs, const T &rhs);
template<typename T>
const bool operator>(const T &lhs, const SSUtils::Math::real &rhs);

const bool operator>=(const SSUtils::Math::real &lhs, const SSUtils::Math::real &rhs);
template<typename T>
const bool operator>=(const SSUtils::Math::real &lhs, const T &rhs);
template<typename T>
const bool operator>=(const T &lhs, const SSUtils::Math::real &rhs);

SSUtils::Math::real operator+(const SSUtils::Math::real &lhs, const SSUtils::Math::real &rhs);
template<typename T>
SSUtils::Math::real operator+(const SSUtils::Math::real &lhs, const T &rhs);
template<typename T>
SSUtils::Math::real operator+(const T &lhs, const SSUtils::Math::real &rhs);

SSUtils::Math::real operator-(const SSUtils::Math::real &lhs, const SSUtils::Math::real &rhs);
template<typename T>
SSUtils::Math::real operator-(const SSUtils::Math::real &lhs, const T &rhs);
template<typename T>
SSUtils::Math::real operator-(const T &lhs, const SSUtils::Math::real &rhs);

SSUtils::Math::real operator*(const SSUtils::Math::real &lhs, const SSUtils::Math::real &rhs);
template<typename T>
SSUtils::Math::real operator*(const SSUtils::Math::real &lhs, const T &rhs);
template<typename T>
SSUtils::Math::real operator*(const T &lhs, const SSUtils::Math::real &rhs);

SSUtils::Math::real operator/(const SSUtils::Math::real &lhs, const SSUtils::Math::real &rhs);
template<typename T>
SSUtils::Math::real operator/(const SSUtils::Math::real &lhs, const T &rhs);
template<typename T>
SSUtils::Math::real operator/(const T &lhs, const SSUtils::Math::real &rhs);

std::istream &operator<<(std::istream &is, SSUtils::Math::real &number);
std::ostream &operator>>(std::ostream &is, SSUtils::Math::real &number);
