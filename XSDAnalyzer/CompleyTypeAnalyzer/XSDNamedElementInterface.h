#pragma once

#include <string>

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		class IXSDNamedElementInterface abstract
		{
		protected:
			IXSDNamedElementInterface(void);
			IXSDNamedElementInterface(const std::string &name);
			IXSDNamedElementInterface(const std::string &&name);
			IXSDNamedElementInterface(const IXSDNamedElementInterface &ano);
			IXSDNamedElementInterface(const IXSDNamedElementInterface &&ano);
			IXSDNamedElementInterface &operator=(const IXSDNamedElementInterface &rhs);
			IXSDNamedElementInterface &operator=(const IXSDNamedElementInterface &&rhs);
		public:
			virtual ~IXSDNamedElementInterface(void);

			inline void setName(const std::string &name) { m_name.assign(name); }
			inline void setName(const std::string &&name) { m_name.assign(std::move(name)); }
			inline const std::string &getName(void) const { return m_name; }

			inline void setDescription(const std::string &description) { m_description.assign(description); }
			inline void setDescription(const std::string &&description) { m_description.assign(description); }
			inline const std::string &getDescription(void) const { return m_description; }

		private:
			std::string m_name;
			std::string m_description;
		};
	};
};
