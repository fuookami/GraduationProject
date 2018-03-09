#include "SimpleTypeLengthLimitConfiguration.h"
#include "XSDToken.h"

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

		const bool LengthLimitConfiguration::refreshLengthLimitConfiguration(const XMLUtils::XMLNode & node)
		{
			bool hasMaxLength(false);
			int maxLength(NoLengthValidator);

			bool hasMinLength(false);
			int minLength(NoLengthValidator);

			if (node.hasChild(XSDFrontend::Token::MaxLengthValidatorTag))
			{
				hasMaxLength = true;
				maxLength = std::stoi(node.getChildren()[node.findChild(XSDFrontend::Token::MaxLengthValidatorTag)].getAttr(XSDFrontend::Token::ValueAttr));
			}
			if (node.hasChild(XSDFrontend::Token::MinLengthValidatorTag))
			{
				hasMinLength = true;
				minLength = std::stoi(node.getChildren()[node.findChild(XSDFrontend::Token::MinLengthValidatorTag)].getAttr(XSDFrontend::Token::ValueAttr));
			}

			if (maxLength != NoLengthValidator && minLength > maxLength)
			{
				std::cerr << "定义的最小长度(" << minLength << ")大于最大值(" << maxLength << ")。";
				return false;
			}

			if (hasMaxLength)
			{
				setMaxLengthValidator(maxLength);
			}
			if (hasMinLength)
			{
				setMinLengthValidator(minLength);
			}
			return true;
		}
	};
};
