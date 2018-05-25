#include "stdafx.h"
#include "CARSDKGlobal.h"

namespace CARSDK
{
#define String_Definition(name, str)\
		const std::string &##name##(void)\
		{\
			static const std::string ret = std::string(str);\
			return ret;\
		}\

	const std::string EDMUtilsFactoryMethodName("getEDMUtilsInterface");
	const std::string EAUtilsFactoryMethodName("getEAUtilsInterface");

	String_Definition(UnitAttr, "unit");
	String_Definition(DigitAttr, "digit");

#undef String_Definition
};
