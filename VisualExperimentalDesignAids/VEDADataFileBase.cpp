#include "VEDADataFileBase.h"
#include "SSUtils/XSD/XSDAnalyzer.h"
#include "SSUtils/XSD/XSDNormalizer.h"

namespace VEDA
{
	VEDADataFileBase::VEDADataFileBase(const std::string & url, const Type type)
		: VEDAFile(url, type)
	{
	}

	const bool VEDADataFileBase::init(const std::shared_ptr<SSUtils::XML::Node> indexNode, const std::shared_ptr<SSUtils::XML::Node> modelNode, const std::shared_ptr<SSUtils::XML::Node> dataNode)
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

		if (dataNode->getTag() != DataNodeTag())
		{
			return false;
		}
		m_data = dataNode;

		return true;
	}

	const bool VEDADataFileBase::init(const VEDAFile & parentFile, const std::string & name)
	{
		return VEDAFile::init(parentFile, name);
	}

	std::shared_ptr<SSUtils::XML::Node> VEDADataFileBase::normalizeModelParameter(void) const
	{
		XSDNormalizer::XSDNormalizer normalizer(m_model);
		if (!normalizer.normalize())
		{
			return nullptr;
		}

		return normalizer.getRoot();
	}
};
