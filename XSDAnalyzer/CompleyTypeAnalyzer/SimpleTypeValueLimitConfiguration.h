#include "ElementGroup.h"
#pragma once

namespace XSDFrontend
{
	namespace SimpleType
	{
		template <typename T>
		class ValueLimitConfiguration abstract
		{
		public:
			struct ValueType
			{
				bool enabled;
				T value;

				ValueType(void) : enabled(false), value() {}
				ValueType(const ValueType &ano) = default;
				ValueType(ValueType &&ano) = default;
				ValueType &operator=(const ValueType &rhs) = default;
				ValueType &operator=(ValueType &&rhs) = default;
				~ValueType(void) = default;

				void set(const T &_value);
				void set(const T &&_value);
				void clear(void);
			};

			static const T NoValueValidator;

		protected:
			ValueLimitConfiguration(void) = default;
			ValueLimitConfiguration(const ValueLimitConfiguration &ano) = default;
			ValueLimitConfiguration(ValueLimitConfiguration &&ano) = default;
			ValueLimitConfiguration &operator=(const ValueLimitConfiguration &rhs) = default;
			ValueLimitConfiguration &operator=(ValueLimitConfiguration &&rhs) = default;
		public:
			virtual ~ValueLimitConfiguration(void) = default;

		public:
			inline void setMaxExclusive(const T &maxExclusive) { m_maxExclusive.set(maxExclusive); m_maxInclusive.clear(); }
			inline void setMaxExclusive(const T &&maxExclusive) { m_maxExclusive.set(std::move(maxExclusive)); m_maxInclusive.clear(); }
			inline void removeMaxExclusive(void) { m_maxExclusive.clear(); m_maxExclusive = NoValueValidator; }
			inline const bool hasMaxExclusive(void) const { return m_minInclusive.enabled; }
			inline const T &getMaxExclusive(void) const { return m_maxExclusive.value; }

			inline void setMaxInclusive(const T &maxInclusive) { m_maxInclusive.set(maxInclusive); m_maxExclusive.clear(); }
			inline void setMaxInclusive(const T &&maxInclusive) { m_maxInclusive.set(std::move(maxInclusive)); m_maxExclusive.clear(); }
			inline void removeMaxInclusive(void) { m_maxInclusive.clear(); m_maxInclusive = NoValueValidator; }
			inline const bool hasMaxInclusive(void) const { return m_minInclusive.enabled; }
			inline const T &getMaxInclusive(void) const { return m_maxInclusive.value; }

			inline void setMinExclusive(const T &minExclusive) { m_minExclusive.set(minExclusive); m_minInclusive.clear(); }
			inline void setMinExclusive(const T &&minExclusive) { m_minExclusive.set(std::move(minExclusive)); m_minInclusive.clear(); }
			inline void removeMinExclusive(void) { m_minExclusive.clear(); m_minExclusive = NoValueValidator; }
			inline const bool hasMinExclusive(void) const { return m_minExclusive.enabled; }
			inline const T &getMinExclusive(void) const { return m_minExclusive.value; }

			inline void setMinInclusive(const T &minInclusive) { m_minInclusive.set(minInclusive); m_minExclusive.clear(); }
			inline void setMinInclusive(const T &&minInclusive) { m_minInclusive.set(std::move(minInclusive)); m_minExclusive.clear(); }
			inline void removeMinInclusive(void) { m_minInclusive.clear(); m_minInclusive = NoValueValidator; }
			inline const bool hasMinInclusive(void) const { return m_minInclusive.enabled; }
			inline const T &getMinInclusive(void) const { return m_minInclusive.value; }

		private:
			ValueType m_maxExclusive;
			ValueType m_maxInclusive;

			ValueType m_minExclusive;
			ValueType m_minInclusive;
		};

		template<typename T>
		inline void ValueLimitConfiguration<T>::ValueType::set(const T & _value)
		{
			enabled = true;
			value = _value;
		}

		template<typename T>
		inline void ValueLimitConfiguration<T>::ValueType::set(const T && _value)
		{
			enabled = true;
			value = std::move(_value);
		}

		template<typename T>
		inline void typename ValueLimitConfiguration<T>::ValueType::clear(void)
		{
			enabled = false;
		}
	};
};
