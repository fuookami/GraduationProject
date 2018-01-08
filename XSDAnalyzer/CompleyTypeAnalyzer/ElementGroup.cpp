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

		ElementGroup::ValueType::ValueType(const ValueType &&ano)
			: flag(ano.flag), element(ano.element), anyElement(ano.anyElement), elementGroup(ano.elementGroup)
		{
		}

		ElementGroup::ValueType &ElementGroup::ValueType::operator=(const ValueType &rhs)
		{
			flag = rhs.flag;
			element = rhs.element;
			anyElement = rhs.anyElement;
			elementGroup = rhs.elementGroup;

			return *this;
		}

		ElementGroup::ValueType &ElementGroup::ValueType::operator=(const ValueType &&rhs)
		{
			flag = rhs.flag;
			element = rhs.element;
			anyElement = rhs.anyElement;
			elementGroup = rhs.elementGroup;

			return *this;
		}

		ElementGroup::ValueType::~ValueType(void)
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

		ElementGroup::ElementGroup(const std::string && name, const eElementGroupType type)
			: IXSDNamedElementInterface(), IXSDReferenceElementInterface(), IXSDNumberLimitedElementInterface(), 
			m_type(type), m_vals()
		{
		}

		ElementGroup::ElementGroup(const ElementGroup & ano)
			: IXSDNamedElementInterface(ano), IXSDReferenceElementInterface(ano), IXSDNumberLimitedElementInterface(ano), 
			m_type(ano.m_type), m_vals(ano.m_vals)
		{
		}

		ElementGroup::ElementGroup(const ElementGroup && ano)
			: IXSDNamedElementInterface(std::move(ano)), IXSDReferenceElementInterface(std::move(ano)), IXSDNumberLimitedElementInterface(std::move(ano)),
			m_type(ano.m_type), m_vals(ano.m_vals)
		{
		}

		ElementGroup & ElementGroup::operator=(const ElementGroup & rhs)
		{
			m_type = rhs.m_type;
			m_vals = rhs.m_vals;

			IXSDNamedElementInterface::operator=(rhs);
			IXSDReferenceElementInterface::operator=(rhs);
			IXSDNumberLimitedElementInterface::operator=(rhs);

			return *this;
		}

		ElementGroup & ElementGroup::operator=(const ElementGroup && rhs)
		{
			m_type = rhs.m_type;
			m_vals = rhs.m_vals;

			IXSDNamedElementInterface::operator=(std::move(rhs));
			IXSDReferenceElementInterface::operator=(std::move(rhs));
			IXSDNumberLimitedElementInterface::operator=(std::move(rhs));

			return *this;
		}

		ElementGroup::~ElementGroup(void)
		{
		}
	};
};
