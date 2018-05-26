#include "stdafx.h"
#include "CARSDKGlobal.h"

namespace CARSDK
{
#define String_Definition(name, str)\
		const std::string &##name##(void)\
		{\
			static const std::string ret = std::string(str);\
			return ret;\
		}\

	const std::string EDMUtilsFactoryMethodName("getEDMUtilsInterface");
	const std::string EAUtilsFactoryMethodName("getEAUtilsInterface");

	String_Definition(UnitAttr, "unit");
	String_Definition(DigitAttr, "digit");

	String_Definition(ExperimentalFactorTypeAttr, "experimental_factor_type");
	const boost::bimap<ExperimentalFactorType, std::string> &ExperimentalFactorType2String(void)
	{
		static const boost::bimap<ExperimentalFactorType, std::string> ret = 
			[]()
		{
			typedef boost::bimap<ExperimentalFactorType, std::string> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(ExperimentalFactorType::ExperimentalFactor, std::string("ExperimentalFactor")));
			ret.insert(pair_type(ExperimentalFactorType::EvaluateFactor, std::string("EvaluateFactor")));
			ret.insert(pair_type(ExperimentalFactorType::NotEvaluateFactor, std::string("NotEvaluateFactor")));
			return ret;
		}();
		return ret;
	}

	const boost::bimap<ExperimentalFactorType, std::string>& ExperimentalFactorType2Display(void)
	{
		static const boost::bimap<ExperimentalFactorType, std::string> ret =
			[]()
		{
			typedef boost::bimap<ExperimentalFactorType, std::string> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(ExperimentalFactorType::ExperimentalFactor, std::string("ʵ������")));
			ret.insert(pair_type(ExperimentalFactorType::EvaluateFactor, std::string("ָ������")));
			ret.insert(pair_type(ExperimentalFactorType::NotEvaluateFactor, std::string("��ָ������")));
			return ret;
		}();
		return ret;
	}

#undef String_Definition
};
