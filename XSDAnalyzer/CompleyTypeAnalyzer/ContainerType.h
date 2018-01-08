#pragma once

#include "SimpleTypeInterface.h"

#include <set>
#include <map>

namespace XSDFrontend
{
	namespace SimpleType
	{
		class ContainerType final : public ISimpleTypeInterface
		{
		public:
			enum class eBaseType
			{
				tUnion,
				tList
			};

		public:
			ContainerType(const std::string &name, const eBaseType baseType);
			ContainerType(const std::string &&name, const eBaseType baseType);
			ContainerType(const ContainerType &ano);
			ContainerType(const ContainerType &&ano);
			ContainerType &operator=(const ContainerType &rhs);
			ContainerType &operator=(const ContainerType &&rhs);
			~ContainerType(void);

			void refreshValidator(const XMLUtils::XMLNode &node) override;

			inline void addBaseType(const std::string &typeName) { m_baseTypeNames.insert(typeName); }
			inline void addBaseType(const std::string &&typeName) { m_baseTypeNames.insert(std::move(typeName)); }
			inline void eraseBaseType(const std::string &typeName) { m_baseTypeNames.erase(typeName); }
			inline void clearBaseTypes(void) { m_baseTypeNames.clear(); }
			inline const bool hasBaseType(const std::string &typeName) { return m_baseTypeNames.find(typeName) != m_baseTypeNames.cend(); }
			inline const std::set<std::string> &getBaseTypes(void) const { return m_baseTypeNames; }

		public:
			eBaseType m_baseType;

			std::set<std::string> m_baseTypeNames;
		};
	};
};
