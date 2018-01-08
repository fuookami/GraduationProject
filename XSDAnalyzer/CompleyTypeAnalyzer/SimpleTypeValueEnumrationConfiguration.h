#pragma once

#include <set>

namespace XSDFrontend
{
	namespace SimpleType
	{
		template <typename T>
		class ValueEnumrationConfiguration abstract
		{
		private:
			struct _ValueTypeCompare
			{
				const bool operator()(const T &lhs, const T &rhs) const;
			};

		protected:
			ValueEnumrationConfiguration(void);
			ValueEnumrationConfiguration(const ValueEnumrationConfiguration &ano);
			ValueEnumrationConfiguration(const ValueEnumrationConfiguration &&ano);
			ValueEnumrationConfiguration &operator=(const ValueEnumrationConfiguration &rhs);
			ValueEnumrationConfiguration &operator=(const ValueEnumrationConfiguration &&rhs);
		public:
			virtual ~ValueEnumrationConfiguration(void);

		public:
			inline void setIsEnum(const bool isEnum) { m_isEnum = isEnum; }
			inline const bool getIsEnum(void) const { return m_isEnum; }

			inline void addEnumValue(const T &enumValue) { m_enumValues.insert(enumValue); }
			inline void addEnumValue(const T &&enumValue) { m_enumValues.insert(std::move(enumValue)); }
			inline void eraseEnumValue(const T &enumValue) { m_enumValues.erase(enumValue); }
			inline void clearEnumValue(void) { m_enumValues.clear(); }
			inline const bool hasEnumValue(const T &enumValue) const { return m_enumValues.find(enumValue) != m_enumValues.cend(); }
			inline const std::set<T, _ValueTypeCompare> &getEnumValues(void) const { return m_enumValues; }

		private:
			bool m_isEnum;
			std::set<T, _ValueTypeCompare> m_enumValues;
		};

		template<typename T>
		inline ValueEnumrationConfiguration<T>::ValueEnumrationConfiguration(void)
			: m_isEnum(false), m_enumValues()
		{
		}

		template<typename T>
		inline ValueEnumrationConfiguration<T>::ValueEnumrationConfiguration(const ValueEnumrationConfiguration & ano)
			: m_isEnum(ano.m_isEnum), m_enumValues(ano.m_enumValues)
		{
		}

		template<typename T>
		inline ValueEnumrationConfiguration<T>::ValueEnumrationConfiguration(const ValueEnumrationConfiguration && ano)
			: m_isEnum(ano.m_isEnum), m_enumValues(std::move(ano.m_enumValues))
		{
		}

		template<typename T>
		inline ValueEnumrationConfiguration<T> & ValueEnumrationConfiguration<T>::operator=(const ValueEnumrationConfiguration & rhs)
		{
			m_isEnum = rhs.m_isEnum;
			m_enumValues = rhs.m_enumValues;

			return *this;
		}

		template<typename T>
		inline ValueEnumrationConfiguration<T> & ValueEnumrationConfiguration<T>::operator=(const ValueEnumrationConfiguration && rhs)
		{
			m_isEnum = rhs.m_isEnum;
			m_enumValues = std::move(rhs.m_enumValues);

			return *this;
		}

		template<typename T>
		inline ValueEnumrationConfiguration<T>::~ValueEnumrationConfiguration(void)
		{
		}

		template<typename T>
		inline const bool ValueEnumrationConfiguration<T>::_ValueTypeCompare::operator()(const T & lhs, const T & rhs) const
		{
			return lhs < rhs;
		}
	};
};
