#include "VEDAModelFileBase.h"
#include "SSUtils/XSD/XSDAnalyzer.h"
#include "SSUtils/XSD/XSDNormalizer.h"

namespace VEDA
{
	VEDAModelFileBase::VEDAModelFileBase(const std::string & url, const Type type)
		: VEDAFile(url, type)
	{
	}

	const bool VEDAModelFileBase::init(const std::shared_ptr<SSUtils::XML::Node> indexNode, const std::shared_ptr<SSUtils::XML::Node> modelNode)
	{
		if (!VEDAFile::init(indexNode))
		{
			return false;
		}

		XSDAnalyzer::XSDAnalyzer analyzer;
		if (!analyzer.scan(modelNode))
		{
			return false;
		}
		m_model = analyzer.getModel();

		return true;
	}

	const bool VEDAModelFileBase::init(const VEDAFile & parentFile, const std::string & name)
	{
		return VEDAFile::init(parentFile, name);
	}

	std::shared_ptr<SSUtils::XML::Node> VEDAModelFileBase::normalizeModelParameter(void) const
	{
		XSDNormalizer::XSDNormalizer normalizer(m_model);
		if (!normalizer.normalize())
		{
			return nullptr;
		}

		return normalizer.getRoot();
	}
};
