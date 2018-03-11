#pragma once

#include <string>

namespace XSDFrontend
{
	namespace Token
	{
		extern const std::string XSPrefix;
		extern const std::string XSDPrefix;
		extern const std::string NamespaceSeparator;
		extern const std::string XSNamespace;
		extern const std::string XSDNamespace;
		extern const std::string XSDTagPrefix;

		extern const std::string AttrTag;

		extern const std::string SchemaTag;
		extern const std::string IncludeTag;
		extern const std::string SimpleTypeTag;
		extern const std::string AttributeTag;
		extern const std::string AttributeGroupTag;
		extern const std::string AnyAttributeTag;
		extern const std::string GroupTag;
		extern const std::string AllTag;
		extern const std::string ChoiceTag;
		extern const std::string SequenceTag;
		extern const std::string ComplexTypeTag;
		extern const std::string SimpleContentTag;
		extern const std::string ComplexContentTag;
		extern const std::string ElementTag;
		extern const std::string AnyTag;

		extern const std::string RestrictionTag;
		extern const std::string ExtensionTag;
		extern const std::string ListTag;
		extern const std::string UnionTag;

		extern const std::string MinExclusiveTag;
		extern const std::string MinInclusiveTag;
		extern const std::string MaxExclusiveTag;
		extern const std::string MaxInclusiveTag;
		extern const std::string TotalDigitsTag;
		extern const std::string FractionDigitsTag;
		extern const std::string LengthValidatorTag;
		extern const std::string MinLengthValidatorTag;
		extern const std::string MaxLengthValidatorTag;
		extern const std::string EnumValidatorTag;
		extern const std::string WhiteSpaceTag;
		extern const std::string PatternTag;

		extern const std::string NameAttr;
		extern const std::string TypeAttr;
		extern const std::string BaseTypeAttr;
		extern const std::string ReferenceAttr;
		extern const std::string SchemaLocationAttr;
		extern const std::string ValueAttr;

		extern const std::string ListItemTypeAttr;
		extern const std::string UnionItemTypeAttr;
		extern const std::string DefaultAttr;
		extern const std::string FixedAttr;
		extern const std::string FormAttr;
		extern const std::string UseAttr;
		extern const std::string NamesapceAttr;
		extern const std::string ProcessContentsAttr;
		extern const std::string MinOccursAttr;
		extern const std::string MaxOccursAttr;

		const bool isInXSDNameSpace(const std::string &token);
	};
};
