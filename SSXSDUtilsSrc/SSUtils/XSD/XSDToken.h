#pragma once

#include "XSDGlobal.h"
#include <string>

namespace XSDFrontend
{
	namespace Token
	{
#define String_Declaration(name) SSXSDUtils_API_DECLSPEC const std::string &##name##(void);\

		String_Declaration(XSPrefix);
		String_Declaration(XSDPrefix);
		String_Declaration(NamespaceSeparator);
		String_Declaration(XSNamespace);
		String_Declaration(XSDNamespace);
		String_Declaration(XSDTagPrefix);

		String_Declaration(AttrTag);

		String_Declaration(SchemaTag);
		String_Declaration(AnnotationTag);
		String_Declaration(DocumentationTag);
		String_Declaration(IncludeTag);
		String_Declaration(SimpleTypeTag);
		String_Declaration(AttributeTag);
		String_Declaration(AttributeGroupTag);
		String_Declaration(AnyAttributeTag);
		String_Declaration(GroupTag);
		String_Declaration(AllTag);
		String_Declaration(ChoiceTag);
		String_Declaration(SequenceTag);
		String_Declaration(ComplexTypeTag);
		String_Declaration(SimpleContentTag);
		String_Declaration(ComplexContentTag);
		String_Declaration(ElementTag);
		String_Declaration(AnyTag);

		String_Declaration(RestrictionTag);
		String_Declaration(ExtensionTag);
		String_Declaration(ListTag);
		String_Declaration(UnionTag);

		String_Declaration(MinExclusiveTag);
		String_Declaration(MinInclusiveTag);
		String_Declaration(MaxExclusiveTag);
		String_Declaration(MaxInclusiveTag);
		String_Declaration(TotalDigitsTag);
		String_Declaration(FractionDigitsTag);
		String_Declaration(LengthValidatorTag);
		String_Declaration(MinLengthValidatorTag);
		String_Declaration(MaxLengthValidatorTag);
		String_Declaration(EnumValidatorTag);
		String_Declaration(WhiteSpaceTag);
		String_Declaration(PatternTag);

		String_Declaration(LangAttr);
		String_Declaration(NameAttr);
		String_Declaration(TypeAttr);
		String_Declaration(BaseTypeAttr);
		String_Declaration(ReferenceAttr);
		String_Declaration(SchemaLocationAttr);
		String_Declaration(ValueAttr);

		String_Declaration(ListItemTypeAttr);
		String_Declaration(UnionItemTypeAttr);
		String_Declaration(DefaultAttr);
		String_Declaration(FixedAttr);
		String_Declaration(FormAttr);
		String_Declaration(UseAttr);
		String_Declaration(AbstractAttr);
		String_Declaration(NillableAttr);
		String_Declaration(MixedAttr);
		String_Declaration(BlockAttr);
		String_Declaration(FinalAttr);
		String_Declaration(NamesapceAttr);
		String_Declaration(ProcessContentsAttr);
		String_Declaration(MinOccursAttr);
		String_Declaration(MaxOccursAttr);
		String_Declaration(SubstitutionGroupAttr);

		SSXSDUtils_API_DECLSPEC const bool isInXSDNameSpace(const std::string &token);

#undef String_Declaration
	};
};
