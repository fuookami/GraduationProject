#pragma once

#include "_pri_xml_global.h"
#include <map>
#include <memory>

namespace SSUtils
{
	namespace XML
	{
		class Node
		{
		public:
			static const int npos;

		private:
			static const std::string DefaultAttrValue;

		public:
			static std::shared_ptr<Node> generate(const std::string &tag);
			static std::shared_ptr<Node> generate(std::string &&tag);
			static std::shared_ptr<Node> deepCopy(const Node &ano);
			static std::shared_ptr<Node> moveCopy(Node &&ano);

		private:
			Node(const std::string &tag);
			Node(std::string &&tag);
			Node(const Node &ano);
			Node(Node &&ano);
		public:
			Node &operator=(const Node &rhs);
			Node &operator=(Node &&rhs);
			~Node(void) = default;

		public:
			inline void setTag(const std::string &tag);
			inline void setTag(std::string &&tag);
			inline const std::string &getTag(void) const;

			inline void setPath(const std::string &path);
			inline void setPath(std::string &&path);
			inline const std::string &getPath(void) const;

			inline void setContent(const std::string &content);
			inline void setContent(std::string &&content);
			inline const std::string &getContent(void) const;

		public:
			inline void addAttr(const std::pair<std::string, std::string> &pair);
			inline void addAttr(std::pair<std::string, std::string> &&pair);
			inline void addAttr(const std::string &key, const std::string &value);
			inline void addAttr(const std::string &key, std::string &&value);
			inline void eraseAttr(const std::string &key);
			inline void clearAttrs(void);
			inline void setAttr(const std::string &key, const std::string &value);
			inline void setAttr(const std::string &key, std::string &&value);
			inline void setAttr(const std::pair<std::string, std::string> &pair);
			inline void setAttr(std::pair<std::string, std::string> &&pair);
			inline const bool hasAttr(const std::string &key) const;
			const std::string &getAttr(const std::string &key, const std::string &defaultValue = DefaultAttrValue) const;
			inline const std::map<std::string, std::string> &getAttrs(void) const;
			inline std::map<std::string, std::string> &getAttrs(void);

		public:
			inline void setParent(const std::weak_ptr<Node> parent);
			inline void removeParent(void);
			inline const bool hasParent(void) const;
			inline const std::weak_ptr<Node> getParent(void) const;

		public:
			inline void addChild(const std::weak_ptr<Node> child);
			inline void removeChild(const std::weak_ptr<Node> child);
			template<typename fun_t>
			inline void removeChildren(const fun_t fun);
			inline void clearChild(void);
			inline const bool hasChild(const std::string &tag) const;
			template<typename fun_t>
			inline const bool hasChild(const fun_t fun);
			inline const bool hasAnyChild(void) const;
			const int findChild(const std::string &tag, const int pos = 0) const;
			template<typename fun_t>
			const int findChild(const fun_t fun, const int pos = 0) const;
			inline const std::vector<std::weak_ptr<Node>> &getChildren(void) const;
			inline std::vector<std::weak_ptr<Node>> &getChildren(void);

		private:
			void deepCopyFrom(const Node &ano);
			void moveCopyFrom(Node &&ano);

		private:
			std::string m_tag;
			std::string m_path;
			std::string m_content;
			std::map<std::string, std::string> m_attrs;
			
			std::weak_ptr<Node> m_self;
			std::weak_ptr<Node> m_parent;
			std::vector<std::weak_ptr<Node>> m_children;
		};

		template<typename fun_t>
		void Node::removeChildren(const fun_t fun)
		{
			std::remove_if(m_children.cbegin(), m_children.cend(), fun);
		}

		template<typename fun_t>
		const bool Node::hasChild(const fun_t fun)
		{
			auto it(std::find_if(m_children.cbegin(), m_children.cend(), fun));
			return it != m_children.cend();
		}

		template<typename fun_t>
		const int Node::findChild(const fun_t fun, const int pos) const
		{
			for (int i(pos), j(m_children.size()); i != j; ++i)
			{
				auto child(m_children[i].lock());
				if (child != nullptr && fun(*child))
				{
					return i;
				}
			}
			return npos;
		}
	};
};
