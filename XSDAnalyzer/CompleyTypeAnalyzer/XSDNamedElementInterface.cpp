#include "XSDNamedElementInterface.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		IXSDNamedElementInterface::IXSDNamedElementInterface(const std::string & name)
			: m_name(name), m_description()
		{
		}

		IXSDNamedElementInterface::IXSDNamedElementInterface(std::string && name)
			: m_name(std::move(name)), m_description()
		{
		}
	};
};
