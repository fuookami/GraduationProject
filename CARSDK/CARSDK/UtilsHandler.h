#pragma once

#include "CARSDKGlobal.h"
#include <memory>
#include <set>
#include <map>
#include <boost/dll.hpp>

namespace CARSDK
{
	class UtilsHandler
	{
	public:
		static std::shared_ptr<UtilsHandler> instance(void);
		static std::shared_ptr<UtilsHandler> instance(const std::string &path);

	private:
		UtilsHandler(void) = default;
	public:
		UtilsHandler(const UtilsHandler &ano) = delete;
		UtilsHandler(UtilsHandler &&ano) = delete;
		UtilsHandler &operator=(const UtilsHandler &rhs) = delete;
		UtilsHandler &operator=(UtilsHandler &&rhs) = delete;
		~UtilsHandler(void) = default;

		const bool hasLoaded(const std::string &url) const;
		inline const std::set<std::string> &urls(void) const { return m_urls; }

		std::shared_ptr<boost::dll::shared_library> lib(const std::string &url) const;
		inline const std::map<std::string, std::shared_ptr<boost::dll::shared_library>> &libs(void) const { return m_libs; }

		void loadUtils(const std::string &path);
		void loadUtil(const std::string &url);

	private:
		std::set<std::string> m_urls;
		std::map<std::string, std::shared_ptr<boost::dll::shared_library>> m_libs;
	};
};
