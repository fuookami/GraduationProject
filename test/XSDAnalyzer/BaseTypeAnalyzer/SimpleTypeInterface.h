#pragma once

#include <boost/property_tree/ptree.hpp>

#include <string>

namespace XSDAnalyzer
{
	namespace SimpleType
	{
		enum class eSimpleType
		{
			tStringType,
			tNumberType,
			tDateTimeType,
			tDataType,
			tContainerType,
			tNonExist
		};

		class ISimpleTypeInterface
		{
		public:
			enum class eWhiteSpace
			{
				Preserve,
				Replace,
				Collapse
			};

		public:
			ISimpleTypeInterface(const eSimpleType type = eSimpleType::tStringType, const eWhiteSpace whitSpace = eWhiteSpace::Preserve);
			ISimpleTypeInterface(const std::string &name, const eSimpleType type = eSimpleType::tStringType, const eWhiteSpace whitSpace = eWhiteSpace::Preserve);
			ISimpleTypeInterface(const std::string &&name, const eSimpleType type = eSimpleType::tStringType, const eWhiteSpace whitSpace = eWhiteSpace::Preserve);
			ISimpleTypeInterface(const ISimpleTypeInterface &ano);
			ISimpleTypeInterface(const ISimpleTypeInterface &&ano);
			ISimpleTypeInterface &operator=(const ISimpleTypeInterface &rhs);
			ISimpleTypeInterface &operator=(const ISimpleTypeInterface &&rhs);
			virtual ~ISimpleTypeInterface(void);

			virtual void refreshValidator(const boost::property_tree::ptree &root) = 0;

			inline void setName(const std::string &name) { m_name.assign(name); }
			inline void setName(const std::string &&name) { m_name.assign(std::move(name)); }
			inline const std::string &getName(void) const { return m_name; }

			inline void setType(const eSimpleType type) { m_type = type; }
			inline const eSimpleType type(void) const { return m_type; }

			inline void setWhiteSpace(const eWhiteSpace whiteSpace) { m_whiteSpace = whiteSpace; }
			inline const eWhiteSpace getWhiteSpace(void) const { return m_whiteSpace; }

			inline void setBaseTypeName(const std::string &baseTypeName) { m_baseTypeName.assign(baseTypeName); }
			inline const std::string &getBaseTypeName(void) const { return m_baseTypeName; }

			inline void setDescription(const std::string &description) { m_description.assign(description); }
			inline void setDescription(const std::string &&description) { m_description.assign(std::move(description)); }
			inline const std::string &getDescription(void) const { return m_description; }

		private:
			std::string m_name;
			eSimpleType m_type;
			eWhiteSpace m_whiteSpace;

			std::string m_baseTypeName;
			std::string m_description;
		};
	}
};
