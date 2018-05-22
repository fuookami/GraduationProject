#pragma once

#include "Global.h"
#include "SystemUtils/_pri_system_global.h"
#include "SystemUtils/EndianTranslator.h"
#include <array>

namespace SSUtils
{
	namespace System
	{
		extern API_DECLSPEC const std::array<byte, CPUIdLength> CPUId;
		extern API_DECLSPEC const uint32 CPUCoreNumber;
	};
};
