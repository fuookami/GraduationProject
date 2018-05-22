#pragma once

#include "SimpleTypeInterface.h"

#include <set>
#include <map>
#include <boost/bimap.hpp>

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
			static const boost::bimap<std::string, eBaseType> String2ItemType;

		public:
			ContainerType(const std::string &name, const eBaseType baseType);
			ContainerType(std::string &&name, const eBaseType baseType);
			ContainerType(const ContainerType &ano) = default;
			ContainerType(ContainerType &&ano) = default;
			ContainerType &operator=(const ContainerType &rhs) = default;
			ContainerType &operator=(ContainerType &&rhs) = default;
			~ContainerType(void) = default;

			const bool refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node) override;
			std::set<std::string> neededTokens(void) const override;

			inline void setBaseType(const eBaseType &type) { m_baseType = type; }
			inline eBaseType getBaseType(void) const { return m_baseType; }

			inline void addBaseType(const std::string &typeName) { m_baseTypeNames.insert(typeName); }
			inline void addBaseType(std::string &&typeName) { m_baseTypeNames.insert(std::move(typeName)); }
			inline void eraseBaseType(const std::string &typeName) { m_baseTypeNames.erase(typeName); }
			inline void clearBaseTypes(void) { m_baseTypeNames.clear(); }
			inline const bool hasBaseType(const std::string &typeName) const { return m_baseTypeNames.find(typeName) != m_baseTypeNames.cend(); }
			inline const std::set<std::string> &getBaseTypes(void) const { return m_baseTypeNames; }

		public:
			eBaseType m_baseType;

			std::set<std::string> m_baseTypeNames;
		};
	};
};
