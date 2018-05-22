#pragma once

#include <set>
#include "XMLUtils.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		class IXSDExtraAttributeInterface abstract
		{
		protected:
			IXSDExtraAttributeInterface(void) = default;
			IXSDExtraAttributeInterface(const IXSDExtraAttributeInterface &ano) = default;
			IXSDExtraAttributeInterface(IXSDExtraAttributeInterface &&ano) = default;
			IXSDExtraAttributeInterface &operator=(const IXSDExtraAttributeInterface &rhs) = default;
			IXSDExtraAttributeInterface &operator=(IXSDExtraAttributeInterface &&rhs) = default;
		public:
			virtual ~IXSDExtraAttributeInterface(void) = default;
			static const std::string DefaultAttrValue;

			void addExAttr(const std::pair<std::string, std::string> &pair);
			void addExAttr(std::pair<std::string, std::string> &&pair);
			void addExAttr(const std::string &key, const std::string &value);
			void addExAttr(const std::string &key, std::string &&value);
			void eraseExAttr(const std::string &key);
			void clearExAttrs(void);
			void setExAttr(const std::string &key, const std::string &value);
			void setExAttr(const std::string &key, std::string &&value);
			void setExAttr(const std::pair<std::string, std::string> &pair);
			void setExAttr(std::pair<std::string, std::string> &&pair);
			const bool hasExAttr(const std::string &key) const;
			const std::string &getExAttr(const std::string &key, const std::string &defaultValue = DefaultAttrValue) const;
			const std::map<std::string, std::string> &getExAttrs(void) const;
			std::map<std::string, std::string> &getExAttrs(void);

			bool loadExAttr(const std::shared_ptr<SSUtils::XML::Node> &node, const std::set<std::string> &BaseAttrs);
			std::shared_ptr<SSUtils::XML::Node> saveExAttr(const std::shared_ptr<SSUtils::XML::Node> &node) const;

		private:
			std::map<std::string, std::string> m_exAttrs;
		};
	};
};
