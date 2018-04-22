#include "_pri_xml_loader.h"
#include "XMLNode.h"
#include "FileUtils.h"
#include <boost/property_tree/xml_parser.hpp>

namespace SSUtils
{
	namespace XML
	{
		std::shared_ptr<Node> getNode(const boost::property_tree::ptree::value_type & root, const CharType charType)
		{
			if (root.first == AttrTag)
			{
				return nullptr;
			}

			auto ret(Node::generate(root.first));
			getAttrs(ret, root, charType);
			getContent(ret, root, charType);

			return ret;
		}

		std::shared_ptr<Node> getTree(const boost::property_tree::ptree::value_type & root, const CharType charType)
		{
			if (root.first == AttrTag)
			{
				return nullptr;
			}

			auto ret(Node::generate(root.first));
			getAttrs(ret, root, charType);
			getChildren(ret, root, charType);

			if (!ret->hasAnyChild())
			{
				getContent(ret, root, charType);
			}

			return ret;
		}

		void getAttrs(std::shared_ptr<Node> node, const boost::property_tree::ptree::value_type & root, const CharType charType)
		{
			static const boost::property_tree::ptree EmptyPTree;

			if (root.first == node->getTag())
			{
				const auto &attrs(root.second.get_child(AttrTag, EmptyPTree));
				for (const auto &attr : attrs)
				{
					node->addAttr(std::make_pair(String::toLocal(charType, attr.first), String::toLocal(charType, attr.second.data())));
				}
			}
		}

		void getChildren(std::shared_ptr<Node> node, const boost::property_tree::ptree::value_type & root, const CharType charType)
		{
			if (root.first == node->getTag())
			{
				for (const auto &childRoot : root.second)
				{
					if (childRoot.first != AttrTag)
					{
						auto tree(getTree(childRoot, charType));
						if (tree != nullptr)
						{
							node->addChild(tree);
						}
					}
				}
			}
		}

		void getContent(std::shared_ptr<Node> node, const boost::property_tree::ptree::value_type & root, const CharType charType)
		{
			if (root.first == node->getTag())
			{
				node->setContent(String::toLocal(charType, root.second.data()));
			}
		}

		const bool openXMLFile(boost::property_tree::ptree & pt, const std::string & url)
		{
			if (File::checkFileExist(url))
			{
				try {
					boost::property_tree::xml_parser::read_xml(url, pt);
				}
				catch (const boost::property_tree::xml_parser::xml_parser_error &ex) {
					std::cerr << "error in file " << ex.filename() << " line " << ex.line() << std::endl;
					return false;
				}
				return true;
			}
			else
			{
				return false;
			}
		}

		std::vector<std::shared_ptr<Node>> loadXMLFile(const std::string & url, const CharType charType)
		{
			boost::property_tree::ptree root;
			if (openXMLFile(root, url))
			{
				return loadXMLFile(root, charType);
			}
			else
			{
				return std::vector<std::shared_ptr<Node>>();
			}
		}

		std::vector<std::shared_ptr<Node>> loadXMLFile(const boost::property_tree::ptree & pt, const CharType charType)
		{
			std::vector<std::shared_ptr<Node>> nodes;
			for (const auto &nodeRoot : root)
			{
				auto tree(getTree(nodeRoot, charType));
				if (tree != nullptr)
				{
					nodes.push_back(tree);
				}
			}

			return nodes;
		}
	};
};
