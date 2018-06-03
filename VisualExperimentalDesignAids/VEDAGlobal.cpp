#include "VEDAGlobal.h"
#include "SSUtils/FileUtils.h"

namespace VEDA
{
	const std::string ProjectFileExtension("vedaproj");
	const std::string ProcessFileExtension("vedaproc");
	const std::string OperationFileExtension("vedaops");
	
	const std::string PublicModelFileExtension("vedapubmodel");
	const std::string ModelFileExtension("vedamodel");
	const std::string DataFileExtension("vedadata");

	const std::string ReportFileExtension("vedarpt");
	const std::string ReportConfigurationFileExtension("vedarptconf");
	const std::string ReportDataFileExtension("vedarptdata");

#ifdef _DEBUG
	const std::string PluginPath = std::string("D:\\project\\GraduationProject\\GraduationProject\\x64\\Debug\\plugins\\");
#else
	const std::string PluginPath = SSUtils::File::InitailPath() + std::string("plugins") + SSUtils::File::PathSeperator();
#endif

	const std::string GithubUrl("https://github.com/fuookami/GraduationProject");
	const std::string CodingUrl("https://coding.net/u/fuookami/p/GraduationProject/git?public=true");

	namespace Tags
	{
		const std::string Project("VedaProject");
		const std::string Process("VedaProcess");

		const std::string VerificationPublicKey("VerificationPublicKey");
		const std::string VerificationPrivateKey("VerificationPrivateKey");
		const std::string VerificationToken("VerifactionToken");

		const std::string Name("Name");
	};

	namespace Attrs
	{
		const std::string Type("type");
	};
};
