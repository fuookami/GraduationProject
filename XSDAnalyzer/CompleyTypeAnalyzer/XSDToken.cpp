#include "XSDToken.h"

namespace XSDFrontend
{
	namespace Token
	{
		const std::string XSPrefix("xs");
		const std::string XSDPrefix("xsd");
		const std::string NamespaceSeparator(":");
		const std::string XSNamespace = XSPrefix + NamespaceSeparator;
		const std::string XSDNamespace = XSDPrefix + NamespaceSeparator;
		const std::string XSDTagPrefix = XSNamespace;

		const std::string AttrTag("<xmlattr>");

		const std::string SchemaTag = XSDTagPrefix + "schema";
		const std::string IncludeTag = XSDTagPrefix + "include";
		const std::string SimpleTypeTag = XSDTagPrefix + "simpleType";
		const std::string AttributeTag = XSDTagPrefix + "attribute";
		const std::string AttributeGroupTag = XSDTagPrefix + "attributeGroup";
		const std::string AnyAttributeTag = XSDTagPrefix + "anyAttribute";
		const std::string GroupTag = XSDTagPrefix + "group";
		const std::string AllTag = XSDTagPrefix + "all";
		const std::string ChoiceTag = XSDTagPrefix + "choice";
		const std::string SequenceTag = XSDTagPrefix + "sequence";
		const std::string ComplexTypeTag = XSDTagPrefix + "complexType";
		const std::string SimpleContentTag = XSDTagPrefix + "simpleContent";
		const std::string ComplexContentTag = XSDTagPrefix + "complexContent";
		const std::string ElementTag = XSDTagPrefix + "element";
		const std::string AnyTag = XSDTagPrefix + "any";

		const std::string RestrictionTag = XSDTagPrefix + "restriction";
		const std::string ExtensionTag = XSDTagPrefix + "extension";
		const std::string ListTag = XSDTagPrefix + "list";
		const std::string UnionTag = XSDTagPrefix + "union";

		const std::string MinExclusiveTag = XSDTagPrefix + "minExclusive";
		const std::string MinInclusiveTag = XSDTagPrefix + "minInclusive";
		const std::string MaxExclusiveTag = XSDTagPrefix + "maxExclusive";
		const std::string MaxInclusiveTag = XSDTagPrefix + "maxInclusive";
		const std::string TotalDigitsTag = XSDTagPrefix + "totalDigits";
		const std::string FractionDigitsTag = XSDTagPrefix + "FractionDigits";
		const std::string LengthValidatorTag = XSDTagPrefix + "length";
		const std::string MinLengthValidatorTag = XSDTagPrefix + "minLength";
		const std::string MaxLengthValidatorTag = XSDTagPrefix + "maxLength";
		const std::string EnumValidatorTag = XSDTagPrefix + "enumeration";
		const std::string WhiteSpaceTag = XSDTagPrefix + "whiteSpace";
		const std::string PatternTag = XSDTagPrefix + "pattern";

		const std::string NameAttr("name");
		const std::string TypeAttr("type");
		const std::string BaseTypeAttr("base");
		const std::string ReferenceAttr("ref");
		const std::string SchemaLocationAttr("schemaLocation");
		const std::string ValueAttr("value");

		const std::string ListItemTypeAttr("itemTypes");
		const std::string UnionItemTypeAttr("memberTypes");
		const std::string DefaultAttr("default");
		const std::string FixedAttr("fixed");
		const std::string FormAttr("form");
		const std::string UseAttr("use");
		const std::string NamesapceAttr("namespace");
		const std::string ProcessContentsAttr("processContents");
		const std::string MinOccursAttr("minOccurs");
		const std::string MaxOccursAttr("maxOccurs");

		const bool isInXSDNameSpace(const std::string & token)
		{
			return token.find(XSNamespace) == 0 || token.find(Token::XSDNamespace) == 0;
		}
	};
};
