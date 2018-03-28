#include "SystemUtils/_pri_cpu_id.h"

namespace FuUtils
{
	namespace System
	{
		const std::array<byte, CPUIdLength> CPUId = getCPUId();
	};
};
