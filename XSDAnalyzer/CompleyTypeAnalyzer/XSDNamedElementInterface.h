#pragma once

#include <string>
#include <map>
#include <memory>
#include "XMLUtils.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		class IXSDNamedElementInterface abstract
		{
		protected:
			IXSDNamedElementInterface(void) = default;
			IXSDNamedElementInterface(const std::string &name);
			IXSDNamedElementInterface(std::string &&name);
			IXSDNamedElementInterface(const IXSDNamedElementInterface &ano) = default;
			IXSDNamedElementInterface(IXSDNamedElementInterface &&ano) = default;
			IXSDNamedElementInterface &operator=(const IXSDNamedElementInterface &rhs) = default;
			IXSDNamedElementInterface &operator=(IXSDNamedElementInterface &&rhs) = default;
		public:
			virtual ~IXSDNamedElementInterface(void) = default;
			static const std::string DefaultAttrValue;

			inline void setName(const std::string &name) { m_name.assign(name); }
			inline void setName(std::string &&name) { m_name.assign(std::move(name)); }
			inline const std::string &getName(void) const { return m_name; }

			inline void setDescription(const std::string &description, const std::string &lang = std::string("cn")) { m_description.assign(description); m_descriptionLang.assign(lang); }
			inline void setDescription(std::string &&description, const std::string &lang = std::string("cn")) { m_description.assign(std::move(description)); m_descriptionLang.assign(lang); }
			inline const std::string &getDescription(void) const { return m_description; }
			inline const std::string &getDescriptionLang(void) const { return m_descriptionLang; }

			inline void setAnonymous(const bool anonymous) { m_anonymous = anonymous; }
			inline const bool getAnonymous(void) const { return m_anonymous; }

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

			virtual bool loadExAttr(const std::shared_ptr<SSUtils::XML::Node> &node) = 0;
			std::shared_ptr<SSUtils::XML::Node> saveExAttr(const std::shared_ptr<SSUtils::XML::Node> &node) const;

		private:
			std::string m_name;
			std::string m_description;
			std::string m_descriptionLang;

			bool m_anonymous;
			std::map<std::string, std::string> m_exAttrs;
		};
	};
};
