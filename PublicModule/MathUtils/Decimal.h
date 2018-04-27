#pragma once

#include "_pri_real_global.h"
#include "DataUtils.h"
#include <limits>

namespace SSUtils
{
	namespace Math
	{
		template<uint32 Digits> 
		class DecimalWrapper
		{
		public:
			typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<Digits>> value_type;

			DecimalWrapper(void)
				: m_value(0.0f), m_index(1) {};
			DecimalWrapper(const DecimalWrapper &ano) = default;
			DecimalWrapper(DecimalWrapper &&ano) = default;
			DecimalWrapper(const value_type &ano, const int32 index = 1)
				: m_value(ano), m_index(index) {};
			DecimalWrapper(value_type &&ano, const int32 index = 1)
				: m_value(std::move(ano)), m_index(index) {};
			template<typename T, typename = std::enable_if_t<!std::is_same_v<T, value_type> && Data::ConversionChecker<T, value_type>::value>>
			DecimalWrapper(const T &ano, const int32 index = 1)
				: m_value(ano), m_index(index) {};
			template<typename T, typename = std::enable_if_t<!std::is_same_v<T, value_type> && Data::ConversionChecker<T, value_type>::value>>
			DecimalWrapper(T &&ano, const int32 index = 1)
				: m_value(ano), m_index(index) {};
			DecimalWrapper &operator=(const DecimalWrapper &rhs) = default;
			DecimalWrapper &operator=(DecimalWrapper &&rhs) = default;
			DecimalWrapper &operator=(const value_type &rhs)
			{
				m_value = rhs;
				m_index = 1;
				return *this;
			}
			DecimalWrapper &operator=(value_type &&rhs)
			{
				m_value = std::move(rhs);
				m_index = 1;
				return *this;
			}
			template<typename T, typename = std::enable_if_t<!std::is_same_v<T, value_type> && Data::ConversionChecker<T, value_type>::value>>
			DecimalWrapper &operator=(const T &rhs)
			{
				m_value = rhs;
				m_index = 1;
				return *this;
			}
			template<typename T, typename = std::enable_if_t<!std::is_same_v<T, value_type> && Data::ConversionChecker<T, value_type>::value>>
			DecimalWrapper &operator=(T &&rhs)
			{
				m_value = std::move(rhs);
				m_index = 1;
				return *this;
			}
			~DecimalWrapper(void) = default;

			template<typename T>
			DecimalWrapper &operator+=(const T &rhs)
			{
				m_value += rhs;
				return *this;
			}
			template<typename T>
			DecimalWrapper &operator-=(const T &rhs)
			{
				m_value -= rhs;
				return *this;
			}
			template<typename T>
			DecimalWrapper &operator/=(const T &rhs)
			{
				m_value /= rhs;
				return *this;
			}
			DecimalWrapper &operator++(void)
			{
				m_value++;
				return *this;
			}
			DecimalWrapper &operator--(void)
			{
				m_value--;
				return *this;
			}
			DecimalWrapper operator++(int)
			{
				DecimalWrapper ret(*this);
				++ret;
				return ret;
			}
			DecimalWrapper operator--(int)
			{
				DecimalWrapper ret(*this);
				--ret;
				return ret;
			}

			const int32 index(void) const { return m_index; }
			void setIndex(const int32 index) { m_index = index; }

			value_type &value(void) { return m_value; }
			const value_type &value(void) const { return m_value; }
			operator value_type(void) const { return m_value * pow(value_type(10), m_index); }

			float getFloat(void) { return m_value.convert_to<float>(); }
			double getDouble(void) { return m_value.convert_to<double>(); }
			float32 getFloat32(void) { return m_value.convert_to<float32>(); }
			float64 getFloat64(void) { return m_value.convert_to<float64>(); }
			float128 getFloat128(void) { return m_value.convert_to<float128>(); }
			float256 getFloat256(void) { return m_value.convert_to<float256>(); }

		private:
			value_type m_value;
			int32 m_index;
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
