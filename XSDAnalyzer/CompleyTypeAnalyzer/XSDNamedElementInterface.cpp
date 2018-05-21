#include "XSDNamedElementInterface.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		IXSDNamedElementInterface::IXSDNamedElementInterface(const std::string & name)
			: m_name(name), m_description(), m_anonymous(false)
		{
		}

		IXSDNamedElementInterface::IXSDNamedElementInterface(std::string && name)
			: m_name(std::move(name)), m_description(), m_anonymous(false)
		{
		}

		void IXSDNamedElementInterface::addExAttr(const std::pair<std::string, std::string>& pair)
		{
			m_exAttrs.insert(pair);
		}

		void IXSDNamedElementInterface::addExAttr(std::pair<std::string, std::string>&& pair)
		{
			m_exAttrs.insert(std::move(pair));
		}

		void IXSDNamedElementInterface::addExAttr(const std::string & key, const std::string & value)
		{
			m_exAttrs.insert(std::make_pair(key, value));
		}

		void IXSDNamedElementInterface::addExAttr(const std::string & key, std::string && value)
		{
			m_exAttrs.insert(std::make_pair(key, std::move(value)));
		}

		void IXSDNamedElementInterface::eraseExAttr(const std::string & key)
		{
			m_exAttrs.erase(key);
		}

		void IXSDNamedElementInterface::clearExAttrs(void)
		{
			m_exAttrs.clear();
		}

		void IXSDNamedElementInterface::setExAttr(const std::string & key, const std::string & value)
		{
			m_exAttrs[key].assign(value);
		}

		void IXSDNamedElementInterface::setExAttr(const std::string & key, std::string && value)
		{
			m_exAttrs[key].assign(std::move(value));
		}

		void IXSDNamedElementInterface::setExAttr(const std::pair<std::string, std::string>& pair)
		{
			m_exAttrs[pair.first].assign(pair.second);
		}

		void IXSDNamedElementInterface::setExAttr(std::pair<std::string, std::string>&& pair)
		{
			m_exAttrs[pair.first].assign(std::move(pair.second));
		}

		const bool IXSDNamedElementInterface::hasExAttr(const std::string & key) const
		{
			return m_exAttrs.find(key) != m_exAttrs.cend();
		}

		const std::string & IXSDNamedElementInterface::getExAttr(const std::string & key, const std::string & defaultValue) const
		{
			auto it(m_exAttrs.find(key));
			return it != m_exAttrs.cend() ? it->second : defaultValue;
		}

		const std::map<std::string, std::string>& IXSDNamedElementInterface::getExAttrs(void) const
		{
			return m_exAttrs;
		}

		std::map<std::string, std::string>& IXSDNamedElementInterface::getExAttrs(void)
		{
			return m_exAttrs;
		}
	};
};
