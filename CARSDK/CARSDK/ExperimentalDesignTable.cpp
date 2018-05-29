#include "stdafx.h"
#include "ExperimentalDesignTable.h"

namespace CARSDK
{
	const std::string ExperimentalDesignTable::Tag("experimental_design_table");
	const std::string ExperimentalDesignTable::BatchTag("batch");

	ExperimentalDesignTable::ExperimentalDesignTable(const std::shared_ptr<SSUtils::XML::Node> node, const std::set<std::string> &factors)
		: ExperimentalDesignTable(fromXML(node, factors))
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

	ExperimentalDesignTable ExperimentalDesignTable::fromXML(const std::shared_ptr<SSUtils::XML::Node> node, const std::set<std::string> &factors)
	{
		if (!checkXMLStruct(node, factors))
		{
			return ExperimentalDesignTable();
		}

		ExperimentalDesignTable ret;
		std::copy(factors.cbegin(), factors.cend(), std::back_inserter(ret.m_typeNames));

		for (const auto batchNode : node->getChildren())
		{
			Batch batch;

			for (const auto factorNode : batchNode->getChildren())
			{
				Cell cell;
				cell.content.assign(factorNode->getContent());
				cell.attrs = factorNode->getAttrs();

				batch.push_back(std::move(cell));
			}

			ret.m_batches.push_back(std::move(batch));
		}

		return ret;
	}

	std::shared_ptr<SSUtils::XML::Node> ExperimentalDesignTable::toXML(void) const
	{
		if (!checkTableStruct())
		{
			return nullptr;
		}

		auto node(SSUtils::XML::Node::generate(Tag));

		for (const auto &batch : m_batches)
		{
			auto batchNode(SSUtils::XML::Node::generate(BatchTag));

			for (int i(0), j(m_typeNames.size()); i != j; ++i)
			{
				auto cellNode(SSUtils::XML::Node::generate(m_typeNames[i]));
				cellNode->setContent(batch[i].content);
				cellNode->getAttrs() = batch[i].attrs;

				batchNode->addChild(cellNode);
			}

			node->addChild(batchNode);
		}

		return node;
	}

	const bool ExperimentalDesignTable::checkXMLStruct(const std::shared_ptr<SSUtils::XML::Node> node, const std::set<std::string> &factors)
	{
		static const auto checkFactors([](const std::shared_ptr<SSUtils::XML::Node> node, const std::set<std::string> &factors) -> const bool
		{
			for (const auto batchNode : node->getChildren())
			{
				std::set<std::string> thisFactors;
				for (const auto factorNode : batchNode->getChildren())
				{
					thisFactors.insert(factorNode->getTag());
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

		if (factors.empty())
		{
			std::set<std::string> originFactors;
			const auto firstBatchNode(node->getChildren().front());
			for (const auto factorNode : firstBatchNode->getChildren())
			{
				originFactors.insert(factorNode->getTag());
			}

			if (!checkFactors(node, originFactors))
			{
				return false;
			}
		}
		else
		{
			if (!checkFactors(node, factors))
			{
				return false;
			}
		}

		return true;
	}

	const bool ExperimentalDesignTable::checkTableStruct(void) const
	{
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
};
