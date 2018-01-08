#include "Attribute.h"

namespace XSDFrontend
{
	namespace Attribute
	{
		Attribute::Attribute(const eForm form, const eUse use)
			: IAttributeInterface(IAttributeInterface::eAttributeType::tAttribute), IXSDNamedTypedElementInterface(), IXSDValueStatedElementInterface(), IXSDReferenceElementInterface(), 
			m_form(form), m_use(use)
		{
		}

		Attribute::Attribute(const std::string & name, const std::string & type, const eForm form, const eUse use)
			: IAttributeInterface(IAttributeInterface::eAttributeType::tAttribute), IXSDNamedTypedElementInterface(name, type), IXSDValueStatedElementInterface(), IXSDReferenceElementInterface(), 
			m_form(form), m_use(use)
		{
		}

		Attribute::Attribute(const std::string && name, const std::string & type, const eForm form, const eUse use)
			: IAttributeInterface(IAttributeInterface::eAttributeType::tAttribute), IXSDNamedTypedElementInterface(std::move(name), type), IXSDValueStatedElementInterface(), IXSDReferenceElementInterface(), 
			m_form(form), m_use(use)
		{
		}

		Attribute::Attribute(const std::string && name, const std::string && type, const eForm form, const eUse use)
			: IAttributeInterface(IAttributeInterface::eAttributeType::tAttribute), IXSDNamedTypedElementInterface(std::move(name), std::move(type)), IXSDValueStatedElementInterface(), IXSDReferenceElementInterface(),
			m_form(form), m_use(use)
		{
		}

		Attribute::Attribute(const Attribute & ano)
			: IAttributeInterface(ano), IXSDNamedTypedElementInterface(ano), IXSDValueStatedElementInterface(ano), IXSDReferenceElementInterface(ano), 
			m_form(ano.m_form), m_use(ano.m_use)
		{
		}

		Attribute::Attribute(const Attribute && ano)
			: IAttributeInterface(std::move(ano)), IXSDNamedTypedElementInterface(std::move(ano)), IXSDValueStatedElementInterface(std::move(ano)), IXSDReferenceElementInterface(std::move(ano)),
			m_form(ano.m_form), m_use(ano.m_use)
		{
		}

		Attribute & Attribute::operator=(const Attribute & rhs)
		{
			m_form = rhs.m_form;
			m_use = rhs.m_use;

			IAttributeInterface::operator=(rhs);
			IXSDNamedTypedElementInterface::operator=(rhs);
			IXSDValueStatedElementInterface::operator=(rhs);
			IXSDReferenceElementInterface::operator=(rhs);

			return *this;
		}

		Attribute & Attribute::operator=(const Attribute && rhs)
		{
			m_form = rhs.m_form;
			m_use = rhs.m_use;

			IAttributeInterface::operator=(std::move(rhs));
			IXSDNamedTypedElementInterface::operator=(std::move(rhs));
			IXSDValueStatedElementInterface::operator=(std::move(rhs));
			IXSDReferenceElementInterface::operator=(std::move(rhs));

			return *this;
		}

		Attribute::~Attribute(void)
		{
		}
	};
};
