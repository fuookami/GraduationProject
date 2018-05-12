#include "ElementGroup.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		const boost::bimap<std::string, ElementGroup::eElementGroupType> ElementGroup::Tag2Type =
			[]()
		{
			typedef boost::bimap<std::string, ElementGroup::eElementGroupType> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(Token::SequenceTag, ElementGroup::eElementGroupType::tSequence));
			ret.insert(pair_type(Token::ChoiceTag, ElementGroup::eElementGroupType::tChoice));
			ret.insert(pair_type(Token::AllTag, ElementGroup::eElementGroupType::tAll));
			return ret;
		}();

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

		std::set<std::string> ElementGroup::suppliedTokens(void) const
		{
			std::set<std::string> ret;
			if (!getAnonymous())
			{
				ret.insert(getName());
			}
			return ret;
		}

		std::set<std::string> ElementGroup::neededTokens(void) const
		{
			std::set<std::string> ret;
			if (hasRef())
			{
				ret.insert(getRefName());
			}
			else
			{
				for (const auto &value : m_vals)
				{
					decltype(ret) tokens;
					if (value.isElement())
					{
						tokens = value.element->neededTokens();
					}
					else if (value.isElementGroup())
					{
						tokens = value.elementGroup->neededTokens();
					}
					std::move(tokens.begin(), tokens.end(), std::inserter(ret, ret.end()));
				}
			}
			return ret;
		}
	};
};
