#pragma once

#include <string>

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		class IXSDParentedElementInterface abstract
		{
		public:
			enum class eParentType
			{
				tAttributeGroup,
				tComplexType,
				tElementGroup,
				tNonParent
			};

		protected:
			IXSDParentedElementInterface(void) = default;
			IXSDParentedElementInterface(const IXSDParentedElementInterface &ano) = default;
			IXSDParentedElementInterface(IXSDParentedElementInterface &&ano) = default;
			IXSDParentedElementInterface &operator=(const IXSDParentedElementInterface &rhs) = default;
			IXSDParentedElementInterface &operator=(IXSDParentedElementInterface &&rhs) = default;
		public:
			virtual ~IXSDParentedElementInterface(void) = default;

		public:
			inline void setParent(const eParentType parentType, const std::string &parentName) { m_parentType = parentType; m_parentName.assign(parentName); }
			inline void setParent(const eParentType parentType, std::string &&parentName) { m_parentType = parentType; m_parentName.assign(std::move(parentName)); }
			inline const bool hasParent(void) const { return m_parentType != eParentType::tNonParent; }
			inline const eParentType getParentType(void) const { return m_parentType; }
			inline const std::string &getParentName(void) const { return m_parentName; }

		private:
			eParentType m_parentType = eParentType::tNonParent;
			std::string m_parentName;
		};
	};
};
