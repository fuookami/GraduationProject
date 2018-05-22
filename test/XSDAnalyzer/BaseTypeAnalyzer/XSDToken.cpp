#include "XSDToken.h"

namespace XSDAnalyzer
{
	namespace Token
	{
		const bool isInXSDNameSpace(const std::string & token)
		{
			return token.find(XSNamespace) == 0 || token.find(Token::XSDNamespace) == 0;
		}
	};
};
