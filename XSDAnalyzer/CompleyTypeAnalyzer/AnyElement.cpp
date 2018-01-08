#include "AnyElement.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		const std::string AnyElement::MaxOccursUnboundedString("unbounded");

		AnyElement::AnyElement(const int minOccurs, const int maxOccurs, const eNamespaceValidator namesapceValidator, const eProcessContents processContents)
			: IElementInterface(IElementInterface::eElementType::tAnyElement), 
			m_namespaceValidator(namesapceValidator), m_processContents(processContents)
		{
		}

		AnyElement::AnyElement(const AnyElement & ano)
			: IElementInterface(ano), 
			m_namespaceValidator(ano.m_namespaceValidator), m_processContents(ano.m_processContents)
		{
		}

		AnyElement::AnyElement(const AnyElement && ano)
			: IElementInterface(std::move(ano)), 
			m_namespaceValidator(ano.m_namespaceValidator), m_processContents(ano.m_processContents)
		{
		}

		AnyElement & AnyElement::operator=(const AnyElement & rhs)
		{
			m_namespaceValidator = rhs.m_namespaceValidator;
			m_processContents = rhs.m_processContents;

			IElementInterface::operator=(rhs);

			return *this;
		}

		AnyElement & AnyElement::operator=(const AnyElement && rhs)
		{
			m_namespaceValidator = rhs.m_namespaceValidator;
			m_processContents = rhs.m_processContents;

			IElementInterface::operator=(std::move(rhs));

			return *this;
		}

		AnyElement::~AnyElement(void)
		{
		}
	};
};
