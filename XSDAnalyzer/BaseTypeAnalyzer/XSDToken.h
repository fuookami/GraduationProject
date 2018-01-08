#pragma once

#include <string>

namespace XSDAnalyzer
{
	namespace Token
	{
		static const std::string XSPrefix("xs");
		static const std::string XSDPrefix("xsd");
		static const std::string NamespaceSeparator(":");
		static const std::string XSNamespace = XSPrefix + NamespaceSeparator;
		static const std::string XSDNamespace = XSDPrefix + NamespaceSeparator;
		static const std::string XSDTagPrefix = XSNamespace;

		static const std::string AttrTag("<xmlattr>");

		static const std::string SchemaTag = XSDTagPrefix + "schema";
		static const std::string IncludeTag = XSDTagPrefix + "include";
		static const std::string SimpleTypeTag = XSDTagPrefix + "simpleType";
		static const std::string CompleyTypeTag = XSDTagPrefix + "complexType";
		static const std::string ElementTypeTag = XSDTagPrefix + "elementType";

		static const std::string TypeTag = XSDTagPrefix + "restriction";
		static const std::string ListTag = XSDTagPrefix + "list";
		static const std::string UnionTag = XSDTagPrefix + "union";

		static const std::string LengthValidatorTag = XSDTagPrefix + "length";
		static const std::string MinLengthValidatorTag = XSDTagPrefix + "minLength";
		static const std::string MaxLengthValidatorTag = XSDTagPrefix + "maxLength";
		static const std::string EnumValidatorTag = XSDTagPrefix + "enumeration";
		static const std::string PatternTag = XSDTagPrefix + "pattern";

		static const std::string NameAttr("name");
		static const std::string BaseTypeAttr("base");
		static const std::string SchemaLocationAttr("schemaLocation");
		static const std::string ListItemTypeAttr("itemTypes");
		static const std::string UnionItemTypeAttr("memberTypes");

		const bool isInXSDNameSpace(const std::string &token);
	};
};
