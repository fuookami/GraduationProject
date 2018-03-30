#include "VEDAVersion.h"
#include "DatetimeUtils.h"
#include "StringUtils.h"

namespace VEDA
{
	const int MajorVersion(0);
	const int SubVersion(1);
	const int ModifyVersion(9);

	const std::string Version = StringUtils::getVersion(MajorVersion, SubVersion, ModifyVersion);
	const std::string BuildDatetime = DatetimeUtils::getBuildDatetime(__DATE__, __TIME__).toString();
};
