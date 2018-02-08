#include "XSDNumberLimitedElementInterface.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		const std::string IXSDNumberLimitedElementInterface::MaxOccursUnboundedString("unbounded");


		IXSDNumberLimitedElementInterface::IXSDNumberLimitedElementInterface(const int minOccurs, const int maxOccurs)
			: m_minOccurs(1), m_maxOccurs(1)
		{

		}

		const bool IXSDNumberLimitedElementInterface::setMinOccurs(const unsigned int newMinOccurs)
		{
			if (m_maxOccurs == MaxOccursUnbounded
				|| (newMinOccurs >= 0 && newMinOccurs <= m_maxOccurs))
			{
				m_minOccurs = newMinOccurs;
				return true;
			}

			return false;
		}

		const bool IXSDNumberLimitedElementInterface::setMaxOccurs(const unsigned int newMaxOccurs)
		{
			if (newMaxOccurs == MaxOccursUnbounded
				|| (newMaxOccurs >= 0 && m_minOccurs <= newMaxOccurs))
			{
				m_maxOccurs = newMaxOccurs;
				return true;
			}

			return false;
		}

		const bool IXSDNumberLimitedElementInterface::loadNumberLimitation(const XMLUtils::XMLNode & node)
		{
			bool ret(true);
			if (node.hasAttr(XSDFrontend::Token::MinOccursAttr))
			{
				ret &= setMinOccurs(std::stoul(node.getAttr(XSDFrontend::Token::MinOccursAttr)));
			}

			if (node.hasAttr(XSDFrontend::Token::MaxOccursAttr))
			{
				ret &= setMaxOccurs(node.getAttr(XSDFrontend::Token::MaxOccursAttr) == MaxOccursUnboundedString 
					? MaxOccursUnbounded
					: std::stoul(node.getAttr(XSDFrontend::Token::MaxOccursAttr)));
			}
			return ret;
		}
	};
};
