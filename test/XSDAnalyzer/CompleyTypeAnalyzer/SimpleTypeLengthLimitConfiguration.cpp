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

		const bool LengthLimitConfiguration::refreshLengthLimitConfiguration(const std::shared_ptr<SSUtils::XML::Node> node)
		{
			bool hasMaxLength(false);
			int maxLength(NoLengthValidator);

			bool hasMinLength(false);
			int minLength(NoLengthValidator);

			if (node->hasChild(XSDFrontend::Token::MaxLengthValidatorTag))
			{
				hasMaxLength = true;
				auto child = node->getChildren()[node->findChild(XSDFrontend::Token::MaxLengthValidatorTag)];
				if (child != nullptr)
				{
					maxLength = std::stoi(child->getAttr(XSDFrontend::Token::ValueAttr));
				}
			}
			if (node->hasChild(XSDFrontend::Token::MinLengthValidatorTag))
			{
				hasMinLength = true;
				auto child = node->getChildren()[node->findChild(XSDFrontend::Token::MinLengthValidatorTag)];
				if (child != nullptr)
				{
					minLength = std::stoi(child->getAttr(XSDFrontend::Token::ValueAttr));
				}
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

		std::shared_ptr<SSUtils::XML::Node> LengthLimitConfiguration::saveLengthLimitConfiguration(const std::shared_ptr<SSUtils::XML::Node> root) const
		{
			if (m_minLength >= 0)
			{
				auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::MinLengthValidatorTag));
				node->setAttr(XSDFrontend::Token::ValueAttr, std::to_string(m_minLength));
				root->addChild(node);
			}
			if (m_maxLength >= 0)
			{
				auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::MaxLengthValidatorTag));
				node->setAttr(XSDFrontend::Token::ValueAttr, std::to_string(m_maxLength));
				root->addChild(node);
			}
			return root;
		}
	};
};
