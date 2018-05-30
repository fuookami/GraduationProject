#include "VEDAProjectHandler.h"
#include "VEDAGlobal.h"
#include "SSUtils\FileUtils.h"
#include "SSUtils\XMLUtils.h"

namespace VEDA
{
	std::shared_ptr<VEDAProjectHandler> VEDAProjectHandler::getInstance(void)
	{
		static std::shared_ptr<VEDAProjectHandler> instance(new VEDAProjectHandler());
		return instance;
	}

	VEDAProjectHandler::VEDAProjectHandler(void)
		: m_currProject(nullptr)
	{
	}

	void VEDAProjectHandler::emitOpenProjectFinished(const bool ok, const QString & info)
	{
		emit openProjectFinished(ok, info);
	}

	void VEDAProjectHandler::emitCloseProjectFinished(const bool ok, const QString & info)
	{
		emit closeProjectFinished(ok, info);
	}

	const std::pair<bool, std::string> VEDAProjectHandler::initProject(const std::string & name, const std::string & path, const bool newDir)
	{
		return std::make_pair(false, std::string());
	}

	void VEDAProjectHandler::openProject(const std::string & projectFileUrl, const bool save)
	{

	}

	void VEDAProjectHandler::closeCurrProject(const bool save)
	{
	}

	void VEDAProjectHandler::saveCurrProject(void)
	{
	}
};
