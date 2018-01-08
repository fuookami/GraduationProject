#include "XSDNamedElementInterface.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		IXSDNamedElementInterface::IXSDNamedElementInterface(void)
			: m_name(), m_description()
		{
		}

		IXSDNamedElementInterface::IXSDNamedElementInterface(const std::string & name)
			: m_name(name), m_description()
		{
		}

		IXSDNamedElementInterface::IXSDNamedElementInterface(const std::string && name)
			: m_name(std::move(name)), m_description()
		{
		}

		IXSDNamedElementInterface::IXSDNamedElementInterface(const IXSDNamedElementInterface & ano)
			: m_name(ano.m_name), m_description(ano.m_description)
		{
		}

		IXSDNamedElementInterface::IXSDNamedElementInterface(const IXSDNamedElementInterface && ano)
			: m_name(std::move(ano.m_name)), m_description(std::move(ano.m_description))
		{
		}

		IXSDNamedElementInterface & IXSDNamedElementInterface::operator=(const IXSDNamedElementInterface & rhs)
		{
			m_name.assign(rhs.m_name);
			m_description.assign(rhs.m_description);

			return *this;
		}

		IXSDNamedElementInterface & IXSDNamedElementInterface::operator=(const IXSDNamedElementInterface && rhs)
		{
			m_name.assign(std::move(rhs.m_name));
			m_description.assign(std::move(rhs.m_description));

			return *this;
		}

		IXSDNamedElementInterface::~IXSDNamedElementInterface(void)
		{
		}
	};
};
