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

				ValueType(void);
				ValueType(const ValueType &ano);
				ValueType(const ValueType &&ano);
				ValueType &operator=(const ValueType &rhs);
				ValueType &operator=(const ValueType &&rhs);
				~ValueType(void);

				void set(const T &_value);
				void set(const T &&_value);
				void clear(void);
			};

			static const T NoValueValidator;

		protected:
			ValueLimitConfiguration(void);
			ValueLimitConfiguration(const ValueLimitConfiguration &ano);
			ValueLimitConfiguration(const ValueLimitConfiguration &&ano);
			ValueLimitConfiguration &operator=(const ValueLimitConfiguration &rhs);
			ValueLimitConfiguration &operator=(const ValueLimitConfiguration &&rhs);
		public:
			virtual ~ValueLimitConfiguration(void);

		public:
			inline void setMaxExclusive(const T &maxExclusive) { m_maxExclusive.set(maxExclusive); m_maxInclusive.clear(); }
			inline void setMaxExclusive(const T &&maxExclusive) { m_maxExclusive.set(std::move(maxExclusive)); m_maxInclusive.clear(); }
			inline void removeMaxExclusive(void) { m_maxExclusive.clear(); m_maxExclusive = NoValueValidator; }
			inline const bool hasMaxExclusive(void) { return m_minInclusive.enabled; }
			inline const T &getMaxExclusive(void) { return m_maxExclusive.value; }

			inline void setMaxInclusive(const T &maxInclusive) { m_maxInclusive.set(maxInclusive); m_maxExclusive.clear(); }
			inline void setMaxInclusive(const T &&maxInclusive) { m_maxInclusive.set(std::move(maxInclusive)); m_maxExclusive.clear(); }
			inline void removeMaxInclusive(void) { m_maxInclusive.clear(); m_maxInclusive = NoValueValidator; }
			inline const bool hasMaxInclusive(void) { return m_minInclusive.enabled; }
			inline const T &getMaxInclusive(void) { return m_maxInclusive.value; }

			inline void setMinExclusive(const T &minExclusive) { m_minExclusive.set(minExclusive); m_minInclusive.clear(); }
			inline void setMinExclusive(const T &&minExclusive) { m_minExclusive.set(std::move(minExclusive)); m_minInclusive.clear(); }
			inline void removeMinExclusive(void) { m_minExclusive.clear(); m_minExclusive = NoValueValidator; }
			inline const bool hasMinExclusive(void) { return m_minExclusive.enabled; }
			inline const T &getMinExclusive(void) { return m_minExclusive.value; }

			inline void setMinInclusive(const T &minInclusive) { m_minInclusive.set(minInclusive); m_minExclusive.clear(); }
			inline void setMinInclusive(const T &&minInclusive) { m_minInclusive.set(std::move(minInclusive)); m_minExclusive.clear(); }
			inline void removeMinInclusive(void) { m_minInclusive.clear(); m_minInclusive = NoValueValidator; }
			inline const bool hasMinInclusive(void) { return m_minInclusive.enabled; }
			inline const T &getMinInclusive(void) { return m_minInclusive.value; }

		private:
			ValueType m_maxExclusive;
			ValueType m_maxInclusive;

			ValueType m_minExclusive;
			ValueType m_minInclusive;
		};

		template<typename T>
		inline ValueLimitConfiguration<T>::ValueType::ValueType(void)
			: enabled(false), value()
		{
		}

		template<typename T>
		inline ValueLimitConfiguration<T>::ValueType::ValueType(const ValueType & ano)
			: enabled(ano.enabled), value(ano.value)
		{
		}

		template<typename T>
		inline ValueLimitConfiguration<T>::ValueType::ValueType(const ValueType && ano)
			: enabled(ano.enabled), value(std::move(ano.value))
		{
		}

		template<typename T>
		inline typename ValueLimitConfiguration<T>::ValueType & ValueLimitConfiguration<T>::ValueType::operator=(const ValueType & rhs)
		{
			enabled = rhs.enabled;
			value = rhs.value;

			return *this;
		}

		template<typename T>
		inline typename ValueLimitConfiguration<T>::ValueType & ValueLimitConfiguration<T>::ValueType::operator=(const ValueType && rhs)
		{
			enabled = rhs.enabled;
			value = std::move(rhs.value);

			return *this;
		}

		template<typename T>
		inline ValueLimitConfiguration<T>::ValueType::~ValueType(void)
		{
		}

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

		template<typename T>
		inline ValueLimitConfiguration<T>::ValueLimitConfiguration(void)
			: m_maxExclusive(), m_maxInclusive(), m_minExclusive(), m_minInclusive()
		{
		}

		template<typename T>
		inline ValueLimitConfiguration<T>::ValueLimitConfiguration(const ValueLimitConfiguration & ano)
			: m_maxExclusive(ano.m_maxExclusive), m_maxInclusive(ano.m_maxInclusive), 
			m_minExclusive(ano.m_minExclusive), m_minInclusive(ano.m_minInclusive)
		{
		}

		template<typename T>
		inline ValueLimitConfiguration<T>::ValueLimitConfiguration(const ValueLimitConfiguration && ano)
			: m_maxExclusive(std::move(ano.m_maxExclusive)), m_maxInclusive(std::move(ano.m_maxInclusive)), 
			m_minExclusive(std::move(ano.m_minExclusive)), m_minInclusive(std::move(ano.m_minInclusive))
		{
		}

		template<typename T>
		inline ValueLimitConfiguration<T> & ValueLimitConfiguration<T>::operator=(const ValueLimitConfiguration & rhs)
		{
			m_maxExclusive = rhs.m_maxExclusive;
			m_maxInclusive = rhs.m_maxInclusive;
			m_minExclusive = rhs.m_minExclusive;
			m_minInclusive = rhs.m_minExclusive;

			return *this;
		}

		template<typename T>
		inline ValueLimitConfiguration<T> & ValueLimitConfiguration<T>::operator=(const ValueLimitConfiguration && rhs)
		{
			m_maxExclusive = std::move(rhs.m_maxExclusive);
			m_maxInclusive = std::move(rhs.m_maxInclusive);
			m_minExclusive = std::move(rhs.m_minExclusive);
			m_minInclusive = std::move(rhs.m_minExclusive);

			return *this;
		}

		template<typename T>
		inline ValueLimitConfiguration<T>::~ValueLimitConfiguration(void)
		{
		}
	};
};
