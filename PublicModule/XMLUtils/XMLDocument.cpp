#include "XMLDocument.h"
#include "XMLLoader.h"
#include "XMLSaver.h"
#include "XMLNode.h"

namespace SSUtils
{
	namespace XML
	{
		Document::Document(const std::vector<std::shared_ptr<Node>>& roots)
		{
			setRoots(roots);
		}

		Document::Document(std::vector<std::shared_ptr<Node>>&& roots)
		{
			setRoots(std::move(roots));
		}

		Document::Document(const Document &ano)
		{
			setRoots(ano);
		}

		Document::Document(Document && ano)
		{
			setRoots(std::move(ano));
		}

		Document & Document::operator=(const Document & rhs)
		{
			setRoots(rhs);
			return *this;
		}

		Document &Document::operator=(Document &&rhs)
		{
			setRoots(std::move(rhs));
			return *this;
		}

		Document Document::fromFile(const std::string & url, const CharType charType)
		{
			Loader loader(url, charType);
			return Document(loader());
		}

		Document Document::fromFile(std::string && url, const CharType charType)
		{
			Loader loader(std::move(url), charType);
			return Document(loader());
		}

		Document Document::fromString(const std::string & data, const CharType charType)
		{
			Scaner scaner(data, charType);
			return Document(scaner());
		}

		Document Document::fromString(std::string && data, const CharType charType)
		{
			Scaner scaner(std::move(data), charType);
			return Document(scaner());
		}

		const bool Document::toFile(const std::string & url, const CharType charType)
		{
			Saver saver(url, *this, charType);
			return saver.toFile();
		}

		std::string Document::toString(const CharType charType)
		{
			Saver saver(*this, charType);
			return saver.toString();
		}

		void Document::setRoots(const std::vector<std::shared_ptr<Node>>& roots)
		{
			clear();
			for (const auto &root : roots)
			{
				if (root != nullptr)
				{
					push_back(Node::deepCopy(*root));
				}
			}
		}

		void Document::setRoots(std::vector<std::shared_ptr<Node>>&& roots)
		{
			clear();
			operator=(std::move(roots));
		}
	};
};
