#include "stdafx.h"
#include "Element.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		const boost::bimap<std::string, Element::eForm> Element::String2Form = 
			[]()
		{
			typedef boost::bimap<std::string, Element::eForm> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("qualified"), Element::eForm::Qualified));
			ret.insert(pair_type(std::string("unqualified"), Element::eForm::Unqualified));
			return ret;
		}();

		const boost::bimap<std::string, bool> Element::String2Nillable = 
			[]()
		{
			typedef boost::bimap<std::string, bool> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(SSUtils::String::True(), true));
			ret.insert(pair_type(SSUtils::String::False(), false));
			return ret;
		}();

		const boost::bimap<std::string, bool> Element::String2Abstract = 
			[]()
		{
			typedef boost::bimap<std::string, bool> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(SSUtils::String::True(), true));
			ret.insert(pair_type(SSUtils::String::False(), false));
			return ret;
		}();

		const boost::bimap<std::string, Element::eBlock> Element::String2Block = 
			[]()
		{
			typedef boost::bimap<std::string, Element::eBlock> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("#all"), Element::eBlock::All));
			ret.insert(pair_type(std::string("extension"), Element::eBlock::Extension));
			ret.insert(pair_type(std::string("restriction"), Element::eBlock::Restriction));
			ret.insert(pair_type(std::string("substitution"), Element::eBlock::Substitution));
			return ret;
		}();

		const boost::bimap<std::string, Element::eFinal> Element::String2Final = 
			[]()
		{
			typedef boost::bimap<std::string, Element::eFinal> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("#all"), Element::eFinal::All));
			ret.insert(pair_type(std::string("extension"), Element::eFinal::Extension));
			ret.insert(pair_type(std::string("restriction"), Element::eFinal::Restriction));
			return ret;
		}();

		const std::set<std::string> Element::BaseAttrs = 
		{
			Token::NameAttr(), Token::ReferenceAttr(), Token::TypeAttr(), Token::SubstitutionGroupAttr(), Token::DefaultAttr(), Token::FixedAttr(), Token::FormAttr(), Token::MaxOccursAttr(), Token::MinOccursAttr(), Token::NillableAttr(), Token::AbstractAttr(), Token::BlockAttr(), Token::FinalAttr()
		};

		Element::Element(const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(), 
			m_substitutionGroup(), m_category(category), 
			m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		Element::Element(const std::string & name, const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(name), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(),
			m_substitutionGroup(), m_category(category), 
			m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		Element::Element(std::string && name, const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(std::move(name)), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(),
			m_substitutionGroup(), m_category(category), 
			m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		Element::Element(const std::string & name, const std::string & type, const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(name, type), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(),
			m_substitutionGroup(), m_category(category), 
			m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		Element::Element(std::string && name, const std::string & type, const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(std::move(name), type), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(),
			m_substitutionGroup(), m_category(category), 
			m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		Element::Element(std::string && name, std::string && type, const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(std::move(name), std::move(type)), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(),
			m_substitutionGroup(), m_category(category), 
			m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		std::set<std::string> Element::suppliedTokens(void) const
		{
			std::set<std::string> ret;
			if (!hasRef())
			{
				ret.insert(getName());
			}
			return ret;
		}

		std::set<std::string> Element::neededTokens(void) const
		{
			std::set<std::string> ret;
			auto substatutions(SSUtils::String::split(m_substitutionGroup, SSUtils::String::SpaceCharacters()));
			std::move(substatutions.begin(), substatutions.end(), std::inserter(ret, ret.end()));
			if (hasRef())
			{
				ret.insert(getRefName());
			}
			else
			{
				ret.insert(getType());
			}
			return ret;
		}
	};
};
