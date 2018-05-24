#include "stdafx.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace Token
	{
#define String_Definition(name, str)\
		const std::string &##name##(void)\
		{\
			static const std::string ret = std::string(str);\
			return ret;\
		}\

		String_Definition(XSPrefix, "xs");
		String_Definition(XSDPrefix, "xsd");
		String_Definition(NamespaceSeparator, ":");
		String_Definition(XSNamespace, XSPrefix() + NamespaceSeparator());
		String_Definition(XSDNamespace, XSDPrefix() + NamespaceSeparator());
		String_Definition(XSDTagPrefix, XSNamespace());

		String_Definition(AttrTag, "<xmlattr>");

		String_Definition(SchemaTag, XSDTagPrefix() + "schema");
		String_Definition(AnnotationTag, XSDTagPrefix() + "annotation");
		String_Definition(DocumentationTag, XSDTagPrefix() + "documentation");
		String_Definition(IncludeTag, XSDTagPrefix() + "include");
		String_Definition(SimpleTypeTag, XSDTagPrefix() + "simpleType");
		String_Definition(AttributeTag, XSDTagPrefix() + "attribute");
		String_Definition(AttributeGroupTag, XSDTagPrefix() + "attributeGroup");
		String_Definition(AnyAttributeTag, XSDTagPrefix() + "anyAttribute");
		String_Definition(GroupTag, XSDTagPrefix() + "group");
		String_Definition(AllTag, XSDTagPrefix() + "all");
		String_Definition(ChoiceTag, XSDTagPrefix() + "choice");
		String_Definition(SequenceTag, XSDTagPrefix() + "sequence");
		String_Definition(ComplexTypeTag, XSDTagPrefix() + "complexType");
		String_Definition(SimpleContentTag, XSDTagPrefix() + "simpleContent");
		String_Definition(ComplexContentTag, XSDTagPrefix() + "complexContent");
		String_Definition(ElementTag, XSDTagPrefix() + "element");
		String_Definition(AnyTag, XSDTagPrefix() + "any");

		String_Definition(RestrictionTag, XSDTagPrefix() + "restriction");
		String_Definition(ExtensionTag, XSDTagPrefix() + "extension");
		String_Definition(ListTag, XSDTagPrefix() + "list");
		String_Definition(UnionTag, XSDTagPrefix() + "union");

		String_Definition(MinExclusiveTag, XSDTagPrefix() + "minExclusive");
		String_Definition(MinInclusiveTag, XSDTagPrefix() + "minInclusive");
		String_Definition(MaxExclusiveTag, XSDTagPrefix() + "maxExclusive");
		String_Definition(MaxInclusiveTag, XSDTagPrefix() + "maxInclusive");
		String_Definition(TotalDigitsTag, XSDTagPrefix() + "totalDigits");
		String_Definition(FractionDigitsTag, XSDTagPrefix() + "FractionDigits");
		String_Definition(LengthValidatorTag, XSDTagPrefix() + "length");
		String_Definition(MinLengthValidatorTag, XSDTagPrefix() + "minLength");
		String_Definition(MaxLengthValidatorTag, XSDTagPrefix() + "maxLength");
		String_Definition(EnumValidatorTag, XSDTagPrefix() + "enumeration");
		String_Definition(WhiteSpaceTag, XSDTagPrefix() + "whiteSpace");
		String_Definition(PatternTag, XSDTagPrefix() + "pattern");

		String_Definition(LangAttr, "xml:lang");
		String_Definition(NameAttr, "name");
		String_Definition(TypeAttr, "type");
		String_Definition(BaseTypeAttr, "base");
		String_Definition(ReferenceAttr, "ref");
		String_Definition(SchemaLocationAttr, "schemaLocation");
		String_Definition(ValueAttr, "value");

		String_Definition(ListItemTypeAttr, "itemTypes");
		String_Definition(UnionItemTypeAttr, "memberTypes");
		String_Definition(DefaultAttr, "default");
		String_Definition(FixedAttr, "fixed");
		String_Definition(FormAttr, "form");
		String_Definition(UseAttr, "use");
		String_Definition(AbstractAttr, "abstract");
		String_Definition(NillableAttr, "nillable");
		String_Definition(MixedAttr, "mixed");
		String_Definition(BlockAttr, "block");
		String_Definition(FinalAttr, "final");
		String_Definition(NamesapceAttr, "namespace");
		String_Definition(ProcessContentsAttr, "processContents");
		String_Definition(MinOccursAttr, "minOccurs");
		String_Definition(MaxOccursAttr, "maxOccurs");
		String_Definition(SubstitutionGroupAttr, "substitutionGroup");

		const bool isInXSDNameSpace(const std::string & token)
		{
			return token.find(XSNamespace()) == 0 || token.find(Token::XSDNamespace()) == 0;
		}
	};
};
