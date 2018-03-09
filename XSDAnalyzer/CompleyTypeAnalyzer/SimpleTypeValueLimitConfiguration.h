#pragma once

#include "XMLUtils.h"

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

				inline void set(const T &_value) { enabled = true; value = _value; }
				inline void set(T &&_value) { enabled = true; value = std::move(_value); }
				inline void clear(void) { enabled = false; value = NoValueValidator; }
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
			using TranslateFunction = std::function<T(const std::string &)>;
			static const TranslateFunction translator;

		public:
			inline void setMaxExclusive(const T &maxExclusive) { m_maxExclusive.set(maxExclusive); m_maxInclusive.clear(); }
			inline void setMaxExclusive(T &&maxExclusive) { m_maxExclusive.set(std::move(maxExclusive)); m_maxInclusive.clear(); }
			inline void removeMaxExclusive(void) { m_maxExclusive.clear(); m_maxExclusive = NoValueValidator; }
			inline const bool hasMaxExclusive(void) const { return m_minInclusive.enabled; }
			inline const T &getMaxExclusive(void) const { return m_maxExclusive.value; }

			inline void setMaxInclusive(const T &maxInclusive) { m_maxInclusive.set(maxInclusive); m_maxExclusive.clear(); }
			inline void setMaxInclusive(T &&maxInclusive) { m_maxInclusive.set(std::move(maxInclusive)); m_maxExclusive.clear(); }
			inline void removeMaxInclusive(void) { m_maxInclusive.clear(); m_maxInclusive = NoValueValidator; }
			inline const bool hasMaxInclusive(void) const { return m_minInclusive.enabled; }
			inline const T &getMaxInclusive(void) const { return m_maxInclusive.value; }

			inline void setMinExclusive(const T &minExclusive) { m_minExclusive.set(minExclusive); m_minInclusive.clear(); }
			inline void setMinExclusive(T &&minExclusive) { m_minExclusive.set(std::move(minExclusive)); m_minInclusive.clear(); }
			inline void removeMinExclusive(void) { m_minExclusive.clear(); m_minExclusive = NoValueValidator; }
			inline const bool hasMinExclusive(void) const { return m_minExclusive.enabled; }
			inline const T &getMinExclusive(void) const { return m_minExclusive.value; }

			inline void setMinInclusive(const T &minInclusive) { m_minInclusive.set(minInclusive); m_minExclusive.clear(); }
			inline void setMinInclusive(T &&minInclusive) { m_minInclusive.set(std::move(minInclusive)); m_minExclusive.clear(); }
			inline void removeMinInclusive(void) { m_minInclusive.clear(); m_minInclusive = NoValueValidator; }
			inline const bool hasMinInclusive(void) const { return m_minInclusive.enabled; }
			inline const T &getMinInclusive(void) const { return m_minInclusive.value; }

			const bool refreshValueLimitConfiguration(const XMLUtils::XMLNode &node);

		private:
			ValueType m_maxExclusive;
			ValueType m_maxInclusive;

			ValueType m_minExclusive;
			ValueType m_minInclusive;
		};

		template<typename T>
		const bool ValueLimitConfiguration<T>::refreshValueLimitConfiguration(const XMLUtils::XMLNode & node)
		{
			if (node.hasChild(XSDFrontend::Token::MaxExclusiveTag) && node.hasChild(XSDFrontend::Token::MaxInclusiveTag))
			{
				std::cerr << "不能同时定义开区间最大值和闭区间最大值" << std::endl;
				return false;
			}
			if (node.hasChild(XSDFrontend::Token::MinExclusiveTag) && node.hasChild(XSDFrontend::Token::MinInclusiveTag))
			{
				std::cerr << "不能同时定义开区间最小值和闭区间最小值" << std::endl;
				return false;
			}

			bool hasMax(false), maxIsExclusive(false);
			T maxValue(NoValueValidator);
			if (node.hasChild(XSDFrontend::Token::MaxExclusiveTag) || node.hasChild(XSDFrontend::Token::MaxInclusiveTag))
			{
				hasMax = true;
				if (node.hasChild(XSDFrontend::Token::MaxExclusiveTag))
				{
					maxIsExclusive = true;
					maxValue = translator(node.getChildren()[node.findChild(XSDFrontend::Token::MaxExclusiveTag)].getAttr(XSDFrontend::Token::ValueAttr));
				}
				else
				{
					maxValue=translator(node.getChildren()[node.findChild(XSDFrontend::Token::MaxInclusiveTag)].getAttr(XSDFrontend::Token::ValueAttr))
				}
			}
			
			bool hasMin(false), minIsExclusive(false);
			T minValue(NoValueValidator);
			if (node.hasChild(XSDFrontend::Token::MinExclusiveTag) || node.hasChild(XSDFrontend::Token::MinInclusiveTag))
			{
				hasMin = true;
				if (node.hasChild(XSDFrontend::Token::MinExclusiveTag))
				{
					minIsExclusive = true;
					minValue = translator(node.getChildren()[node.findChild(XSDFrontend::Token::MinExclusiveTag)].getAttr(XSDFrontend::Token::ValueAttr));
				}
				else
				{
					minValue = translator(node.getChildren()[node.findChild(XSDFrontend::Token::MinInclusiveTag)].getAttr(XSDFrontend::Token::ValueAttr));
				}
			}

			if (hasMin && hasMax && minValue > maxValue)
			{
				std::cerr << "定义的最小值(" << minValue << ")大于最大值(" << maxValue << ")。";
				return false;
			}

			if (hasMax)
			{
				if (maxIsExclusive)
				{
					setMaxExclusive(maxValue);
				}
				else
				{
					setMaxInclusive(maxValue);
				}
			}
			if (hasMin)
			{
				if (minIsExclusive)
				{
					setMinExclusive(minValue);
				}
				else
				{
					setMinInclusive(minValue);
				}
			}

			return true;
		}
	};
};
