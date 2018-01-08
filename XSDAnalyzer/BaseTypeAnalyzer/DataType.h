#pragma once

#include "SimpleTypeInterface.h"
#include "DataUtils.h"

#include <map>
#include <set>
#include <functional>

namespace XSDAnalyzer
{
	namespace SimpleType
	{
		class DataType final : public ISimpleTypeInterface
		{
		public:
			enum class eBaseType
			{
				tHexBinary,
				tBase64Binary
			};
			static const int NoLengthValidator = -1;
			using ValueType = DataUtils::Data;
			
		private:
			struct _ValueTypeCompare
			{
				const bool operator()(const ValueType& lhs, const ValueType& rhs) const;
			};

		public:
			DataType(void);
			DataType(const std::string &name, const eBaseType baseType = eBaseType::tBase64Binary);
			DataType(const std::string &&name, const eBaseType baseType = eBaseType::tBase64Binary);
			DataType(const DataType &ano);
			DataType(const DataType &&ano);
			DataType &operator=(const DataType &rhs);
			DataType &operator=(const DataType &&rhs);
			~DataType(void);

			void refreshValidator(const boost::property_tree::ptree &root) override;

			inline void setBaseType(const eBaseType baseType) { m_baseType = baseType; }
			inline const eBaseType getBaseType(void) const { return m_baseType; }

			inline void setLengthValidator(const int lenth) { m_minLength = m_maxLength = lenth; }
			inline void removeLengthValidator(void) { setLengthValidator(NoLengthValidator); }
			inline const int getLengthValidator(void) const { return m_minLength == m_maxLength ? m_minLength : NoLengthValidator; }

			inline void setMinLengthValidator(const int minLength) { m_minLength = minLength; }
			inline void removeMinLengthValidator(void) { setMinLengthValidator(NoLengthValidator); }
			inline const int getMinLengthValidator(void) const { return m_minLength; }

			inline void setMaxLengthValidator(const int maxLength) { m_maxLength = maxLength; }
			inline void removeMaxLengthValidator(void) { setMaxLengthValidator(NoLengthValidator); }
			inline const int getMaxLengthValidator(void) const { return m_maxLength; }

			inline void setIsEnum(const bool isEnum) { m_isEnum = isEnum; }
			inline const bool getIsEnum(void) const { return m_isEnum; }

			inline void addEnumValue(const ValueType &enumValue) { m_enumValues.insert(enumValue); }
			inline void addEnumValue(const ValueType &&enumValue) { m_enumValues.insert(std::move(enumValue)); }
			inline void eraseEnumValue(const ValueType &enumValue) { m_enumValues.erase(enumValue); }
			inline void clearEnumValue(void) { m_enumValues.clear(); }
			inline const bool hasEnumValue(const ValueType &enumValue) const { return m_enumValues.find(enumValue) != m_enumValues.cend(); }
			inline const std::set<ValueType, _ValueTypeCompare> &getEnumValues(void) const { return m_enumValues; }

		private:
			eBaseType m_baseType;

			int m_minLength;
			int m_maxLength;

			bool m_isEnum;
			std::set<ValueType, _ValueTypeCompare> m_enumValues;
		};

		static const std::map<std::string, DataType::eBaseType> DataBaseTypeName2Type =
		{
			std::make_pair(std::string("hexBinary"), DataType::eBaseType::tHexBinary),
			std::make_pair(std::string("base64Binary"), DataType::eBaseType::tBase64Binary)
		};
	};
};
