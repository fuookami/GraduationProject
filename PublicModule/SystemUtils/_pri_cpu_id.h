#pragma once

#include "_pri_global.h"
#include <array>

namespace FuUtils
{
	namespace System
	{
		std::array<byte, CPUIdLength> getCPUId(void);
		void _getCPUId(unsigned int CPUInfo[4], unsigned int infoType);
		void _getCPUIdEx(unsigned int CPUInfo[4], unsigned int infoType, unsigned int ecxValue);
	}
};
