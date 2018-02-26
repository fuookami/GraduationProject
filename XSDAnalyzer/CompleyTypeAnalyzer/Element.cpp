#include "Element.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
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
