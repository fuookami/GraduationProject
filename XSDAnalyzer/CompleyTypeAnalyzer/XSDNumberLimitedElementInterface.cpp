#include "XSDNumberLimitedElementInterface.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		const std::string IXSDNumberLimitedElementInterface::MaxOccursUnboundedString("unbounded");


		IXSDNumberLimitedElementInterface::IXSDNumberLimitedElementInterface(const int minOccurs, const int maxOccurs)
			: m_minOccurs(1), m_maxOccurs(1)
		{

		}

		const bool IXSDNumberLimitedElementInterface::setMinOccurs(const int newMinOccurs)
		{
			if (m_maxOccurs == MaxOccursUnbounded
				|| (newMinOccurs >= 0 && newMinOccurs <= m_maxOccurs))
			{
				m_minOccurs = newMinOccurs;
				return true;
			}

			return false;
		}

		const bool IXSDNumberLimitedElementInterface::setMaxOccurs(const int newMaxOccurs)
		{
			if (newMaxOccurs == MaxOccursUnbounded
				|| (newMaxOccurs >= 0 && m_minOccurs <= newMaxOccurs))
			{
				m_maxOccurs = newMaxOccurs;
				return true;
			}

			return false;
		}
	};
};
