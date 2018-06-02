#pragma once

#include "CARSDKGlobal.h"
#include "DataModelingModule.h"
#include "DataHandlingModule.h"
#include "ExperimentalDesignTable.h"
#include "SSUtils\XMLUtils.h"
#include "SSUtils\XSD\XSDModel.h"

#include <map>
#include <set>
#include <utility>
#include <boost/shared_ptr.hpp>

namespace CARSDK
{
	class CARSDK_API_DECLSPEC IExperimentalDesignMethodInterface abstract
	{
	public:
		IExperimentalDesignMethodInterface(void) = default;
		IExperimentalDesignMethodInterface(const IExperimentalDesignMethodInterface &ano) = delete;
		IExperimentalDesignMethodInterface(IExperimentalDesignMethodInterface &&ano) = delete;
		IExperimentalDesignMethodInterface &operator=(const IExperimentalDesignMethodInterface &rhs) = delete;
		IExperimentalDesignMethodInterface &operator=(IExperimentalDesignMethodInterface &&rhs) = delete;
		virtual ~IExperimentalDesignMethodInterface(void) = default;

		virtual const std::string &category(void) const = 0;
		virtual const std::string &displayName(void) const = 0;
		virtual const std::map<std::string, std::pair<std::string, CARSDK::AttributeType>> &neededAttributes(void) const = 0;
		virtual const std::map<std::string, std::string> &factorNeededAttributes(void) const = 0;
		virtual const bool valid(const std::map<std::string, std::string> &attributes) = 0;
		virtual ExperimentalDesignTable generateExperimentalDesignTable(const std::shared_ptr<XSDFrontend::XSDModel> &xsdModel, const std::map<std::string, std::string> &attributes) = 0;
		inline const std::string &lastError(void) const { return m_lastError; };

	protected:
		std::string m_lastError;
	};
};
