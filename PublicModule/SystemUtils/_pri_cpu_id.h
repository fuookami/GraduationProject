#pragma once

#include "Global.h"
#include <array>

namespace SSUtils
{
	namespace System
	{
		std::array<byte, CPUIdLength> getCPUId(void);
		void _getCPUId(uint32 CPUInfo[4], uint32  infoType);
		void _getCPUIdEx(uint32 CPUInfo[4], uint32  infoType, uint32 ecxValue);
	}
};
