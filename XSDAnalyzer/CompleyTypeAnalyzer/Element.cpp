#include "Element.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		const std::map<std::string, Element::eForm> Element::String2Form = 
		{
			std::make_pair(std::string("qualified"), Element::eForm::Qualified),
			std::make_pair(std::string("unqualified"), Element::eForm::Unqualified)
		};

		const std::map<std::string, bool> Element::String2Nillable = 
		{
			std::make_pair(SSUtils::String::True, true),
			std::make_pair(SSUtils::String::False, false)
		};

		const std::map<std::string, bool> Element::String2Abastract = 
		{
			std::make_pair(SSUtils::String::True, true),
			std::make_pair(SSUtils::String::False, false)
		};

		const std::map<std::string, Element::eBlock> Element::String2Block = 
		{
			std::make_pair(std::string("#all"), Element::eBlock::All),
			std::make_pair(std::string("extension"), Element::eBlock::Extension),
			std::make_pair(std::string("restriction"), Element::eBlock::Restriction),
			std::make_pair(std::string("substitution"), Element::eBlock::Substitution)
		};

		const std::map<std::string, Element::eFinal> Element::String2Final = 
		{
			std::make_pair(std::string("#all"), Element::eFinal::All),
			std::make_pair(std::string("extension"), Element::eFinal::Extension),
			std::make_pair(std::string("restriction"), Element::eFinal::Restriction)
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
	};
};
