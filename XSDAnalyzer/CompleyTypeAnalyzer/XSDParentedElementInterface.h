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
				tComplexType,
				tAttributeGroup,
				tElementGroup,
				tNonParent
			};

		protected:
			IXSDParentedElementInterface(void);
			IXSDParentedElementInterface(const IXSDParentedElementInterface &ano);
			IXSDParentedElementInterface(const IXSDParentedElementInterface &&ano);
			IXSDParentedElementInterface &operator=(const IXSDParentedElementInterface &rhs);
			IXSDParentedElementInterface &operator=(const IXSDParentedElementInterface &&rhs);
		public:
			virtual ~IXSDParentedElementInterface(void);

		public:
			inline void setParent(const eParentType parentType, const std::string &parentName) { m_parentType = parentType; m_parentName.assign(parentName); }
			inline void setParent(const eParentType parentType, const std::string &&parentName) { m_parentType = parentType; m_parentName.assign(std::move(parentName)); }
			inline const bool hasParent(void) const { return m_parentType != eParentType::tNonParent; }
			inline const eParentType getParentType(void) const { return m_parentType; }
			inline const std::string &getParentName(void) const { return m_parentName; }

		private:
			eParentType m_parentType;
			std::string m_parentName;
		};
	};
};
