#include "stdafx.h"
#include "ExperimentalDesignTable.h"

namespace CARSDK
{
	const std::string ExperimentalDesignTable::Tag("experimental_design_table");
	const std::string ExperimentalDesignTable::BatchTag("batch");
	const std::string ExperimentalDesignTable::CellTag("cell");
	const std::string ExperimentalDesignTable::NameAttr("name");

	ExperimentalDesignTable::ExperimentalDesignTable(const std::shared_ptr<SSUtils::XML::Node> node, const FactorTypeGroup &group)
		: ExperimentalDesignTable(fromXML(node, group))
	{
	}

	const bool ExperimentalDesignTable::valid(const std::shared_ptr<XSDFrontend::XSDModel> model) const
	{
		if (!checkTableStruct())
		{
			return false;
		}

		return true;
	}

	ExperimentalDesignTable ExperimentalDesignTable::fromXML(const std::shared_ptr<SSUtils::XML::Node> node, const FactorTypeGroup &group)
	{
		if (!checkXMLStruct(node, group))
		{
			return ExperimentalDesignTable();
		}

		ExperimentalDesignTable ret;
		auto factorInserter = [&ret](const decltype(group.experimentalFactors) &factorWrappers)
		{
			for (const auto factorWrapper : factorWrappers)
			{
				ret.m_typeNames.push_back(factorWrapper.get().name);
			}
		};
		factorInserter(group.experimentalFactors);
		factorInserter(group.evaluateFactor);
		factorInserter(group.notEvaluateFactor);
		for (const auto factorWrapper : group.experimentalFactors)
		{
			ret.m_readOnlyTypeNames.insert(factorWrapper.get().name);
		}

		for (const auto batchNode : node->getChildren())
		{
			Batch batch;

			for (const auto factorNode : batchNode->getChildren())
			{
				Cell cell;
				cell.content.assign(factorNode->getContent());
				cell.attrs = factorNode->getAttrs();
				cell.attrs.erase(NameAttr);

				batch.push_back(std::move(cell));
			}

			ret.m_batches.push_back(std::move(batch));
		}

		return ret;
	}

	std::shared_ptr<SSUtils::XML::Node> ExperimentalDesignTable::toXML(const FactorTypeGroup &group) const
	{
		if (!checkTableStruct(group))
		{
			return nullptr;
		}

		auto node(SSUtils::XML::Node::generate(Tag));

		for (const auto &batch : m_batches)
		{
			auto batchNode(SSUtils::XML::Node::generate(BatchTag));

			for (int i(0), j(m_typeNames.size()); i != j; ++i)
			{
				auto cellNode(SSUtils::XML::Node::generate(CellTag));
				cellNode->setContent(normalizeContent(batch[i].content, group.getFactorType(m_typeNames[i])));
				cellNode->getAttrs() = batch[i].attrs;
				cellNode->addAttr(NameAttr, m_typeNames[i]);

				batchNode->addChild(cellNode);
			}

			node->addChild(batchNode);
		}

		return node;
	}

	const bool ExperimentalDesignTable::checkXMLStruct(const std::shared_ptr<SSUtils::XML::Node> node, const FactorTypeGroup &group)
	{
		static const auto getFactorNames([](const FactorTypeGroup &group) 
		{
			const auto factors = group.factors();
			std::vector<std::string> names;
			for (const auto &factor : factors)
			{
				names.push_back(factor.get().name);
			}
			return names;
		});
		static const auto checkFactors([](const std::shared_ptr<SSUtils::XML::Node> node, const std::vector<std::string> &factors) -> const bool
		{
			for (const auto batchNode : node->getChildren())
			{
				std::vector<std::string> thisFactors;
				for (const auto factorNode : batchNode->getChildren())
				{
					if (factorNode->getTag() != CellTag)
					{
						return false;
					}
					thisFactors.push_back(factorNode->getAttr(NameAttr));
				}

				if (factors != thisFactors)
				{
					return false;
				}
			}

			return true;
		});

		if (node->getTag() != Tag)
		{
			return false;
		}

		for (const auto batchNode : node->getChildren())
		{
			if (batchNode->getTag() != BatchTag)
			{
				return false;
			}
		}

		if (group.empty())
		{
			std::vector<std::string> originFactors;
			const auto firstBatchNode(node->getChildren().front());
			for (const auto factorNode : firstBatchNode->getChildren())
			{
				originFactors.push_back(factorNode->getAttr(NameAttr));
			}

			if (!checkFactors(node, originFactors))
			{
				return false;
			}
		}
		else
		{
			if (!checkFactors(node, getFactorNames(group)))
			{
				return false;
			}
		}

		return true;
	}

	const bool ExperimentalDesignTable::checkTableStruct(const FactorTypeGroup &group) const
	{
		static const auto getFactorNames([](const FactorTypeGroup &group)
		{
			const auto factors = group.factors();
			std::vector<std::string> names;
			for (const auto &factor : factors)
			{
				names.push_back(factor.get().name);
			}
			return names;
		});

		if (!group.empty() && m_typeNames != getFactorNames(group))
		{
			return false;
		}

		const int factorNumber = m_typeNames.size();
		for (const auto &batch : m_batches)
		{
			if (batch.size() != factorNumber)
			{
				return false;
			}
		}

		return true;
	}

	std::string ExperimentalDesignTable::normalizeContent(const std::string & content, const FactorType & factor)
	{
		if (content.empty())
		{
			return content;
		}

		if (factor.simpleType == XSDFrontend::SimpleType::eSimpleType::tNumberType)
		{
			SSUtils::Math::Real value(content);

			auto digitIt(factor.attributes.find(DigitAttr()));
			if (digitIt == factor.attributes.cend())
			{
				return value.toString();
			}
			else
			{
				SSUtils::uint32 digits = SSUtils::Math::DefaultDigits;
				if (digitIt != factor.attributes.cend() && SSUtils::String::isPositiveDecInteger(digitIt->second))
				{
					digits = std::stoul(digitIt->second);
				}
				return value.toDecimal().second.str(digits, std::ios::fixed);
			}
		}
		else if (factor.simpleType == XSDFrontend::SimpleType::eSimpleType::tStringType)
		{
			return content;
		}
		else if (factor.simpleType == XSDFrontend::SimpleType::eSimpleType::tDatetimeType)
		{
			return SSUtils::Datetime::DatetimeDuration::fromString(content).toString();
		}
		
		return std::string("");
	}
};
