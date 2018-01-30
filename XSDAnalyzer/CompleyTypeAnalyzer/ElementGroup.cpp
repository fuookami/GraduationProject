#include "ElementGroup.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		ElementGroup::ValueType::ValueType(void)
			: flag(eValueType::tNone), element(nullptr), anyElement(nullptr), elementGroup(nullptr)
		{
		}

		ElementGroup::ValueType::ValueType(const std::shared_ptr<Element>& ele)
			: flag(eValueType::tElement), element(ele), elementGroup(nullptr)
		{
		}

		ElementGroup::ValueType::ValueType(const std::shared_ptr<AnyElement> &anyEle)
			: flag(eValueType::tAnyElement), element(nullptr), anyElement(anyEle), elementGroup(nullptr)
		{

		}

		ElementGroup::ValueType::ValueType(const std::shared_ptr<ElementGroup>& group)
			: flag(eValueType::tElementGroup), element(nullptr), anyElement(nullptr), elementGroup(group)
		{
		}

		ElementGroup::ValueType::ValueType(const ValueType &ano)
			: flag(ano.flag), element(ano.element), anyElement(ano.anyElement), elementGroup(ano.elementGroup)
		{
		}

		ElementGroup::ElementGroup(const eElementGroupType type)
			: ElementGroup("", type)
		{
		}

		ElementGroup::ElementGroup(const std::string & name, const eElementGroupType type)
			: IXSDNamedElementInterface(), IXSDReferenceElementInterface(), IXSDNumberLimitedElementInterface(),
			m_type(type), m_vals()
		{
		}

		ElementGroup::ElementGroup(std::string && name, const eElementGroupType type)
			: IXSDNamedElementInterface(), IXSDReferenceElementInterface(), IXSDNumberLimitedElementInterface(),
			m_type(type), m_vals()
		{
		}

		ElementGroup::ElementGroup(const ElementGroup & ano)
			: IXSDNamedElementInterface(ano), IXSDReferenceElementInterface(ano), IXSDNumberLimitedElementInterface(ano),
			m_type(ano.m_type), m_vals(ano.m_vals)
		{
		}
	};
};
