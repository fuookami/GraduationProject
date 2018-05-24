#pragma once

#include "SimpleTypeInterface.h"
#include "SSUtils\DataUtils.h"

#include <map>
#include <set>
#include <functional>
#include <boost/bimap.hpp>

namespace XSDFrontend
{
	namespace SimpleType
	{
		inline const bool ValueEnumrationConfiguration<SSUtils::Block>::_ValueTypeCompare::operator()(const SSUtils::Block & lhs, const SSUtils::Block & rhs) const
		{
			for (SSUtils::Block::const_iterator lCurrIt(lhs.cbegin()), rCurrIt(rhs.cbegin()), lEdIt(lhs.cend()), rEdIt(rhs.cend()); lCurrIt != lEdIt && rCurrIt != rEdIt; ++lCurrIt, ++rCurrIt)
			{
				if (*lCurrIt < *rCurrIt)
				{
					return true;
				}
			}

			return false;
		}

		class SSXSDUtils_API_DECLSPEC DataType final : public ISimpleTypeInterface,
			public LengthLimitConfiguration, 
			public ValueEnumrationConfiguration<SSUtils::Block>
		{
		public:
			enum class eBaseType
			{
				tHexBinary,
				tBase64Binary,
				tRaw
			};
			static const int NoLengthValidator = -1;
			static const boost::bimap<std::string, eBaseType> String2Type;

		public:
			DataType(void);
			DataType(const std::string &name, const eBaseType baseType = eBaseType::tRaw);
			DataType(std::string &&name, const eBaseType baseType = eBaseType::tRaw);
			DataType(const DataType &ano) = default;
			DataType(DataType &&ano) = default;
			DataType &operator=(const DataType &rhs) = default;
			DataType &operator=(DataType &&rhs) = default;
			~DataType(void) = default;

			const bool refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node) override;
			std::shared_ptr<SSUtils::XML::Node> saveValidator(const std::shared_ptr<SSUtils::XML::Node> root) const override;

			void setBaseType(const eBaseType baseType);
			inline const eBaseType getBaseType(void) const { return m_baseType; }

		private:
			eBaseType m_baseType;
		};

		SSXSDUtils_API_DECLSPEC SSUtils::Block XSDString2Data(const DataType::eBaseType type, const std::string & str);
		SSXSDUtils_API_DECLSPEC std::string XSDData2String(const DataType::eBaseType type, const SSUtils::Block & value);
	};
};
