#include "stdafx.h"
#include "TwoFactorsAEDM.h"
#include "SSUtils\MathUtils.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace AEDM
{
	const std::string TwoFactorsAEDM::Category("TwoFactorAEDM");
	const std::string TwoFactorsAEDM::DisplayName("二因子析因设计方法");
	const std::string TwoFactorsAEDM::RepeatTimeAttr("repeat_time");
	const std::string TwoFactorsAEDM::InteractionEffectAttr("has_interaction_effect");

	boost::shared_ptr<TwoFactorsAEDM> TwoFactorsAEDM::create(void)
	{
		return boost::shared_ptr<TwoFactorsAEDM>(new TwoFactorsAEDM());
	}

	const std::string &TwoFactorsAEDM::category(void) const
	{
		return Category;
	}

	const std::string &TwoFactorsAEDM::displayName(void) const
	{
		return DisplayName;
	}

	const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> &TwoFactorsAEDM::neededAttributes(void) const
	{
		static const std::vector<std::pair<std::string, std::pair<std::string, CARSDK::AttributeType>>> ret = 
		{
			std::make_pair(InteractionEffectAttr, std::make_pair(std::string("交互作用"), CARSDK::AttributeType::Boolean)),
			std::make_pair(RepeatTimeAttr, std::make_pair(std::string("重复次数"), CARSDK::AttributeType::Number))
		};
		return ret;
	}

	const std::map<std::string, std::string>& TwoFactorsAEDM::factorNeededAttributes(void) const
	{
		static const std::map<std::string, std::string> ret = DefaultFactorAttributes;
		return ret;
	}

	const bool TwoFactorsAEDM::valid(const std::map<std::string, std::string>& attributes)
	{
		if (!SSUtils::String::isPositiveDecInteger(attributes.find(RepeatTimeAttr)->second))
		{
			m_lastError.assign("重复次数不是一个有效的十进制正整数");
			return false;
		}

		return true;
	}

	const bool TwoFactorsAEDM::valid(const std::map<std::string, std::string>& attributes, const CARSDK::FactorTypeGroup & factorTypeGroup)
	{
		if (!valid(attributes))
		{
			return false;
		}

		if (factorTypeGroup.experimentalFactors.size() != 2)
		{
			m_lastError.assign("实验因素类型的数量不为2");
			return false;
		}

		std::vector<std::string> NoEnumFactors;
		for (const auto &factorWrapper : factorTypeGroup.experimentalFactors)
		{
			const auto &factor = factorWrapper.get();
			if (CARSDK::DataModelingModule::getEnumNumber(factor) <= 0)
			{
				NoEnumFactors.push_back(factor.name);
			}
		}
		if (!NoEnumFactors.empty())
		{
			std::ostringstream sout;
			sout << "实验因素" << SSUtils::String::join(NoEnumFactors, std::string("，")) << "没有水平值";
			m_lastError.assign(sout.str());
			return false;
		}

		return true;
	}

	CARSDK::ExperimentalDesignTable TwoFactorsAEDM::generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel>& xsdModel, const std::map<std::string, std::string>& attributes)
	{
		auto modelingModule(CARSDK::DataModelingModule::instance());
		auto infos(modelingModule->analyzeForData(xsdModel));
		auto group(CARSDK::DataModelingModule::divideToGroup(infos));

		if (!valid(attributes, group))
		{
			return CARSDK::ExperimentalDesignTable();
		}
		
		CARSDK::ExperimentalDesignTable table;
		auto factorInserter = [&table](const decltype(group.experimentalFactors) &factorWrappers) 
		{
			for (const auto factorWrapper : factorWrappers)
			{
				table.typeNames().push_back(factorWrapper.get().name);
			}
		};
		factorInserter(group.experimentalFactors);
		factorInserter(group.evaluateFactor);
		factorInserter(group.notEvaluateFactor);
		for (const auto factorWrapper : group.experimentalFactors)
		{
			table.readOnlyTypeNames().insert(factorWrapper.get().name);
		}

		SSUtils::uint32 repeatTime = std::stoul(attributes.find(RepeatTimeAttr)->second);

		std::vector<std::vector<std::string>> enumStrings;
		std::vector<SSUtils::int32> numbers;
		for (const auto &factor : group.experimentalFactors)
		{
			enumStrings.push_back(CARSDK::DataModelingModule::getEnumString(factor));
			numbers.push_back(enumStrings.back().size());
		}
		
		SSUtils::Math::CombinationGenerator combinationGenerator(numbers);
		do 
		{
			CARSDK::ExperimentalDesignTable::Batch batch;
			const auto &combination(combinationGenerator.currCombination);
			for (SSUtils::uint32 i(0), j(combination.size()); i != j; ++i)
			{
				batch.push_back(generateCell(group.experimentalFactors[i], enumStrings[i][combination[i]]));
			}
			for (SSUtils::uint32 i(0), j(group.evaluateFactor.size()); i != j; ++i)
			{
				batch.push_back(generateCell(group.evaluateFactor[i]));
			}
			for (SSUtils::uint32 i(0), j(group.notEvaluateFactor.size()); i != j; ++i)
			{
				batch.push_back(generateCell(group.notEvaluateFactor[i]));
			}

			table.batches().insert(table.batches().end(), repeatTime, batch);
		} while (combinationGenerator.next());

		std::random_shuffle(table.batches().begin(), table.batches().end());
		return table;
	}

	CARSDK::ExperimentalDesignTable::Cell TwoFactorsAEDM::generateCell(const CARSDK::FactorType & info, const std::string & value)
	{
		return IExperimentalDesignMethodInterface::generateCell(info, value);
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::OriginAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "evaluate_" << evaluateFactorOrder << "_origin";
		displaySout << "原始（" << group.evaluateFactor[evaluateFactorOrder].get().name << "）";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(originAnalyse, std::placeholders::_1, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::VarianceOriginAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "evaluate_" << evaluateFactorOrder << "_variance_origin";
		displaySout << "方差法原始（" << group.evaluateFactor[evaluateFactorOrder].get().name << "）";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(varianceOriginAnalyse, std::placeholders::_1, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::FactorSumAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "factor_" << experimentalFactorOrder << "_evaluate_" << evaluateFactorOrder << "_sum";
		displaySout << group.experimentalFactors[experimentalFactorOrder].get().name << "-" << group.evaluateFactor[evaluateFactorOrder].get().name << "和值";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(factorSumAnalyse, std::placeholders::_1, experimentalFactorOrder, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::FactorAverageAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "factor_" << experimentalFactorOrder << "_evaluate_" << evaluateFactorOrder << "_average";
		displaySout << group.experimentalFactors[experimentalFactorOrder].get().name << "-" << group.evaluateFactor[evaluateFactorOrder].get().name << "平均值";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(factorAverageAnalyse, std::placeholders::_1, experimentalFactorOrder, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::Factor1Factor2SumAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "evaluate_" << evaluateFactorOrder << "_sum";
		displaySout << "(" << group.experimentalFactors[0].get().name << ", " << group.experimentalFactors[1].get().name << "）-" << group.evaluateFactor[evaluateFactorOrder].get().name << "和值";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(factor1Factor2SumAnalyse, std::placeholders::_1, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	std::tuple<std::string, std::string, TwoFactorsAEDMAnalyzers::Analyzer> TwoFactorsAEDMAnalyzers::Factor1Factor2AverageAnalyzer(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder)
	{
		std::ostringstream flagSout, displaySout;
		flagSout << "evaluate_" << evaluateFactorOrder << "_average";
		displaySout << "(" << group.experimentalFactors[0].get().name << ", " << group.experimentalFactors[1].get().name << "）-" << group.evaluateFactor[evaluateFactorOrder].get().name << "平均值";
		return std::make_tuple(flagSout.str(), displaySout.str(), std::bind(factor1Factor2AverageAnalyse, std::placeholders::_1, evaluateFactorOrder, std::placeholders::_2, std::placeholders::_3));
	}

	boost::shared_ptr<TwoFactorsAEDMAnalyzers> TwoFactorsAEDMAnalyzers::create(void)
	{
		return boost::shared_ptr<TwoFactorsAEDMAnalyzers>(new TwoFactorsAEDMAnalyzers());
	}

	const std::string & TwoFactorsAEDMAnalyzers::category(void) const
	{
		return TwoFactorsAEDM::Category;
	}

	const std::string & TwoFactorsAEDMAnalyzers::displayName(void) const
	{
		return TwoFactorsAEDM::DisplayName;
	}

	TwoFactorsAEDMAnalyzers::AnalyzerGroup TwoFactorsAEDMAnalyzers::generateAnalyzerGroup(const CARSDK::FactorTypeGroup &group) const
	{
		AnalyzerGroup ret;
		const auto AddAnalyzer([&ret](const std::tuple<std::string, std::string, Analyzer> &tuple) 
		{
			ret.flags.insert(std::make_pair(std::get<0>(tuple), std::get<1>(tuple)));
			ret.analyzers.insert(std::make_pair(std::get<0>(tuple), std::get<2>(tuple)));
		});

		for (SSUtils::uint32 i(0), j(group.evaluateFactor.size()); i != j; ++i)
		{
			AddAnalyzer(OriginAnalyzer(group, i));
			if (group.evaluateFactor[i].get().simpleType == XSDFrontend::SimpleType::eSimpleType::tNumberType)
			{
				AddAnalyzer(VarianceOriginAnalyzer(group, i));
				AddAnalyzer(FactorSumAnalyzer(group, 0, i));
				AddAnalyzer(FactorSumAnalyzer(group, 1, i));
				AddAnalyzer(FactorAverageAnalyzer(group, 0, i));
				AddAnalyzer(FactorAverageAnalyzer(group, 1, i));
				AddAnalyzer(Factor1Factor2SumAnalyzer(group, i));
				AddAnalyzer(Factor1Factor2AverageAnalyzer(group, i));
			}
		}

		return ret;
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::originAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		auto factor1Enum(CARSDK::DataModelingModule::getEnumString(group.experimentalFactors[0])), factor2Enum(CARSDK::DataModelingModule::getEnumString(group.experimentalFactors[1]));
		std::string factor1Unit, factor2Unit;
		if (group.experimentalFactors[0].get().attributes.find(CARSDK::UnitAttr()) != group.experimentalFactors[0].get().attributes.cend())
		{
			auto unit = group.experimentalFactors[0].get().attributes.find(CARSDK::UnitAttr())->second;
			factor1Unit = unit;
			for (auto &value : factor1Enum)
			{
				value += unit;
			}
		}
		if (group.experimentalFactors[1].get().attributes.find(CARSDK::UnitAttr()) != group.experimentalFactors[1].get().attributes.cend())
		{
			auto unit = group.experimentalFactors[1].get().attributes.find(CARSDK::UnitAttr())->second;
			factor2Unit = unit;
			for (auto &value : factor2Enum)
			{
				value += unit;
			}
		}

		std::map<std::string, std::map<std::string, std::vector<std::string>>> strings;
		for (const auto &batch : table.batches())
		{
			strings[batch[0].content + factor1Unit][batch[1].content + factor2Unit].push_back(batch[2 + evaluateFactorOrder].content);
		}

		std::ostringstream html5;
		html5 << "<table class=\"centered\"><thead><tr>";
		html5 << "<td rowspan=\"2\" class=\"center\">" << group.experimentalFactors[0].get().name << "</td>";
		html5 << "<td colspan=\"" << factor2Enum.size() << "\" class=\"center\">" << group.experimentalFactors[1].get().name << "</td>";
		html5 << "</tr><tr>";
		for (const auto &factor2 : factor2Enum)
		{
			html5 << "<td class=\"center\">" << factor2 << "</td>";
		}
		html5 << "</tr></thead><tbody>";
		for (const auto &factor1 : factor1Enum)
		{
			html5 << "<tr><td>" << factor1 << "</td>";
			for (const auto &factor2 : factor2Enum)
			{
				const auto &values = strings[factor1][factor2];
				html5 << "<td>" << SSUtils::String::join(values.cbegin(), values.cend(), std::string(", ")) << "</td>" ;
			}
		}
		html5 << "</tbody></table>";

		return std::make_pair(CARSDK::AnalysisResultType::Html5, html5.str());
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::varianceOriginAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		// to do

		return std::make_pair(CARSDK::AnalysisResultType::Raw, std::string("未实现"));
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::factorSumAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		using namespace boost::property_tree;
		auto factorEnum(CARSDK::DataModelingModule::getEnumString(group.experimentalFactors[experimentalFactorOrder]));
		std::string factorUnit;
		if (group.experimentalFactors[experimentalFactorOrder].get().attributes.find(CARSDK::UnitAttr()) != group.experimentalFactors[experimentalFactorOrder].get().attributes.cend())
		{
			auto unit = group.experimentalFactors[0].get().attributes.find(CARSDK::UnitAttr())->second;
			factorUnit = unit;
			for (auto &value : factorEnum)
			{
				value += unit;
			}
		}

		std::map<std::string, std::vector<std::string>> strings;
		for (const auto &batch : table.batches())
		{
			strings[batch[experimentalFactorOrder].content + factorUnit].push_back(batch[2 + evaluateFactorOrder].content);
		}

		SSUtils::uint32 digits = SSUtils::Math::DefaultDigits;
		auto digitIt(group.evaluateFactor[evaluateFactorOrder].get().attributes.find(CARSDK::DigitAttr()));
		if (digitIt != group.evaluateFactor[evaluateFactorOrder].get().attributes.cend() && SSUtils::String::isPositiveDecInteger(digitIt->second))
		{
			digits = std::stoul(digitIt->second);
		}
		std::map<std::string, std::string> values;
		for (const auto &row : strings)
		{
			SSUtils::dec50 thisValue(.0f);
			for (const auto &value : row.second)
			{
				thisValue += SSUtils::dec50(value);
			}
			values[row.first] = thisValue.str(digits, std::ios::fixed);
		}

		ptree json, xCategories, datas;
		for (const auto &factor1 : factorEnum)
		{
			ptree value;
			value.put(std::string(""), factor1);
			xCategories.push_back(std::make_pair(std::string(""), value));
		}
		for (SSUtils::uint32 i(0), j(factorEnum.size()); i != j; ++i)
		{
			ptree data, x, value;
			x.put(std::string(""), i);
			value.put(std::string(""), values[factorEnum[i]]);
			data.push_back(std::make_pair(std::string(""), x));
			data.push_back(std::make_pair(std::string(""), value));
			datas.push_back(std::make_pair(std::string(""), data));
		}

		json.push_back(std::make_pair(std::string("xCategories"), xCategories));
		json.push_back(std::make_pair(std::string("datas"), datas));
		std::ostringstream sout;
		write_json(sout, json);
		return std::make_pair(CARSDK::AnalysisResultType::Table, sout.str());
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::factorAverageAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 experimentalFactorOrder, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		using namespace boost::property_tree;
		auto factorEnum(CARSDK::DataModelingModule::getEnumString(group.experimentalFactors[experimentalFactorOrder]));
		std::string factorUnit;
		if (group.experimentalFactors[experimentalFactorOrder].get().attributes.find(CARSDK::UnitAttr()) != group.experimentalFactors[experimentalFactorOrder].get().attributes.cend())
		{
			auto unit = group.experimentalFactors[0].get().attributes.find(CARSDK::UnitAttr())->second;
			factorUnit = unit;
			for (auto &value : factorEnum)
			{
				value += unit;
			}
		}

		std::map<std::string, std::vector<std::string>> strings;
		for (const auto &batch : table.batches())
		{
			strings[batch[experimentalFactorOrder].content + factorUnit].push_back(batch[2 + evaluateFactorOrder].content);
		}

		SSUtils::uint32 digits = SSUtils::Math::DefaultDigits;
		auto digitIt(group.evaluateFactor[evaluateFactorOrder].get().attributes.find(CARSDK::DigitAttr()));
		if (digitIt != group.evaluateFactor[evaluateFactorOrder].get().attributes.cend() && SSUtils::String::isPositiveDecInteger(digitIt->second))
		{
			digits = std::stoul(digitIt->second);
		}
		std::map<std::string, std::string> values;
		for (const auto &row : strings)
		{
			SSUtils::dec50 thisValue(.0f);
			for (const auto &value : row.second)
			{
				thisValue += SSUtils::dec50(value);
			}
			thisValue /= row.second.size();
			values[row.first] = thisValue.str(digits, std::ios::fixed);
		}

		ptree json, xCategories, datas;
		for (const auto &factor1 : factorEnum)
		{
			ptree value;
			value.put(std::string(""), factor1);
			xCategories.push_back(std::make_pair(std::string(""), value));
		}
		for (SSUtils::uint32 i(0), j(factorEnum.size()); i != j; ++i)
		{
			ptree data, x, value;
			x.put(std::string(""), i);
			value.put(std::string(""), values[factorEnum[i]]);
			data.push_back(std::make_pair(std::string(""), x));
			data.push_back(std::make_pair(std::string(""), value));
			datas.push_back(std::make_pair(std::string(""), data));
		}

		json.push_back(std::make_pair(std::string("xCategories"), xCategories));
		json.push_back(std::make_pair(std::string("datas"), datas));
		std::ostringstream sout;
		write_json(sout, json);
		return std::make_pair(CARSDK::AnalysisResultType::Table, sout.str());
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::factor1Factor2SumAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		using namespace boost::property_tree;

		auto factor1Enum(CARSDK::DataModelingModule::getEnumString(group.experimentalFactors[0])), factor2Enum(CARSDK::DataModelingModule::getEnumString(group.experimentalFactors[1]));
		std::string factor1Unit, factor2Unit;
		if (group.experimentalFactors[0].get().attributes.find(CARSDK::UnitAttr()) != group.experimentalFactors[0].get().attributes.cend())
		{
			auto unit = group.experimentalFactors[0].get().attributes.find(CARSDK::UnitAttr())->second;
			factor1Unit = unit;
			for (auto &value : factor1Enum)
			{
				value += unit;
			}
		}
		if (group.experimentalFactors[1].get().attributes.find(CARSDK::UnitAttr()) != group.experimentalFactors[1].get().attributes.cend())
		{
			auto unit = group.experimentalFactors[1].get().attributes.find(CARSDK::UnitAttr())->second;
			factor2Unit = unit;
			for (auto &value : factor2Enum)
			{
				value += unit;
			}
		}

		std::map<std::string, std::map<std::string, std::vector<std::string>>> strings;
		for (const auto &batch : table.batches())
		{
			strings[batch[0].content + factor1Unit][batch[1].content + factor2Unit].push_back(batch[2 + evaluateFactorOrder].content);
		}

		SSUtils::uint32 digits = SSUtils::Math::DefaultDigits;
		auto digitIt(group.evaluateFactor[evaluateFactorOrder].get().attributes.find(CARSDK::DigitAttr()));
		if (digitIt != group.evaluateFactor[evaluateFactorOrder].get().attributes.cend() && SSUtils::String::isPositiveDecInteger(digitIt->second))
		{
			digits = std::stoul(digitIt->second);
		}
		std::map<std::string, std::map<std::string, std::string>> values;
		for (const auto &row : strings)
		{
			for (const auto &column : row.second)
			{
				SSUtils::dec50 thisValue(.0f);
				for (const auto &value : column.second)
				{
					thisValue += SSUtils::dec50(value);
				}
				values[row.first][column.first] = thisValue.str(digits, std::ios::fixed);
			}
		}

		ptree json, xCategories, yCategories, datas;
		for (const auto &factor1 : factor1Enum)
		{
			ptree value;
			value.put(std::string(""), factor1);
			xCategories.push_back(std::make_pair(std::string(""), value));
		}
		for (const auto &factor2 : factor2Enum)
		{
			ptree value;
			value.put(std::string(""), factor2);
			yCategories.push_back(std::make_pair(std::string(""), value));
		}
		for (SSUtils::uint32 i(0), j(factor1Enum.size()); i != j; ++i)
		{
			for (SSUtils::uint32 p(0), q(factor2Enum.size()); p != q; ++p)
			{
				ptree data, x, y, value;
				x.put(std::string(""), i);
				y.put(std::string(""), p);
				value.put(std::string(""), values[factor1Enum[i]][factor2Enum[p]]);
				data.push_back(std::make_pair(std::string(""), x));
				data.push_back(std::make_pair(std::string(""), y));
				data.push_back(std::make_pair(std::string(""), value));
				datas.push_back(std::make_pair(std::string(""), data));
			}
		}

		json.push_back(std::make_pair(std::string("xCategories"), xCategories));
		json.push_back(std::make_pair(std::string("yCategories"), yCategories));
		json.push_back(std::make_pair(std::string("datas"), datas));
		std::ostringstream sout;
		write_json(sout, json);
		return std::make_pair(CARSDK::AnalysisResultType::Table, sout.str());
	}

	const std::pair<CARSDK::AnalysisResultType, std::string> TwoFactorsAEDMAnalyzers::factor1Factor2AverageAnalyse(const CARSDK::FactorTypeGroup & group, const SSUtils::uint32 evaluateFactorOrder, const CARSDK::ExperimentalDesignTable & table, const std::map<std::string, std::string>& attributes)
	{
		using namespace boost::property_tree;

		auto factor1Enum(CARSDK::DataModelingModule::getEnumString(group.experimentalFactors[0])), factor2Enum(CARSDK::DataModelingModule::getEnumString(group.experimentalFactors[1]));
		std::string factor1Unit, factor2Unit;
		if (group.experimentalFactors[0].get().attributes.find(CARSDK::UnitAttr()) != group.experimentalFactors[0].get().attributes.cend())
		{
			auto unit = group.experimentalFactors[0].get().attributes.find(CARSDK::UnitAttr())->second;
			factor1Unit = unit;
			for (auto &value : factor1Enum)
			{
				value += unit;
			}
		}
		if (group.experimentalFactors[1].get().attributes.find(CARSDK::UnitAttr()) != group.experimentalFactors[1].get().attributes.cend())
		{
			auto unit = group.experimentalFactors[1].get().attributes.find(CARSDK::UnitAttr())->second;
			factor2Unit = unit;
			for (auto &value : factor2Enum)
			{
				value += unit;
			}
		}

		std::map<std::string, std::map<std::string, std::vector<std::string>>> strings;
		for (const auto &batch : table.batches())
		{
			strings[batch[0].content + factor1Unit][batch[1].content + factor2Unit].push_back(batch[2 + evaluateFactorOrder].content);
		}

		SSUtils::uint32 digits = SSUtils::Math::DefaultDigits;
		auto digitIt(group.evaluateFactor[evaluateFactorOrder].get().attributes.find(CARSDK::DigitAttr()));
		if (digitIt != group.evaluateFactor[evaluateFactorOrder].get().attributes.cend() && SSUtils::String::isPositiveDecInteger(digitIt->second))
		{
			digits = std::stoul(digitIt->second);
		}
		std::map<std::string, std::map<std::string, std::string>> values;
		for (const auto &row : strings)
		{
			for (const auto &column : row.second)
			{
				SSUtils::dec50 thisValue(.0f);
				for (const auto &value : column.second)
				{
					thisValue += SSUtils::dec50(value);
				}
				thisValue /= column.second.size();
				values[row.first][column.first] = thisValue.str(digits, std::ios::fixed);
			}
		}

		ptree json, xCategories, yCategories, datas;
		for (const auto &factor1 : factor1Enum)
		{
			ptree value;
			value.put(std::string(""), factor1);
			xCategories.push_back(std::make_pair(std::string(""), value));
		}
		for (const auto &factor2 : factor2Enum)
		{
			ptree value;
			value.put(std::string(""), factor2);
			yCategories.push_back(std::make_pair(std::string(""), value));
		}
		for (SSUtils::uint32 i(0), j(factor1Enum.size()); i != j; ++i)
		{
			for (SSUtils::uint32 p(0), q(factor2Enum.size()); p != q; ++p)
			{
				ptree data, x, y, value;
				x.put(std::string(""), i);
				y.put(std::string(""), p);
				value.put(std::string(""), values[factor1Enum[i]][factor2Enum[p]]);
				data.push_back(std::make_pair(std::string(""), x));
				data.push_back(std::make_pair(std::string(""), y));
				data.push_back(std::make_pair(std::string(""), value));
				datas.push_back(std::make_pair(std::string(""), data));
			}
		}

		json.push_back(std::make_pair(std::string("xCategories"), xCategories));
		json.push_back(std::make_pair(std::string("yCategories"), yCategories));
		json.push_back(std::make_pair(std::string("datas"), datas));
		std::ostringstream sout;
		write_json(sout, json);
		return std::make_pair(CARSDK::AnalysisResultType::Table, sout.str());
	}
};
