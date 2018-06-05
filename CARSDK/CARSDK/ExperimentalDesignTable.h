#pragma once

#include "CARSDKGlobal.h"
#include "DataModelingModule.h"
#include "SSUtils/XSD/XSDModel.h"
#include "SSUtils/XMLUtils.h"

namespace CARSDK
{
	class CARSDK_API_DECLSPEC ExperimentalDesignTable
	{
	public:
		static const std::string Tag;
		static const std::string BatchTag;
		static const std::string CellTag;
		static const std::string NameAttr;
		struct Cell
		{
			std::string content;
			std::map<std::string, std::string> attrs;
		};
		using Batch = std::vector<Cell>;

	public:
		ExperimentalDesignTable(void) = default;
		ExperimentalDesignTable(const std::shared_ptr<SSUtils::XML::Node> node, const FactorTypeGroup &group);
		ExperimentalDesignTable(const ExperimentalDesignTable &ano) = default;
		ExperimentalDesignTable(ExperimentalDesignTable &&ano) = default;
		ExperimentalDesignTable &operator=(const ExperimentalDesignTable &rhs) = default;
		ExperimentalDesignTable &operator=(ExperimentalDesignTable &&rhs) = default;
		~ExperimentalDesignTable(void) = default;

		inline std::set<std::string> &readOnlyTypeNames(void) { return m_readOnlyTypeNames; }
		inline const std::set<std::string> &readOnlyTypeNames(void) const { return m_readOnlyTypeNames; }

		inline std::vector<std::string> &typeNames(void) { return m_typeNames; }
		inline const std::vector<std::string> &typeNames(void) const { return m_typeNames; }

		inline std::vector<Batch> &batches(void) { return m_batches; }
		inline const std::vector<Batch> &batches(void) const { return m_batches; }

		const bool valid(const std::shared_ptr<XSDFrontend::XSDModel> model = nullptr) const;
		inline void clear(void) { m_typeNames.clear(); m_batches.clear(); }
		inline const bool empty(void) const { return m_batches.empty(); }

		static ExperimentalDesignTable fromXML(const std::shared_ptr<SSUtils::XML::Node> node, const FactorTypeGroup &group);
		std::shared_ptr<SSUtils::XML::Node> toXML(void) const;

		static const bool checkXMLStruct(const std::shared_ptr<SSUtils::XML::Node> node, const FactorTypeGroup &group = FactorTypeGroup());
		const bool checkTableStruct(void) const;

	private:
		std::set<std::string> m_readOnlyTypeNames;
		std::vector<std::string> m_typeNames;
		std::vector<Batch> m_batches;
	};
};
