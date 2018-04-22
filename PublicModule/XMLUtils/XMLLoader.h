#pragma once

#include "_pri_xml_global.h"
#include "StringUtils.h"
#include <boost/property_tree/ptree.hpp>
#include <memory>

namespace SSUtils
{
	namespace XML
	{
		struct Loader
		{
			boost::property_tree::ptree ori_pt;
			std::shared_ptr<std::reference_wrapper<const boost::property_tree::ptree>> pt;
			std::string url;
			CharType charType;

			Loader(const CharType _charType = String::LocalCharType);
			Loader(const std::string &_url, const CharType _charType = String::LocalCharType);
			Loader(std::string &&_url, const CharType _charType = String::LocalCharType);
			Loader(const boost::property_tree::ptree &_pt, const CharType _charType = String::LocalCharType);
			Loader(const Loader &ano) = default;
			Loader(Loader &&ano) = default;
			~Loader(void) = default;

			inline const bool isOpened(void) const;
			std::shared_ptr<std::reference_wrapper<const boost::property_tree::ptree>> open(void);
			std::shared_ptr<std::reference_wrapper<const boost::property_tree::ptree>> open(const std::string &_url);
			std::vector<std::shared_ptr<Node>> operator()();
			std::vector<std::shared_ptr<Node>> operator()(const boost::property_tree::ptree &_pt, const CharType _charType = String::LocalCharType);
		};
	};
};
