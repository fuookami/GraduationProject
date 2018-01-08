#include "AnyAttribute.h"

namespace XSDFrontend
{
	namespace Attribute
	{
		AnyAttribute::AnyAttribute(const eNamespaceValidator namesapceValidator, const eProcessContents processContents)
			: IAttributeInterface(IAttributeInterface::eAttributeType::tAnyAttribute), m_namespaceValidator(namesapceValidator), m_processContents(processContents)
		{
		}

		AnyAttribute::AnyAttribute(const AnyAttribute & ano)
			: IAttributeInterface(ano), m_namespaceValidator(ano.m_namespaceValidator), m_processContents(ano.m_processContents)
		{
		}

		AnyAttribute::AnyAttribute(const AnyAttribute && ano)
			: IAttributeInterface(std::move(ano)), m_namespaceValidator(ano.m_namespaceValidator), m_processContents(ano.m_processContents)
		{
		}

		AnyAttribute & AnyAttribute::operator=(const AnyAttribute & rhs)
		{
			m_namespaceValidator = rhs.m_namespaceValidator;
			m_processContents = rhs.m_processContents;

			IAttributeInterface::operator=(rhs);

			return *this;
		}

		AnyAttribute & AnyAttribute::operator=(const AnyAttribute && rhs)
		{
			m_namespaceValidator = rhs.m_namespaceValidator;
			m_processContents = rhs.m_processContents;

			IAttributeInterface::operator=(std::move(rhs));

			return *this;
		}

		AnyAttribute::~AnyAttribute(void)
		{
		}
	}
};
