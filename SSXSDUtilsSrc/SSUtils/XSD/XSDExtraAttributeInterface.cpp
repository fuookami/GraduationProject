#include "stdafx.h"
#include "XSDExtraAttributeInterface.h"
#include "SSUtils\StringUtils.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		const std::string IXSDExtraAttributeInterface::DefaultAttrValue = SSUtils::String::EmptyString();

		void IXSDExtraAttributeInterface::addExAttr(const std::pair<std::string, std::string>& pair)
		{
			m_exAttrs.insert(pair);
		}

		void IXSDExtraAttributeInterface::addExAttr(std::pair<std::string, std::string>&& pair)
		{
			m_exAttrs.insert(std::move(pair));
		}

		void IXSDExtraAttributeInterface::addExAttr(const std::string & key, const std::string & value)
		{
			m_exAttrs.insert(std::make_pair(key, value));
		}

		void IXSDExtraAttributeInterface::addExAttr(const std::string & key, std::string && value)
		{
			m_exAttrs.insert(std::make_pair(key, std::move(value)));
		}

		void IXSDExtraAttributeInterface::eraseExAttr(const std::string & key)
		{
			m_exAttrs.erase(key);
		}

		void IXSDExtraAttributeInterface::clearExAttrs(void)
		{
			m_exAttrs.clear();
		}

		void IXSDExtraAttributeInterface::setExAttr(const std::string & key, const std::string & value)
		{
			m_exAttrs[key].assign(value);
		}

		void IXSDExtraAttributeInterface::setExAttr(const std::string & key, std::string && value)
		{
			m_exAttrs[key].assign(std::move(value));
		}

		void IXSDExtraAttributeInterface::setExAttr(const std::pair<std::string, std::string>& pair)
		{
			m_exAttrs[pair.first].assign(pair.second);
		}

		void IXSDExtraAttributeInterface::setExAttr(std::pair<std::string, std::string>&& pair)
		{
			m_exAttrs[pair.first].assign(std::move(pair.second));
		}

		const bool IXSDExtraAttributeInterface::hasExAttr(const std::string & key) const
		{
			return m_exAttrs.find(key) != m_exAttrs.cend();
		}

		const std::string & IXSDExtraAttributeInterface::getExAttr(const std::string & key, const std::string & defaultValue) const
		{
			auto it(m_exAttrs.find(key));
			return it != m_exAttrs.cend() ? it->second : defaultValue;
		}

		const std::map<std::string, std::string>& IXSDExtraAttributeInterface::getExAttrs(void) const
		{
			return m_exAttrs;
		}

		std::map<std::string, std::string>& IXSDExtraAttributeInterface::getExAttrs(void)
		{
			return m_exAttrs;
		}

		bool IXSDExtraAttributeInterface::loadExAttr(const std::shared_ptr<SSUtils::XML::Node>& node, const std::set<std::string>& BaseAttrs)
		{
			for (const auto &pair : node->getAttrs())
			{
				if (BaseAttrs.find(pair.first) == BaseAttrs.cend())
				{
					addExAttr(pair);
				}
			}
			return true;
		}

		std::shared_ptr<SSUtils::XML::Node> IXSDExtraAttributeInterface::saveExAttr(const std::shared_ptr<SSUtils::XML::Node>& node) const
		{
			for (const auto &pair : m_exAttrs)
			{
				if (!pair.second.empty())
				{
					node->addAttr(pair);
				}
			}
			return node;
		}

	};
};
