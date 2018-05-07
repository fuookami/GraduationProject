#include "VEDAVersion.h"
#include "DatetimeUtils.h"
#include "StringUtils.h"

namespace VEDA
{
	const int MajorVersion(0);
	const int SubVersion(1);
	const int ModifyVersion(9);

	const std::string Version = SSUtils::String::getVersion(MajorVersion, SubVersion, ModifyVersion);
	const std::string BuildDatetime = SSUtils::Datetime::getBuildDatetime(__DATE__, __TIME__).toString();
};
