#pragma once

#include "CARSDKGlobal.h"
#include "SSUtils/XSD/XSDModel.h"
#include "SSUtils/XMLUtils.h"

namespace CARSDK
{
	class CARSDK_API_DECLSPEC ExperimentalDesignTable
	{
	public:
		static const std::string Tag;
		static const std::string BatchTag;
		struct Cell
		{
			std::string content;
			std::map<std::string, std::string> attrs;
		};
		using Batch = std::vector<Cell>;

	public:
		ExperimentalDesignTable(void) = default;
		ExperimentalDesignTable(const std::shared_ptr<SSUtils::XML::Node> node, const std::set<std::string> &factors);
		ExperimentalDesignTable(const ExperimentalDesignTable &ano) = default;
		ExperimentalDesignTable(ExperimentalDesignTable &&ano) = default;
		ExperimentalDesignTable &operator=(const ExperimentalDesignTable &rhs) = default;
		ExperimentalDesignTable &operator=(ExperimentalDesignTable &&rhs) = default;
		~ExperimentalDesignTable(void) = default;

		inline std::vector<std::string> &typeNames(void) { return m_typeNames; }
		inline const std::vector<std::string> &typeNames(void) const { return m_typeNames; }

		inline std::vector<Batch> &batches(void) { return m_batches; }
		inline const std::vector<Batch> &batches(void) const { return m_batches; }

		const bool valid(const std::shared_ptr<XSDFrontend::XSDModel> model = nullptr) const;
		inline const bool empty(void) const { return m_batches.empty(); }

		static ExperimentalDesignTable fromXML(const std::shared_ptr<SSUtils::XML::Node> node, const std::set<std::string> &factors);
		std::shared_ptr<SSUtils::XML::Node> toXML(void) const;

		static const bool checkXMLStruct(const std::shared_ptr<SSUtils::XML::Node> node, const std::set<std::string> &factors = std::set<std::string>());
		const bool checkTableStruct(void) const;

	private:
		std::vector<std::string> m_typeNames;
		std::vector<Batch> m_batches;
	};
};
