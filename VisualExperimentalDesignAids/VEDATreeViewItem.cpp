#include "VEDATreeViewItem.h"
#include "SSUtils/FileUtils.h"
#include "VEDAProjectFile.h"
#include "VEDAProcessFile.h"

namespace VEDA
{
	VEDATreeViewItem * VEDATreeViewItem::generateProjectItem(std::shared_ptr<VEDAProjectFile> projectFile)
	{
		auto projectItem(new VEDATreeViewItem(projectFile->getUrl(), projectFile->getType(), projectFile.get()));
		if (!projectFile->getPublicModelFileUrl().empty())
		{
			auto publicModelItem(new VEDATreeViewItem(projectItem, SSUtils::File::getSystemNativePath(projectFile->getPath() + projectFile->getPublicModelFileUrl()), VEDAFile::Type::PublicModel, nullptr));
			projectItem->addChild(publicModelItem);
		}
		return projectItem;
	}

	VEDATreeViewItem * VEDATreeViewItem::generateProcessItem(VEDATreeViewItem *projectItem, std::shared_ptr<VEDAProcessFile> processFile)
	{
		auto processItem(new VEDATreeViewItem(projectItem, processFile->getUrl(), processFile->getType(), processFile.get()));
		if (!processFile->getModelFileUrl().empty())
		{
			auto modelItem(new VEDATreeViewItem(processItem, SSUtils::File::getSystemNativePath(processFile->getPath() + processFile->getModelFileUrl()), VEDAFile::Type::Model, nullptr));
			processItem->addChild(modelItem);
		}
		return processItem;
	}

	VEDATreeViewItem::VEDATreeViewItem(const std::string & url, const VEDAFile::Type type, VEDAFile * file)
		: VEDATreeViewItem(nullptr, url, type, file)
	{
	}

	VEDATreeViewItem::VEDATreeViewItem(QTreeWidgetItem * parent, const std::string & url, const VEDAFile::Type type, VEDAFile * file)
		: QTreeWidgetItem(parent), 
		m_url(QString::fromLocal8Bit(url.c_str())),
		m_name(QString::fromLocal8Bit(SSUtils::File::getFileNameOfUrl(url).c_str())), 
		m_type(type), m_file(file)
	{
		this->setText(0, m_name);
		this->setToolTip(0, m_url);
	}
};
