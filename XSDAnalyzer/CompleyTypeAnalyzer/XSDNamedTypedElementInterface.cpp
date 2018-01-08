#include "XSDNamedTypedElementInterface.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(void)
			: IXSDNamedElementInterface(), m_type()
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(const std::string & name)
			: IXSDNamedElementInterface(name), m_type()
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(const std::string && name)
			: IXSDNamedElementInterface(std::move(name)), m_type()
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(const std::string & name, const std::string & type)
			: IXSDNamedElementInterface(name), m_type(type)
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(const std::string & name, const std::string && type)
			: IXSDNamedElementInterface(name), m_type(std::move(type))
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(const std::string && name, const std::string & type)
			: IXSDNamedElementInterface(std::move(name)), m_type(type)
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(const std::string && name, const std::string && type)
			: IXSDNamedElementInterface(std::move(name)), m_type(std::move(type))
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(const IXSDNamedTypedElementInterface & ano)
			: IXSDNamedElementInterface(ano), m_type(ano.m_type)
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(const IXSDNamedTypedElementInterface && ano)
			: IXSDNamedElementInterface(std::move(ano)), m_type(std::move(ano.m_type))
		{
		}

		IXSDNamedTypedElementInterface & IXSDNamedTypedElementInterface::operator=(const IXSDNamedTypedElementInterface & rhs)
		{
			m_type.assign(rhs.m_type);

			IXSDNamedElementInterface::operator=(rhs);

			return *this;
		}

		IXSDNamedTypedElementInterface & IXSDNamedTypedElementInterface::operator=(const IXSDNamedTypedElementInterface && rhs)
		{
			m_type.assign(std::move(rhs.m_type));

			IXSDNamedElementInterface::operator=(std::move(rhs));

			return *this;
		}

		IXSDNamedTypedElementInterface::~IXSDNamedTypedElementInterface(void)
		{
		}
	};
};
