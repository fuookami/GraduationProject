#pragma once

#include <string>

namespace XSDFrontend
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
		static const std::string AnnotationTag = XSDTagPrefix + "annotation";
		static const std::string DocumentationTag = XSDTagPrefix + "documentation";
		static const std::string IncludeTag = XSDTagPrefix + "include";
		static const std::string SimpleTypeTag = XSDTagPrefix + "simpleType";
		static const std::string AttributeTag = XSDTagPrefix + "attribute";
		static const std::string AttributeGroupTag = XSDTagPrefix + "attributeGroup";
		static const std::string AnyAttributeTag = XSDTagPrefix + "anyAttribute";
		static const std::string GroupTag = XSDTagPrefix + "group";
		static const std::string AllTag = XSDTagPrefix + "all";
		static const std::string ChoiceTag = XSDTagPrefix + "choice";
		static const std::string SequenceTag = XSDTagPrefix + "sequence";
		static const std::string ComplexTypeTag = XSDTagPrefix + "complexType";
		static const std::string SimpleContentTag = XSDTagPrefix + "simpleContent";
		static const std::string ComplexContentTag = XSDTagPrefix + "complexContent";
		static const std::string ElementTag = XSDTagPrefix + "element";
		static const std::string AnyTag = XSDTagPrefix + "any";

		static const std::string RestrictionTag = XSDTagPrefix + "restriction";
		static const std::string ExtensionTag = XSDTagPrefix + "extension";
		static const std::string ListTag = XSDTagPrefix + "list";
		static const std::string UnionTag = XSDTagPrefix + "union";

		static const std::string MinExclusiveTag = XSDTagPrefix + "minExclusive";
		static const std::string MinInclusiveTag = XSDTagPrefix + "minInclusive";
		static const std::string MaxExclusiveTag = XSDTagPrefix + "maxExclusive";
		static const std::string MaxInclusiveTag = XSDTagPrefix + "maxInclusive";
		static const std::string TotalDigitsTag = XSDTagPrefix + "totalDigits";
		static const std::string FractionDigitsTag = XSDTagPrefix + "FractionDigits";
		static const std::string LengthValidatorTag = XSDTagPrefix + "length";
		static const std::string MinLengthValidatorTag = XSDTagPrefix + "minLength";
		static const std::string MaxLengthValidatorTag = XSDTagPrefix + "maxLength";
		static const std::string EnumValidatorTag = XSDTagPrefix + "enumeration";
		static const std::string WhiteSpaceTag = XSDTagPrefix + "whiteSpace";
		static const std::string PatternTag = XSDTagPrefix + "pattern";

		static const std::string LangAttr("xml:lang");
		static const std::string NameAttr("name");
		static const std::string TypeAttr("type");
		static const std::string BaseTypeAttr("base");
		static const std::string ReferenceAttr("ref");
		static const std::string SchemaLocationAttr("schemaLocation");
		static const std::string ValueAttr("value");

		static const std::string ListItemTypeAttr("itemTypes");
		static const std::string UnionItemTypeAttr("memberTypes");
		static const std::string DefaultAttr("default");
		static const std::string FixedAttr("fixed");
		static const std::string FormAttr("form");
		static const std::string UseAttr("use");
		static const std::string AbstractAttr("abstract");
		static const std::string NillableAttr("nillable");
		static const std::string MixedAttr("mixed");
		static const std::string BlockAttr("block");
		static const std::string FinalAttr("final");
		static const std::string NamesapceAttr("namespace");
		static const std::string ProcessContentsAttr("processContents");
		static const std::string MinOccursAttr("minOccurs");
		static const std::string MaxOccursAttr("maxOccurs");
		static const std::string SubstitutionGroupAttr("substitutionGroup");

		const bool isInXSDNameSpace(const std::string &token);
	};
};
