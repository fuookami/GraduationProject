#pragma once

#include <string>

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
