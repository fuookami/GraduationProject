#include "ElementInterface.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		IElementInterface::IElementInterface(const eElementType type)
			: IXSDParentedElementInterface(), IXSDNumberLimitedElementInterface(), m_type(type)
		{
		}

		IElementInterface::IElementInterface(const IElementInterface & ano)
			: IXSDParentedElementInterface(ano), IXSDNumberLimitedElementInterface(ano), m_type(ano.m_type)
		{
		}

		IElementInterface::IElementInterface(const IElementInterface && ano)
			: IXSDParentedElementInterface(std::move(ano)), IXSDNumberLimitedElementInterface(std::move(ano)), m_type(ano.m_type)
		{
		}

		IElementInterface & XSDFrontend::ComplexType::IElementInterface::operator=(const IElementInterface & rhs)
		{
			m_type = rhs.m_type;

			IXSDParentedElementInterface::operator=(rhs);
			IXSDNumberLimitedElementInterface::operator=(rhs);

			return *this;
		}

		IElementInterface & XSDFrontend::ComplexType::IElementInterface::operator=(const IElementInterface && rhs)
		{
			m_type = rhs.m_type;

			IXSDParentedElementInterface::operator=(std::move(rhs));
			IXSDNumberLimitedElementInterface::operator=(std::move(rhs));

			return *this;
		}

		XSDFrontend::ComplexType::IElementInterface::~IElementInterface(void)
		{
		}
	};
};
