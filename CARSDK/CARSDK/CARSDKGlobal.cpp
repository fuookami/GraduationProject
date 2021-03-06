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
	String_Definition(DigitAttr, "digits");

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
			ret.insert(pair_type(ExperimentalFactorType::ExperimentalFactor, std::string("实验因素")));
			ret.insert(pair_type(ExperimentalFactorType::EvaluateFactor, std::string("指标因素")));
			ret.insert(pair_type(ExperimentalFactorType::NotEvaluateFactor, std::string("非指标因素")));
			return ret;
		}();
		return ret;
	}

	const boost::bimap<AnalysisResultType, std::string> &AnalysisResultType2String(void)
	{
		static const boost::bimap<AnalysisResultType, std::string> ret = 
			[]()
		{
			typedef boost::bimap<AnalysisResultType, std::string> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(AnalysisResultType::Raw, std::string("Raw")));
			ret.insert(pair_type(AnalysisResultType::Table, std::string("Table")));
			ret.insert(pair_type(AnalysisResultType::Html5, std::string("Html5")));
			ret.insert(pair_type(AnalysisResultType::None, std::string("None")));
			return ret;
		}();
		return ret;
	}

	const boost::bimap<AttributeType, std::string> &AttributeType2String(void)
	{
		static const boost::bimap<AttributeType, std::string> ret = 
			[]()
		{
			typedef boost::bimap<AttributeType, std::string> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(AttributeType::Boolean, std::string("Boolean")));
			ret.insert(pair_type(AttributeType::Number, std::string("Number")));
			ret.insert(pair_type(AttributeType::String, std::string("String")));
			return ret;
		}();
		return ret;
	}

	std::reference_wrapper<const FactorType> FactorTypeGroup::getFactorType(const std::string & name) const
	{
		auto it(std::find_if(experimentalFactors.begin(), experimentalFactors.end(), [&name](const std::reference_wrapper<const FactorType> wrapper) 
		{
			return wrapper.get().name == name;
		}));
		if (it != experimentalFactors.end())
		{
			return *it;
		}

		it = std::find_if(evaluateFactor.begin(), evaluateFactor.end(), [&name](const std::reference_wrapper<const FactorType> wrapper)
		{
			return wrapper.get().name == name;
		});
		if (it != evaluateFactor.end())
		{
			return *it;
		}

		return *std::find_if(notEvaluateFactor.begin(), notEvaluateFactor.end(), [&name](const std::reference_wrapper<const FactorType> wrapper)
		{
			return wrapper.get().name == name;
		});
	}

	std::vector<std::reference_wrapper<const FactorType>> FactorTypeGroup::factors(void) const
	{
		std::vector<std::reference_wrapper<const FactorType>> ret;
		ret.insert(ret.end(), experimentalFactors.cbegin(), experimentalFactors.cend());
		ret.insert(ret.end(), evaluateFactor.cbegin(), evaluateFactor.cend());
		ret.insert(ret.end(), notEvaluateFactor.cbegin(), notEvaluateFactor.cend());
		return ret;
	}

#undef String_Definition
};
