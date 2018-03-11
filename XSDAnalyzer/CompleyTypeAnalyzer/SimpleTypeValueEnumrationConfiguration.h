#pragma once

#include <set>
#include <functional>
#include "XMLUtils.h"
#include "XSDToken.h"

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
			using TranslateFunction = std::function<T(const std::string &)>;
			static const TranslateFunction translator;

		public:
			inline void setIsEnum(const bool isEnum) { m_isEnum = isEnum; }
			inline const bool getIsEnum(void) const { return m_isEnum; }

			inline void addEnumValue(const T &enumValue) { m_enumValues.insert(enumValue); }
			inline void addEnumValue(T &&enumValue) { m_enumValues.insert(std::move(enumValue)); }
			inline void eraseEnumValue(const T &enumValue) { m_enumValues.erase(enumValue); }
			inline void clearEnumValue(void) { m_enumValues.clear(); }
			inline const bool hasEnumValue(const T &enumValue) const { return m_enumValues.find(enumValue) != m_enumValues.cend(); }
			inline const std::set<T, _ValueTypeCompare> &getEnumValues(void) const { return m_enumValues; }

			void refreshValueEnumrationConfiguration(const XMLUtils::XMLNode &node);

		private:
			bool m_isEnum;
			std::set<T, _ValueTypeCompare> m_enumValues;
		};

		template<typename T>
		inline void ValueEnumrationConfiguration<T>::refreshValueEnumrationConfiguration(const XMLUtils::XMLNode & node)
		{
			if (node.hasChild(XSDFrontend::Token::EnumValidatorTag))
			{
				m_isEnum = true;

				std::for_each(node.getChildren().cbegin(), node.getChildren().cend(), 
					[this](const XMLUtils::XMLNode &node) 
				{
					if (node.getTag() == XSDFrontend::Token::EnumValidatorTag
						&& node.hasAttr(XSDFrontend::Token::ValueAttr))
					{
						this->addEnumValue(translator(node.getAttr(XSDFrontend::Token::ValueAttr)));
					}
				});
			}
		}
	};
};
