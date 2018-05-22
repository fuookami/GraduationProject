#include "XSDValueStatedElementInterface.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		const std::string IXSDValueStatedElementInterface::NoDefaultValue("");
		const std::string &IXSDValueStatedElementInterface::NoFixedValue(NoDefaultValue);

		IXSDValueStatedElementInterface::IXSDValueStatedElementInterface(void)
			: m_hasDefault(false), m_defaultEnabled(true), m_default(), 
			m_hasFixed(false), m_fixedEnabled(true), m_fixed()
		{
		}

		const bool IXSDValueStatedElementInterface::setDefault(const std::string & defaultValue)
		{
			if (m_defaultEnabled)
			{
				m_hasDefault = true;
				m_default.assign(defaultValue);
				clearFixed();
				return true;
			}

			return false;
		}

		const bool IXSDValueStatedElementInterface::setDefault(std::string && defaultValue)
		{
			if (m_defaultEnabled)
			{
				m_hasDefault = true;
				m_default.assign(std::move(defaultValue));
				clearFixed();
				return true;
			}

			return false;
		}

		const bool IXSDValueStatedElementInterface::setFixed(const std::string & fixedValue)
		{
			if (m_fixedEnabled)
			{
				m_hasFixed = true;
				m_fixed.assign(fixedValue);
				clearDefault();
				return true;
			}

			return false;
		}
		
		const bool IXSDValueStatedElementInterface::setFixed(std::string && fixedValue)
		{
			if (m_fixedEnabled)
			{
				m_hasFixed = true;
				m_fixed.assign(std::move(fixedValue));
				clearDefault();
				return true;
			}

			return false;
		}

		const bool IXSDValueStatedElementInterface::loadValueStatement(const std::shared_ptr<SSUtils::XML::Node> & node)
		{
			bool ret(true);
			if (node->hasAttr(XSDFrontend::Token::DefaultAttr) && node->hasAttr(XSDFrontend::Token::FixedAttr))
			{
				return false;
			}

			if (node->hasAttr(XSDFrontend::Token::DefaultAttr))
			{
				ret &= setDefault(node->getAttr(XSDFrontend::Token::DefaultAttr));
			}

			if (node->hasAttr(XSDFrontend::Token::FixedAttr))
			{
				ret &= setFixed(node->getAttr(XSDFrontend::Token::FixedAttr));
			}

			return ret;
		}

		std::shared_ptr<SSUtils::XML::Node> IXSDValueStatedElementInterface::saveValueStatement(const std::shared_ptr<SSUtils::XML::Node>& node) const
		{
			if (hasDefault())
			{
				node->addAttr(XSDFrontend::Token::DefaultAttr, m_default);
			}
			else if (hasFixed())
			{
				node->addAttr(XSDFrontend::Token::FixedAttr, m_fixed);
			}

			return node;
		}

		void IXSDValueStatedElementInterface::setDefaultEnabled(const bool enabled)
		{
			if (m_defaultEnabled && !enabled)
			{
				clearDefault();
				m_defaultEnabled = false;
			}
		}

		void IXSDValueStatedElementInterface::setFixedEnabled(const bool enabled)
		{
			if (m_fixedEnabled && !enabled)
			{
				clearFixed();
				m_fixedEnabled = false;
			}
		}

		void IXSDValueStatedElementInterface::clearDefault(void)
		{
			if (m_hasDefault)
			{
				m_hasDefault = false;
				m_default.clear();
			}
		}

		void IXSDValueStatedElementInterface::clearFixed(void)
		{
			if (m_hasFixed)
			{
				m_hasFixed = false;
				m_fixed.clear();
			}
		}
	};
};
