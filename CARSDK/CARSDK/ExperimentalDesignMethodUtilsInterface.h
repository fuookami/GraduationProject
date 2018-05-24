#pragma once

#include "CARSDKGlobal.h"
#include "ExperimentalDesignMethodInterface.h"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace CARSDK
{
	class CARSDK_API_DECLSPEC IExperimentalDesignMethodUtilsInterface abstract
	{
	public:
		IExperimentalDesignMethodUtilsInterface(void) = default;
		IExperimentalDesignMethodUtilsInterface(const IExperimentalDesignMethodUtilsInterface &ano) = delete;
		IExperimentalDesignMethodUtilsInterface(IExperimentalDesignMethodUtilsInterface &&ano) = delete;
		IExperimentalDesignMethodUtilsInterface &operator=(const IExperimentalDesignMethodUtilsInterface &rhs) = delete;
		IExperimentalDesignMethodUtilsInterface &operator=(IExperimentalDesignMethodUtilsInterface &&rhs) = delete;
		virtual ~IExperimentalDesignMethodUtilsInterface(void) = default;

		virtual const std::string &name(void) const = 0;
		virtual const std::string &displayName(void) const = 0;
		virtual const std::map<std::string, boost::shared_ptr<IExperimentalDesignMethodInterface>> &methods(void) const = 0;

	protected:
		static inline std::pair<std::string, boost::shared_ptr<IExperimentalDesignMethodInterface>> make_method(boost::shared_ptr<IExperimentalDesignMethodInterface> method)
		{
			return std::make_pair(method->category(), method);
		}
	};
};
