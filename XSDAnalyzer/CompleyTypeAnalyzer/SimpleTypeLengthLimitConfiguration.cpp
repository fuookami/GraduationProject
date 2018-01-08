#include "SimpleTypeLengthLimitConfiguration.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		LengthLimitConfiguration::LengthLimitConfiguration(const int minLength, const int maxLength)
			: m_minLength(minLength), m_maxLength(maxLength)
		{
		}

		LengthLimitConfiguration::LengthLimitConfiguration(const LengthLimitConfiguration & ano)
			: m_minLength(ano.m_minLength), m_maxLength(ano.m_maxLength)
		{
		}

		LengthLimitConfiguration::LengthLimitConfiguration(const LengthLimitConfiguration && ano)
			: m_minLength(ano.m_minLength), m_maxLength(ano.m_maxLength)
		{
		}

		LengthLimitConfiguration & LengthLimitConfiguration::operator=(const LengthLimitConfiguration & rhs)
		{
			m_minLength = rhs.m_minLength;
			m_maxLength = rhs.m_maxLength;

			return *this;
		}

		LengthLimitConfiguration & LengthLimitConfiguration::operator=(const LengthLimitConfiguration && rhs)
		{
			m_minLength = rhs.m_minLength;
			m_maxLength = rhs.m_maxLength;

			return *this;
		}

		LengthLimitConfiguration::~LengthLimitConfiguration(void)
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
