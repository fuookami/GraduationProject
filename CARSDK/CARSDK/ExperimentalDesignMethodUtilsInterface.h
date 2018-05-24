#pragma once

#include "CARSDKGlobal.h"
#include "ExperimentalDesignMethodInterface.h"

namespace CARSDK
{
	class IExperimentalDesignMethodUtilsInterface abstract
	{
	public:
		IExperimentalDesignMethodUtilsInterface(void) = default;
		IExperimentalDesignMethodUtilsInterface(const IExperimentalDesignMethodInterface &ano) = delete;
		IExperimentalDesignMethodUtilsInterface(IExperimentalDesignMethodUtilsInterface &&ano) = delete;
		IExperimentalDesignMethodUtilsInterface &operator=(const IExperimentalDesignMethodUtilsInterface &rhs) = delete;
		IExperimentalDesignMethodUtilsInterface &operator=(IExperimentalDesignMethodUtilsInterface &&rhs) = delete;
		virtual ~IExperimentalDesignMethodUtilsInterface(void) = default;

		virtual const std::string &name(void) const = 0;
		virtual const std::string &displayName(void) const = 0;
		virtual const std::map<std::string, IExperimentalDesignMethodInterface *> &methods(void) const = 0;
	};
};
