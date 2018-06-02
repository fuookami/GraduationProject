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
			auto publicModelItem(generatePublicModelItem(projectItem, SSUtils::File::getSystemNativePath(projectFile->getPath() + projectFile->getPublicModelFileUrl()), nullptr));
			projectItem->addChild(publicModelItem);
		}

		for (const auto &pair : projectFile->getLoadedDataFiles())
		{
			auto currProcess(pair.second);
			auto processItem(VEDATreeViewItem::generateProcessItem(projectItem, currProcess));
			projectItem->addChild(processItem);
		}
		return projectItem;
	}

	VEDATreeViewItem * VEDATreeViewItem::generatePublicModelItem(VEDATreeViewItem * projectItem, const std::string & url, VEDAFile * file)
	{
		return new VEDATreeViewItem(projectItem, url, VEDAFile::Type::PublicModel, file);
	}

	VEDATreeViewItem * VEDATreeViewItem::generateProcessItem(VEDATreeViewItem *projectItem, std::shared_ptr<VEDAProcessFile> processFile)
	{
		auto processItem(new VEDATreeViewItem(projectItem, processFile->getUrl(), processFile->getType(), processFile.get()));
		if (!processFile->getModelFileUrl().empty())
		{
			auto modelItem(genearteModelItem(processItem, SSUtils::File::getSystemNativePath(processFile->getPath() + processFile->getModelFileUrl()), nullptr));
			processItem->addChild(modelItem);
		}

		for (const auto &pair : processFile->getLoadedDataFiles())
		{
			auto currOperation(pair.second);
			auto operationItem(VEDATreeViewItem::generateOperationItem(processItem, currOperation));
			processItem->addChild(operationItem);
		}
		return processItem;
	}

	VEDATreeViewItem * VEDATreeViewItem::genearteModelItem(VEDATreeViewItem * processItem, const std::string & url, VEDAFile * file)
	{
		return new VEDATreeViewItem(processItem, url, VEDAFile::Type::Model, file);
	}

	VEDATreeViewItem * VEDATreeViewItem::generateOperationItem(VEDATreeViewItem * processItem, std::shared_ptr<VEDAOperationFile> operationFile)
	{
		auto operationItem(new VEDATreeViewItem(processItem, operationFile->getUrl(), operationFile->getType(), operationFile.get()));
		
		for (const auto &url : operationFile->getDataFileUrls())
		{
			auto dataItem(VEDATreeViewItem::generateDataItem(operationItem, SSUtils::File::getSystemNativePath(operationFile->getPath() + url), nullptr));
			operationItem->addChild(dataItem);
		}
		return operationItem;
	}

	VEDATreeViewItem * VEDATreeViewItem::generateDataItem(VEDATreeViewItem * operationItem, const std::string & url, VEDAFile * file)
	{
		return new VEDATreeViewItem(operationItem, url, VEDAFile::Type::Data, file);
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
