#pragma once

#include "Global.h"
#include <array>

namespace SSUtils
{
	namespace UUID
	{
		std::array<byte, UUIDLength> generateUUIDV1(void);
		std::array<byte, UUIDLength> generateUUIDV4(void);
	};
};
