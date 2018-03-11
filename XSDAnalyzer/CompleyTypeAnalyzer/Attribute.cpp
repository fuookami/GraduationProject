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

		const std::map<std::string, Attribute::eForm> FormString2Form =
		{
			std::make_pair(std::string("qualified"), Attribute::eForm::Qualified),
			std::make_pair(std::string("unqualified"), Attribute::eForm::Unqualified)
		};

		const std::map<std::string, Attribute::eUse> UseString2Use =
		{
			std::make_pair(std::string("optional"), Attribute::eUse::Optional),
			std::make_pair(std::string("required"), Attribute::eUse::Required),
			std::make_pair(std::string("prohibited"), Attribute::eUse::Prohibited),
		};
	};
};
