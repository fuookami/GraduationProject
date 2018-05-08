#pragma once

#include "_pri_xml_global.h"
#include "StringUtils.h"
#include <memory>

namespace SSUtils
{
	namespace XML
	{
		class Document : public std::vector<std::shared_ptr<Node>>
		{
		public:
			Document(void) = default;
			Document(const std::vector<std::shared_ptr<Node>> &roots);
			Document(std::vector<std::shared_ptr<Node>> &&roots);
			Document(const Document &ano);
			Document(Document &&ano);
			Document &operator=(const Document &rhs);
			Document &operator=(Document &&rhs);
			~Document(void) = default;

		public:
			static Document fromFile(const std::string &url, const CharType charType = String::LocalCharType);
			static Document fromFile(std::string &&url, const CharType charType = String::LocalCharType);
			static Document fromString(const std::string &data, const CharType charType = String::LocalCharType);
			static Document fromString(std::string &&data, const CharType charType = String::LocalCharType);

			const bool toFile(const std::string &url, const CharType charType = String::LocalCharType);
			std::string toString(const CharType charType = String::LocalCharType);

		private:
			void setRoots(const std::vector<std::shared_ptr<Node>> &roots);
			void setRoots(std::vector<std::shared_ptr<Node>> &&roots);
		};
	};
};
