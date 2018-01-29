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
				inline const bool operator()(const T &lhs, const T &rhs) const
				{
					return lhs < rhs;
				}
			};

		protected:
			ValueEnumrationConfiguration(void) : m_isEnum(false), m_enumValues() {}
			ValueEnumrationConfiguration(const ValueEnumrationConfiguration &ano) = default;
			ValueEnumrationConfiguration(ValueEnumrationConfiguration &&ano) = default;
			ValueEnumrationConfiguration &operator=(const ValueEnumrationConfiguration &rhs) = default;
			ValueEnumrationConfiguration &operator=(ValueEnumrationConfiguration &&rhs) = default;
		public:
			virtual ~ValueEnumrationConfiguration(void) = default;

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
	};
};
