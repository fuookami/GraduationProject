#include "SimpleTypeLengthLimitConfiguration.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		LengthLimitConfiguration::LengthLimitConfiguration(const int minLength, const int maxLength)
			: m_minLength(minLength), m_maxLength(maxLength)
		{
		}

		const bool LengthLimitConfiguration::setMinLengthValidator(const int minLength)
		{
			if (m_maxLength == NoLengthValidator
				|| (minLength >= 0 && minLength <= m_maxLength))
			{
				m_minLength = minLength;
				return true;
			}

			return false;
		}

		const bool  LengthLimitConfiguration::setMaxLengthValidator(const int maxLength)
		{
			if (maxLength == NoLengthValidator
				|| (maxLength >= 0 && m_minLength <= maxLength))
			{
				m_maxLength = maxLength;
				return true;
			}

			return false;
		}
	};
};
