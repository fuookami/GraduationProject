#include "XSDNamedTypedElementInterface.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(const std::string & name)
			: IXSDNamedElementInterface(name), m_type()
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(std::string && name)
			: IXSDNamedElementInterface(std::move(name)), m_type()
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(const std::string & name, const std::string & type)
			: IXSDNamedElementInterface(name), m_type(type)
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(const std::string & name, std::string && type)
			: IXSDNamedElementInterface(name), m_type(std::move(type))
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(std::string && name, const std::string & type)
			: IXSDNamedElementInterface(std::move(name)), m_type(type)
		{
		}

		IXSDNamedTypedElementInterface::IXSDNamedTypedElementInterface(std::string && name, std::string && type)
			: IXSDNamedElementInterface(std::move(name)), m_type(std::move(type))
		{
		}
	};
};
