#pragma once

#include "SimpleTypeInterface.h"
#include "DataUtils.h"

#include <map>
#include <set>
#include <functional>

namespace XSDFrontend
{
	namespace SimpleType
	{
		inline const bool ValueEnumrationConfiguration<DataUtils::Data>::_ValueTypeCompare::operator()(const DataUtils::Data & lhs, const DataUtils::Data & rhs) const
		{
			for (DataUtils::Data::const_iterator lCurrIt(lhs.cbegin()), rCurrIt(rhs.cbegin()), lEdIt(lhs.cend()), rEdIt(rhs.cend()); lCurrIt != lEdIt && rCurrIt != rEdIt; ++lCurrIt, ++rCurrIt)
			{
				if (*lCurrIt < *rCurrIt)
				{
					return true;
				}
			}

			return false;
		}

		class DataType final : public ISimpleTypeInterface, 
			public LengthLimitConfiguration, 
			public ValueEnumrationConfiguration<DataUtils::Data>
		{
		public:
			enum class eBaseType
			{
				tHexBinary,
				tBase64Binary
			};
			static const int NoLengthValidator = -1;

		public:
			DataType(void);
			DataType(const std::string &name, const eBaseType baseType = eBaseType::tBase64Binary);
			DataType(std::string &&name, const eBaseType baseType = eBaseType::tBase64Binary);
			DataType(const DataType &ano) = default;
			DataType(DataType &&ano) = default;
			DataType &operator=(const DataType &rhs) = default;
			DataType &operator=(DataType &&rhs) = default;
			~DataType(void) = default;

			void refreshValidator(const XMLUtils::XMLNode &node) override;

			inline void setBaseType(const eBaseType baseType) { m_baseType = baseType; }
			inline const eBaseType getBaseType(void) const { return m_baseType; }

		private:
			eBaseType m_baseType;
		};

		static const std::map<std::string, DataType::eBaseType> DataBaseTypeName2Type =
		{
			std::make_pair(std::string("hexBinary"), DataType::eBaseType::tHexBinary),
			std::make_pair(std::string("base64Binary"), DataType::eBaseType::tBase64Binary)
		};
	};
};
