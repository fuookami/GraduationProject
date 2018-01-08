#include "Element.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		Element::Element(const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(), 
			m_category(category), m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		Element::Element(const std::string & name, const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(name), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(),
			m_category(category), m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		Element::Element(const std::string && name, const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(std::move(name)), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(),
			m_category(category), m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		Element::Element(const std::string & name, const std::string & type, const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(name, type), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(),
			m_category(category), m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		Element::Element(const std::string && name, const std::string & type, const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(std::move(name), type), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(),
			m_category(category), m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		Element::Element(const std::string && name, const std::string && type, const eCategory category, const eForm form, const eBlock block, const eFinal _final)
			: IElementInterface(IElementInterface::eElementType::tElement), IXSDNamedTypedElementInterface(std::move(name), std::move(type)), IXSDReferenceElementInterface(), IXSDValueStatedElementInterface(),
			m_category(category), m_form(form), m_nillable(false), m_abstract(false), m_final(_final)
		{
		}

		Element::Element(const Element & ano)
			: IElementInterface(ano), IXSDNamedTypedElementInterface(ano), IXSDReferenceElementInterface(ano), IXSDValueStatedElementInterface(ano), 
			m_category(ano.m_category), m_form(ano.m_form), m_nillable(false), m_abstract(false), m_final(ano.m_final)
		{
		}

		Element::Element(const Element && ano)
			: IElementInterface(std::move(ano)), IXSDNamedTypedElementInterface(std::move(ano)), IXSDReferenceElementInterface(std::move(ano)), IXSDValueStatedElementInterface(std::move(ano)),
			m_category(ano.m_category), m_form(ano.m_form), m_nillable(false), m_abstract(false), m_final(ano.m_final)
		{
		}

		Element & Element::operator=(const Element & rhs)
		{
			m_category = rhs.m_category;
			
			m_form = rhs.m_form;
			m_nillable = rhs.m_nillable;
			m_abstract = rhs.m_abstract;
			m_block = rhs.m_block;
			m_final = rhs.m_final;

			IElementInterface::operator=(rhs);
			IXSDNamedTypedElementInterface::operator=(rhs);
			IXSDReferenceElementInterface::operator=(rhs);
			IXSDValueStatedElementInterface::operator=(rhs);

			return *this;
		}

		Element & Element::operator=(const Element && rhs)
		{
			m_category = rhs.m_category;

			m_form = rhs.m_form;
			m_nillable = rhs.m_nillable;
			m_abstract = rhs.m_abstract;
			m_block = rhs.m_block;
			m_final = rhs.m_final;

			IElementInterface::operator=(std::move(rhs));
			IXSDNamedTypedElementInterface::operator=(std::move(rhs));
			IXSDReferenceElementInterface::operator=(std::move(rhs));
			IXSDValueStatedElementInterface::operator=(std::move(rhs));

			return *this;
		}

		Element::~Element(void)
		{
		}
	};
};
