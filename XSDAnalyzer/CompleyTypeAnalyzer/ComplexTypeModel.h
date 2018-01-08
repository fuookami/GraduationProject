#pragma once

#include "Element.h"
#include "AnyElement.h"
#include "ElementGroup.h"
#include "SimpleContent.h"
#include "ComplexContent.h"

namespace XSDFrontend
{
	class ComplexTypeModel
	{
	public:
		ComplexTypeModel(void);
		ComplexTypeModel(const ComplexTypeModel &ano) = delete;
		ComplexTypeModel(const ComplexTypeModel &&ano) = delete;
		ComplexTypeModel &operator=(const ComplexTypeModel &rhs) = delete;
		ComplexTypeModel &operator=(const ComplexTypeModel &&rhs) = delete;
		~ComplexTypeModel(void);

	public:
		static const std::string getNewDefaultElementGroupName(void);

	private:

	};
};
