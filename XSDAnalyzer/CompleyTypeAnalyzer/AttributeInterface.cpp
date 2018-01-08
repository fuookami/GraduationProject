#include "AttributeInterface.h"

namespace XSDFrontend
{
	namespace Attribute
	{
		IAttributeInterface::IAttributeInterface(const eAttributeType type)
			: IXSDParentedElementInterface(), m_type(type)
		{
		}

		IAttributeInterface::IAttributeInterface(const IAttributeInterface & ano)
			: IXSDParentedElementInterface(ano), m_type(ano.m_type)
		{
		}

		IAttributeInterface::IAttributeInterface(const IAttributeInterface && ano)
			: IXSDParentedElementInterface(std::move(ano)), m_type(ano.m_type)
		{
		}

		IAttributeInterface & IAttributeInterface::operator=(const IAttributeInterface & rhs)
		{
			m_type = rhs.m_type;

			IXSDParentedElementInterface::operator=(rhs);

			return *this;
		}

		IAttributeInterface & IAttributeInterface::operator=(const IAttributeInterface && rhs)
		{
			m_type = rhs.m_type;

			IXSDParentedElementInterface::operator=(std::move(rhs));

			return *this;
		}

		IAttributeInterface::~IAttributeInterface(void)
		{
		}
	};
};
