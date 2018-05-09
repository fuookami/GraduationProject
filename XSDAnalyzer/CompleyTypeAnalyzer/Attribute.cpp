#include "Attribute.h"

namespace XSDFrontend
{
	namespace Attribute
	{
		const std::map<std::string, Attribute::eForm> Attribute::String2Form =
		{
			std::make_pair(std::string("qualified"), Attribute::eForm::Qualified),
			std::make_pair(std::string("unqualified"), Attribute::eForm::Unqualified)
		};

		const std::map<std::string, Attribute::eUse> Attribute::String2Use =
		{
			std::make_pair(std::string("optional"), Attribute::eUse::Optional),
			std::make_pair(std::string("required"), Attribute::eUse::Required),
			std::make_pair(std::string("prohibited"), Attribute::eUse::Prohibited),
		};

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
