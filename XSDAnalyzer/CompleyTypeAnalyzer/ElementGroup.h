#pragma once

#include "Element.h"
#include "AnyElement.h"
#include "XSDToken.h"

#include <vector>
#include <memory>

namespace XSDFrontend
{
	namespace ComplexType
	{
		class ElementGroup final : public XSDElementUtils::IXSDNamedElementInterface, 
			public XSDElementUtils::IXSDReferenceElementInterface<ElementGroup>, 
			public XSDElementUtils::IXSDNumberLimitedElementInterface
		{
		public:
			enum class eElementGroupType
			{
				tSequence,
				tAll,
				tChoice
			};

			enum class eValueType
			{
				tNone,
				tElement,
				tAnyElement,
				tElementGroup
			};

			struct ValueType
			{
				eValueType flag;
				std::shared_ptr<Element> element;
				std::shared_ptr<AnyElement> anyElement;
				std::shared_ptr<ElementGroup> elementGroup;

				ValueType(void);
				ValueType(const std::shared_ptr<Element> &ele);
				ValueType(const std::shared_ptr<AnyElement> &anyElement);
				ValueType(const std::shared_ptr<ElementGroup> &group);
				ValueType(const ValueType &ano) = default;
				ValueType(ValueType &&ano) = default;
				ValueType &operator=(const ValueType &rhs) = default;
				ValueType &operator=(ValueType &&rhs) = default;
				~ValueType(void) = default;

				inline void setElement(const std::shared_ptr<Element> &ele) { flag = eValueType::tElement; element = ele; anyElement.reset(); elementGroup.reset(); }
				inline void setAnyElement(const std::shared_ptr<AnyElement> &anyEle) { flag = eValueType::tAnyElement; element.reset(); anyElement = anyEle; elementGroup.reset(); }
				inline void setElementGroup(const std::shared_ptr<ElementGroup> &group) { flag = eValueType::tElementGroup; element.reset(); anyElement.reset(); elementGroup = group; }

				inline const bool isElement(void) const { return flag == eValueType::tElement; }
				inline const bool isAnyElement(void) const { return flag == eValueType::tAnyElement; }
				inline const bool isElementGroup(void) const { return flag == eValueType::tElementGroup; }
			};

		public:
			ElementGroup(const eElementGroupType type = eElementGroupType::tSequence);
			ElementGroup(const std::string &name, const eElementGroupType type = eElementGroupType::tSequence);
			ElementGroup(std::string &&name, const eElementGroupType type = eElementGroupType::tSequence);
			ElementGroup(const ElementGroup &ano) = default;
			ElementGroup(ElementGroup &&ano) = default;
			ElementGroup &operator=(const ElementGroup &rhs) = default;
			ElementGroup &operator=(ElementGroup &&rhs) = default;
			~ElementGroup(void) = default;

			inline void setElementGroupType(const eElementGroupType type) { m_type = type; }
			inline const eElementGroupType getElementGroupType(void) const { return m_type; }

			inline void insert(const int pos, const ValueType &val) { m_vals.insert(m_vals.begin() + pos, val); }
			inline void insert(const int pos, const ValueType &&val) { m_vals.insert(m_vals.begin() + pos, val); }
			inline void pushBack(const ValueType &val) { m_vals.push_back(val); }
			inline void pushBack(const ValueType &&val) { m_vals.push_back(val); }

			inline void erase(const int pos) { m_vals.erase(m_vals.begin() + pos); }

			inline const bool empty(void) const { return m_vals.empty(); }
			inline const unsigned int size(void) const { return m_vals.size(); }

			inline ValueType &getValue(const int pos) { return m_vals[pos]; }
			inline const ValueType &getValue(const int pos) const { return m_vals[pos]; }
			inline std::vector<ValueType> &getValues(void) { return m_vals; }
			inline const std::vector<ValueType> &getValues(void) const { return m_vals; }

		private:
			eElementGroupType m_type;

			std::vector<ValueType> m_vals;
		};

		static const std::map<std::string, ElementGroup::eElementGroupType> ElementGroupTag2Type = 
		{
			std::make_pair(Token::SequenceTag, ElementGroup::eElementGroupType::tSequence),
			std::make_pair(Token::ChoiceTag, ElementGroup::eElementGroupType::tChoice),
			std::make_pair(Token::AllTag, ElementGroup::eElementGroupType::tAll)
		};
	};
};
