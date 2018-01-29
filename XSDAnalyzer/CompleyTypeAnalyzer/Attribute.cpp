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

		Attribute::Attribute(std::string && name, const std::string & type, const eForm form, const eUse use)
			: IAttributeInterface(IAttributeInterface::eAttributeType::tAttribute), IXSDNamedTypedElementInterface(std::move(name), type), IXSDValueStatedElementInterface(), IXSDReferenceElementInterface(), 
			m_form(form), m_use(use)
		{
		}

		Attribute::Attribute(std::string && name, std::string && type, const eForm form, const eUse use)
			: IAttributeInterface(IAttributeInterface::eAttributeType::tAttribute), IXSDNamedTypedElementInterface(std::move(name), std::move(type)), IXSDValueStatedElementInterface(), IXSDReferenceElementInterface(),
			m_form(form), m_use(use)
		{
		}
	};
};
