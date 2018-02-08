#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <vector>
#include <map>
#include <string>

#include "FileUtils.h"
#include "StringConvertUtils.h"

namespace XMLUtils
{
	static const std::string AttrTag("<xmlattr>");
	static const std::string PathSeperator("/");

	class XMLNode
	{
	public:
		static const int NoChild = -1;

	private:
		static const std::string DefaultAttrValue;

	public:
		XMLNode(const std::string &tag);
		XMLNode(std::string &&tag);
		XMLNode(const XMLNode &rhs) = default;
		XMLNode(XMLNode &&rhs) = default;
		XMLNode &operator=(const XMLNode &rhs) = default;
		XMLNode &operator=(XMLNode &&rhs) = default;
		~XMLNode(void) = default;

		inline void setTag(const std::string &tag) { m_tag.assign(tag); };
		inline void setTag(const std::string &&tag) { m_tag.assign(std::move(tag)); }
		inline const std::string &getTag(void) const { return m_tag; }

		inline void setPath(const std::string &path) { m_path.assign(path); }
		inline void setPath(const std::string &&path) { m_path.assign(std::move(path)); }
		inline const std::string &getPath(void) const { return m_path; }

		inline void setContent(const std::string &content) { m_content.assign(content); }
		inline void setContent(const std::string &&content) { m_content.assign(std::move(content)); }
		inline const std::string &getContent(void) const { return m_content; }

		inline void addAttr(const std::pair<std::string, std::string> &pair) { m_attrs.insert(pair); }
		inline void addAttr(const std::pair<std::string, std::string> &&pair) { m_attrs.insert(std::move(pair)); }
		inline void eraseAttr(const std::string &key) { m_attrs.erase(key); }
		inline const bool hasAttr(const std::string &key) const { return m_attrs.find(key) != m_attrs.cend(); }
		const std::string &getAttr(const std::string &key, const std::string &defaultValue = DefaultAttrValue) const;
		inline void setAttr(const std::string &key, const std::string &value) { m_attrs[key].assign(value); }
		inline void setAttr(const std::string &key, const std::string &&value) { m_attrs[key].assign(std::move(value)); }
		inline const std::map<std::string, std::string> &getAttrs(void) const { return m_attrs; }

	public:
		void tidyStruct(void);

	public:
		inline void addChild(const XMLNode &child) { m_children.push_back(child); }
		inline void addChild(const XMLNode &&child) { m_children.push_back(std::move(child)); }
		inline const bool hasChild(const std::string &tag) const { return findChild(tag) != NoChild; }
		inline const bool hasAnyChild(void) const { return !m_children.empty(); }
		int findChild(const std::string &tag, const int pos = 0) const;
		inline const std::vector<XMLNode> &getChildren(void) const { return m_children; }
		inline std::vector<XMLNode> &getChildren(void) { return m_children; }

		inline void setParent(XMLNode &parent) { m_parent = std::addressof(parent); }
		inline void removeParent(void) { m_parent = nullptr; }
		inline const bool hasParent(void) const { return m_parent == nullptr; }
		inline XMLNode *getParent(void) { return m_parent; }

	public:
		static XMLNode shallowCopyFrom(const XMLNode &ano);
		static XMLNode shallowCopyFrom(const XMLNode &&ano);

	private:
		std::string m_tag;
		std::string m_path;
		std::string m_content;
		std::map<std::string, std::string> m_attrs;

	private:
		XMLNode *m_parent;
		std::vector<XMLNode> m_children;
	};

	template<StringConvertUtils::StringCodeId code>
	XMLNode getNode(const boost::property_tree::ptree::value_type & root);
	template<StringConvertUtils::StringCodeId code>
	XMLNode getTree(const boost::property_tree::ptree::value_type & root);
	template<StringConvertUtils::StringCodeId code>
	void getAttrs(XMLNode &node, const boost::property_tree::ptree::value_type & root);
	template<StringConvertUtils::StringCodeId code>
	void getChildren(XMLNode &node, const boost::property_tree::ptree::value_type & root);
	template<StringConvertUtils::StringCodeId code>
	void getContent(XMLNode &node, const boost::property_tree::ptree::value_type &root);

	template<StringConvertUtils::StringCodeId code>
	const bool openXMLFile(boost::property_tree::ptree &pt, const std::string &fileUrl);
	template<StringConvertUtils::StringCodeId code>
	std::vector<XMLNode> scanXMLFile(const std::string &fileUrl);
	template<StringConvertUtils::StringCodeId code>
	std::vector<XMLNode> scanXMLFile(const boost::property_tree::ptree &root);

	template<StringConvertUtils::StringCodeId code>
	XMLNode getNode(const boost::property_tree::ptree::value_type & root)
	{
		if (root.first == AttrTag)
		{
			return XMLNode("");
		}

		XMLNode ret(root.first);
		getAttrs<code>(ret, root);
		getContent<code>(ret, root);

		return ret;
	}

	template<StringConvertUtils::StringCodeId code>
	XMLNode getTree(const boost::property_tree::ptree::value_type & root)
	{
		if (root.first == AttrTag)
		{
			return XMLNode("");
		}

		XMLNode ret(root.first);
		getAttrs<code>(ret, root);
		getChildren<code>(ret, root);

		if (!ret.hasAnyChild())
		{
			getContent<code>(ret, root);
		}

		return ret;
	}

	template<StringConvertUtils::StringCodeId code>
	void getAttrs(XMLNode & node, const boost::property_tree::ptree::value_type & root)
	{
		static const boost::property_tree::ptree EmptyPTree;

		if (root.first == node.getTag())
		{
			const auto &attrs(root.second.get_child(AttrTag, EmptyPTree));
			for (const auto &attr : attrs)
			{
				node.addAttr(std::make_pair(StringConvertUtils::toLocal<code>(attr.first), StringConvertUtils::toLocal<code>(attr.second.data())));
			}
		}
	}

	template<StringConvertUtils::StringCodeId code>
	void getChildren(XMLNode & node, const boost::property_tree::ptree::value_type & root)
	{
		if (root.first == node.getTag())
		{
			for (const auto &childRoot : root.second)
			{
				if (childRoot.first != AttrTag)
				{
					auto tree(getTree<code>(childRoot));
					if (!tree.getTag().empty())
					{
						node.addChild(std::move(tree));
					}
				}
			}
		}
	}

	template<StringConvertUtils::StringCodeId code>
	void getContent(XMLNode & node, const boost::property_tree::ptree::value_type & root)
	{
		if (root.first == node.getTag())
		{
			node.setContent(StringConvertUtils::toLocal<code>(root.second.data()));
		}
	}

	template<StringConvertUtils::StringCodeId code>
	const bool openXMLFile(boost::property_tree::ptree & pt, const std::string & fileUrl)
	{
		if (FileUtils::checkFileExist(fileUrl))
		{
			boost::property_tree::xml_parser::read_xml(fileUrl, pt);
			return true;
		}
		else
		{
			return false;
		}
	}

	template<StringConvertUtils::StringCodeId code>
	std::vector<XMLNode> scanXMLFile(const std::string & fileUrl)
	{
		boost::property_tree::ptree root;
		if (openXMLFile<code>(root, fileUrl))
		{
			return scanXMLFile<code>(root);
		}
		else
		{
			return std::vector<XMLNode>();
		}
	}

	template<StringConvertUtils::StringCodeId code>
	std::vector<XMLNode> scanXMLFile(const boost::property_tree::ptree & root)
	{
		std::vector<XMLNode> nodes;
		for (const auto &nodeRoot : root)
		{
			auto tree(getTree<code>(nodeRoot));
			if (!tree.getTag().empty())
			{
				nodes.push_back(std::move(tree));

				auto &node(nodes.back());
				node.tidyStruct();
			}
		}

		return nodes;
	}
};
