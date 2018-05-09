#pragma once

#include <string>

namespace VEDA
{
	extern const std::string ProjectFileSuffix;
	extern const std::string ProcessFileSuffix;
	extern const std::string OperationFileSuffix;
	extern const std::string DataModalDefinitionFileSuffix;
	extern const std::string DataFileSuffix;

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
