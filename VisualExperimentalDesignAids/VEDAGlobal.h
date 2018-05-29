#pragma once

#include <string>

namespace VEDA
{
	extern const std::string ProjectFileExtension;
	extern const std::string ProcessFileExtension;
	extern const std::string OperationFileExtension;

	extern const std::string ModelFileExtension;
	extern const std::string DataFileExtension;

	extern const std::string ReportFileExtensionl;
	extern const std::string ReportConfigurationFileExtension;
	extern const std::string ReportDataFileExtension;

	extern const std::string GithubUrl;
	extern const std::string CodingUrl;

	namespace Tags
	{
		extern const std::string Project;
		extern const std::string Process;

		extern const std::string VerificationPublicKey;
		extern const std::string VerificationPrivateKey;
		extern const std::string VerificationToken;
		extern const std::string Name;
		extern const std::string DataModelFileName;
	};

	namespace Attrs
	{
		extern const std::string Type;
	};
};
