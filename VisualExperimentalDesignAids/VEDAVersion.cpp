#include "VEDAVersion.h"
#include "SSUtils\DatetimeUtils.h"
#include "SSUtils\StringUtils.h"

namespace VEDA
{
	const int MajorVersion(0);
	const int SubVersion(3);
	const int ModifyVersion(17);

	const std::string Version = SSUtils::String::getVersion(MajorVersion, SubVersion, ModifyVersion);
	const std::string BuildDatetime = SSUtils::Datetime::getBuildDatetime(__DATE__, __TIME__).toString();
};
