#include "ElementGroup.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		ElementGroup::ValueType::ValueType(void)
			: flag(eValueType::tNone), element(nullptr), anyElement(nullptr), elementGroup(nullptr)
		{
		}

		ElementGroup::ValueType::ValueType(const std::shared_ptr<Element>& ele)
			: flag(eValueType::tElement), element(ele), elementGroup(nullptr)
		{
		}

		ElementGroup::ValueType::ValueType(const std::shared_ptr<AnyElement> &anyEle)
			: flag(eValueType::tAnyElement), element(nullptr), anyElement(anyEle), elementGroup(nullptr)
		{

		}

		ElementGroup::ValueType::ValueType(const std::shared_ptr<ElementGroup>& group)
			: flag(eValueType::tElementGroup), element(nullptr), anyElement(nullptr), elementGroup(group)
		{
		}

		ElementGroup::ElementGroup(const eElementGroupType type)
			: ElementGroup("", type)
		{
		}

		ElementGroup::ElementGroup(const std::string & name, const eElementGroupType type)
			: IXSDNamedElementInterface(), IXSDReferenceElementInterface(), IXSDNumberLimitedElementInterface(),
			m_type(type), m_vals()
		{
		}

		ElementGroup::ElementGroup(std::string && name, const eElementGroupType type)
			: IXSDNamedElementInterface(), IXSDReferenceElementInterface(), IXSDNumberLimitedElementInterface(),
			m_type(type), m_vals()
		{
		}

		const std::map<std::string, ElementGroup::eElementGroupType> ElementGroupTag2Type =
		{
			std::make_pair(Token::SequenceTag, ElementGroup::eElementGroupType::tSequence),
			std::make_pair(Token::ChoiceTag, ElementGroup::eElementGroupType::tChoice),
			std::make_pair(Token::AllTag, ElementGroup::eElementGroupType::tAll)
		};
	};
};
