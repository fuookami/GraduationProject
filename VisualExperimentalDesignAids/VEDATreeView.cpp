#include "VEDATreeView.h"
#include "VEDAInitProcessDialog.h"
#include "VEDAInitModelDialog.h"
#include "VEDAInitOperationDialog.h"
#include "VEDAInitDataDialog.h"
#include "SSUtils\GUI\QMessageBoxUtils.h"
#include <QtGui/QGuiApplication>
#include <thread>

namespace VEDA
{
	VEDATreeView::VEDATreeView(QWidget *parent)
		: QTreeWidget(parent), m_projectHandler(VEDAProjectHandler::getInstance()), m_itemHandler(VEDATreeViewItemHandler::getInstance())
	{
		this->setHeaderHidden(true);

		connect(m_projectHandler.get(), &VEDAProjectHandler::openProjectFinished, this, &VEDATreeView::onOpenProjectFinished);
		connect(m_projectHandler.get(), &VEDAProjectHandler::closeProjectFinished, this, &VEDATreeView::onCloseProjectFinished);

		connect(this, &QTreeWidget::itemPressed, this, &VEDATreeView::onItemPressed);
	}

	void VEDATreeView::onOpenProjectFinished(bool ok, QString url)
	{
		auto currProject(m_projectHandler->currProject());
		auto projectItem(VEDATreeViewItem::generateProjectItem(currProject));
		this->addTopLevelItem(projectItem);
	}

	void VEDATreeView::onCloseProjectFinished(bool ok, QString url)
	{
		this->clear();
		m_itemHandler->setCurrentClickItem(nullptr);
		m_itemHandler->setCurrentRightClickItem(nullptr);
	}

	void VEDATreeView::onItemPressed(QTreeWidgetItem * _item, int column)
	{
		if (QGuiApplication::mouseButtons() & Qt::LeftButton)
		{
			auto current(dynamic_cast<VEDATreeViewItem *>(_item));
			m_itemHandler->setCurrentClickItem(current);
		}
		else if (QGuiApplication::mouseButtons() & Qt::RightButton)
		{
			auto item(dynamic_cast<VEDATreeViewItem *>(_item));
			m_itemHandler->setCurrentRightClickItem(item);

			auto menu(VEDATreeViewItemHandler::getItemMenu(item));
			menu->exec(QCursor::pos());
		}
	}

	const std::map<VEDAFile::Type, std::vector<std::vector<std::shared_ptr<QAction>>>>& VEDATreeViewItemHandler::Type2Action(void)
	{
		static const std::map<VEDAFile::Type, std::vector<std::vector<std::shared_ptr<QAction>>>> ret = initActionMap();
		return ret;
	}

	std::shared_ptr<VEDATreeViewItemHandler> VEDATreeViewItemHandler::getInstance(void)
	{
		static std::shared_ptr<VEDATreeViewItemHandler> ret(new VEDATreeViewItemHandler());
		return ret;
	}

	VEDATreeViewItemHandler::VEDATreeViewItemHandler(void)
		: QObject(nullptr)
	{
		initActions();
	}

	void VEDATreeViewItemHandler::setCurrentClickItem(VEDATreeViewItem * currItem)
	{
		m_currClickItem = currItem;

		switch (m_currClickItem->type())
		{
		case VEDAFile::Type::PublicModel:
			break;
		case VEDAFile::Type::Model:
			onModelOpen(currItem);
			break;
		case VEDAFile::Type::Data:
			onDataOpen(currItem);
			break;
		case VEDAFile::Type::ReportConfiguration:
			break;
		case VEDAFile::Type::ReportData:
			break;
		case VEDAFile::Type::Project:
		case VEDAFile::Type::Process:
		case VEDAFile::Type::Operation:
		case VEDAFile::Type::Report:
		default:
			break;
		}
	}

	std::shared_ptr<QMenu> VEDATreeViewItemHandler::getItemMenu(VEDATreeViewItem * item)
	{
		static auto instance(getInstance());

		QString typeDisplay(QString::fromLocal8Bit(VEDAFile::Type2Display.left.find(item->type())->second.c_str()));
		instance->m_remove->setText(QString::fromLocal8Bit("卸载%1").arg(typeDisplay));
		instance->m_delete->setText(QString::fromLocal8Bit("删除%1").arg(typeDisplay));

		std::shared_ptr<QMenu> menu(new QMenu());
		auto actionsIt(Type2Action().find(item->type()));
		if (actionsIt != Type2Action().cend())
		{
			const auto &groups(actionsIt->second);
			for (const auto &group : groups)
			{
				for (const auto action : group)
				{
					menu->addAction(action.get());
				}
				menu->addSeparator();
			}
		}

		return menu;
	}

	void VEDATreeViewItemHandler::initActions(void)
	{
		m_open.reset(new QAction());
		m_open->setText(QString::fromLocal8Bit("打开"));
		connect(m_open.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onOpenTriggered);

		m_rename.reset(new QAction());
		m_rename->setText(QString::fromLocal8Bit("重命名"));
		connect(m_rename.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onRenameTrigggered);

		{
			m_initProcess.reset(new QAction());
			m_initProcess->setText(QString::fromLocal8Bit("新建实验流程"));
			connect(m_initProcess.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onInitProcessTriggered);

			m_importProcess.reset(new QAction());
			m_importProcess->setText(QString::fromLocal8Bit("添加现有实验流程"));
			connect(m_importProcess.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onImportProcessTriggered);

			m_initPublicModel.reset(new QAction());
			m_initPublicModel->setText(QString::fromLocal8Bit("新建公共模型"));
			connect(m_initPublicModel.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onInitPublicModelTriggered);

			m_importPublicModel.reset(new QAction());
			m_importPublicModel->setText(QString::fromLocal8Bit("添加现有公共模型"));
			connect(m_importPublicModel.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onImportPublicModelTreiggered);

			m_initReport.reset(new QAction());
			m_initReport->setText(QString::fromLocal8Bit("新建实验报告"));
			connect(m_initReport.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onInitReportTriggered);

			m_importReport.reset(new QAction());
			m_importReport->setText(QString::fromLocal8Bit("添加现有实验报告"));
			connect(m_importReport.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onImportReportTriggered);

			m_closeProject.reset(new QAction());
			m_closeProject->setText(QString::fromLocal8Bit("关闭实验项目"));
			connect(m_closeProject.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onCloseProjectTriggered);
		}

		{
			m_initOperation.reset(new QAction());
			m_initOperation->setText(QString::fromLocal8Bit("新建实验操作"));
			connect(m_initOperation.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onInitOperationTriggered);

			m_importOperation.reset(new QAction());
			m_importOperation->setText(QString::fromLocal8Bit("添加现有实验操作"));
			connect(m_importOperation.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onImportOperationTriggered);

			m_initModel.reset(new QAction());
			m_initModel->setText(QString::fromLocal8Bit("新建实验因素数据模型"));
			connect(m_initModel.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onInitModelTriggered);

			m_importModel.reset(new QAction());
			m_importModel->setText(QString::fromLocal8Bit("添加现有实验因素数据模型"));
			connect(m_importModel.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onImportModelTreiggered);
		}

		{
			m_initData.reset(new QAction());
			m_initData->setText(QString::fromLocal8Bit("新建实验数据"));
			connect(m_initData.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onInitDataTriggered);

			m_importData.reset(new QAction());
			m_importData->setText(QString::fromLocal8Bit("添加现有实验数据"));
			connect(m_importData.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onImportDataTriggered);
		}

		{
			m_analyse.reset(new QAction());
			m_analyse->setText(QString::fromLocal8Bit("分析实验数据"));
			connect(m_analyse.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onAnalyseTriggered);
		}
		
		{
			m_initReportConfiguration.reset(new QAction());
			m_initReportConfiguration->setText(QString::fromLocal8Bit("新建实验报告设计"));
			connect(m_initReportConfiguration.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onInitReportConfigurationTriggered);

			m_importReportConfiguration.reset(new QAction());
			m_importReportConfiguration->setText(QString::fromLocal8Bit("添加现有实验报告设计"));
			connect(m_importReportConfiguration.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onImportReportConfigurationTriggered);
		}

		{
			m_initReportData.reset(new QAction());
			m_initReportData->setText(QString::fromLocal8Bit("新建实验报告数据"));
			connect(m_initReportData.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onInitReportDataTriggered);

			m_importReportData.reset(new QAction());
			m_importReportData->setText(QString::fromLocal8Bit("添加现有实验报告数据"));
			connect(m_importReportData.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onImportReportDataTriggered);
		}

		m_exportReport.reset(new QAction());
		m_exportReport->setText(QString::fromLocal8Bit("导出实验报告"));
		connect(m_exportReport.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onExportReportTriggered);

		m_remove.reset(new QAction());
		connect(m_remove.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onRemoveTriggered);
		m_delete.reset(new QAction());
		connect(m_delete.get(), &QAction::triggered, this, &VEDATreeViewItemHandler::onDeleteTriggered);
	}

	void VEDATreeViewItemHandler::initConnections(void)
	{
		connect(this, &VEDATreeViewItemHandler::sig_modelRemove, this, &VEDATreeViewItemHandler::onModelRemove);
		connect(this, &VEDATreeViewItemHandler::sig_dataRemove, this, &VEDATreeViewItemHandler::onDataRemove);
	}

	std::map<VEDAFile::Type, std::vector<std::vector<std::shared_ptr<QAction>>>> VEDATreeViewItemHandler::initActionMap(void)
	{
		auto instance(VEDATreeViewItemHandler::getInstance());

		std::map<VEDAFile::Type, std::vector<std::vector<std::shared_ptr<QAction>>>> ret =
		{
			std::make_pair(VEDAFile::Type::Project, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_initProcess, instance->m_initPublicModel }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_importProcess, instance->m_importPublicModel }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_initReport }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_importReport }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_rename }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_closeProject })
				})),
			std::make_pair(VEDAFile::Type::PublicModel, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_open }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_rename }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove, instance->m_delete })
				})),
			std::make_pair(VEDAFile::Type::Process, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_initOperation, instance->m_initModel }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_importOperation, instance->m_importModel }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_rename }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove })
				})),
			std::make_pair(VEDAFile::Type::Model, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_open }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_rename }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove, instance->m_delete })
				})),
			std::make_pair(VEDAFile::Type::Operation, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_initData }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_importData }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_rename }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove })
				})),
			std::make_pair(VEDAFile::Type::Data, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_open }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_analyse }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_rename }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove, instance->m_delete })
				})),
			std::make_pair(VEDAFile::Type::Report, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_initReportConfiguration }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_importReportConfiguration }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_rename }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove })
				})),
			std::make_pair(VEDAFile::Type::ReportConfiguration, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_open }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_initReportData }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_importReportData }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_rename }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove })
				})),
			std::make_pair(VEDAFile::Type::ReportData, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{

					std::vector<std::shared_ptr<QAction>>({ instance->m_open }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_exportReport }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_rename }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove, instance->m_delete })
				}))
		};

		return ret;
	}

	void VEDATreeViewItemHandler::onInitProcessSucceeded(std::shared_ptr<VEDAProcessFile> processFile)
	{
		auto processItem(VEDATreeViewItem::generateProcessItem(m_currRightClickItem, processFile));
		m_currRightClickItem->addChild(processItem);
		m_currRightClickItem->setExpanded(true);
	}

	void VEDATreeViewItemHandler::onInitModelSucceeded(std::shared_ptr<VEDAModelFile> modelFile)
	{
		auto modelItem(VEDATreeViewItem::genearteModelItem(m_currRightClickItem, modelFile->getUrl(), modelFile.get()));
		m_currRightClickItem->insertChild(0, modelItem);
		m_currRightClickItem->setExpanded(true);
	}

	void VEDATreeViewItemHandler::onInitOperationSucceeded(std::shared_ptr<VEDAOperationFile> operationFile)
	{
		auto operationItem(VEDATreeViewItem::generateOperationItem(m_currRightClickItem, operationFile));
		m_currRightClickItem->addChild(operationItem);
		m_currRightClickItem->setExpanded(true);
	}

	void VEDATreeViewItemHandler::onInitDataSucceeded(std::shared_ptr<VEDADataFile> dataFile)
	{
		auto dataItem(VEDATreeViewItem::generateDataItem(m_currRightClickItem, dataFile->getUrl(), dataFile.get()));
		m_currRightClickItem->addChild(dataItem);
		m_currRightClickItem->setExpanded(true);
	}

	void VEDATreeViewItemHandler::emitModelOpened(VEDAModelFile * modelFile)
	{
		emit modelOpened(modelFile);
	}

	void VEDATreeViewItemHandler::emitModelRemove(VEDATreeViewItem * item)
	{
		emit sig_modelRemove(item);
	}

	void VEDATreeViewItemHandler::emitDataOpened(VEDADataFile * dataFile)
	{
		emit dataOpened(dataFile);
	}

	void VEDATreeViewItemHandler::emitDataRemove(VEDATreeViewItem * item)
	{
		emit sig_dataRemove(item);
	}

	void VEDATreeViewItemHandler::emitDataAnalyzerOpened(VEDADataFile * dataFile)
	{
		emit dataAnalyzerOpened(dataFile);
	}

	void VEDATreeViewItemHandler::onModelOpen(VEDATreeViewItem * item)
	{
		auto parent = dynamic_cast<VEDATreeViewItem *>(item->parent());
		auto projectHandler(VEDAProjectHandler::getInstance());

		std::thread([this, item, parent, projectHandler]()
		{
			projectHandler->emitLoadingBegin();

			auto processFile(dynamic_cast<VEDAProcessFile *>(parent->file()));
			if (item->file() == nullptr)
			{
				if (processFile->getModelFile() != nullptr)
				{
					item->setFile(processFile->getModelFile().get());
				}
				else
				{
					auto model = projectHandler->openModel(processFile);
					if (model == nullptr)
					{
						this->emitModelRemove(item);
					}
					else
					{
						item->setFile(model.get());
					}
				}
			}
			if (item->file() != nullptr)
			{
				this->emitModelOpened(dynamic_cast<VEDAModelFile *>(item->file()));
			}

			projectHandler->emitLoadingEnd();
		}).detach();
	}

	void VEDATreeViewItemHandler::onModelRemove(VEDATreeViewItem * item)
	{
		if (item->file() != nullptr)
		{
			auto temp = dynamic_cast<VEDAModelFile *>(item->file());
			auto process = temp->getParent();
			auto model = process->getModelFile();

			process->setModelFileUrl("");
			process->setModelFile(nullptr);
			process->save();

			emit modelRemove(model);
		}
		delete item;
	}

	void VEDATreeViewItemHandler::onDataOpen(VEDATreeViewItem * item)
	{
		auto parent = dynamic_cast<VEDATreeViewItem *>(item->parent());
		auto projectHandler(VEDAProjectHandler::getInstance());

		std::thread([this, item, parent, projectHandler]()
		{
			projectHandler->emitLoadingBegin();

			auto operationFile(dynamic_cast<VEDAOperationFile *>(parent->file()));
			std::string url(std::string(item->url().toLocal8Bit()));
			auto relativeUrl(SSUtils::File::getRelativeUrlOfPath(operationFile->getPath(), url));
			if (item->file() == nullptr)
			{
				if (operationFile->getLoadedDataFiles().find(relativeUrl) != operationFile->getLoadedDataFiles().cend())
				{
					item->setFile(operationFile->getLoadedDataFiles().find(relativeUrl)->second.get());
				}
				else
				{
					auto data = projectHandler->openData(operationFile, url);
					if (data == nullptr)
					{
						this->emitDataRemove(item);
					}
					else
					{
						item->setFile(data.get());
					}
				}
			}
			if (item->file() != nullptr)
			{
				this->emitDataOpened(dynamic_cast<VEDADataFile *>(item->file()));
			}

			projectHandler->emitLoadingEnd();
		}).detach();
	}

	void VEDATreeViewItemHandler::onDataRemove(VEDATreeViewItem * item)
	{
		if (item->file() != nullptr)
		{
			auto temp = dynamic_cast<VEDADataFile *>(item->file());
			auto operation = temp->getParent();
			auto relativeUrl(SSUtils::File::getRelativeUrlOfPath(operation->getPath(), temp->getUrl()));
			auto data = operation->getLoadedDataFiles().find(relativeUrl)->second;

			operation->getDataFileUrls().erase(relativeUrl);
			operation->getLoadedDataFiles().erase(relativeUrl);
			operation->save();
			emit dataRemove(data);
		}
		delete item;
	}

	void VEDATreeViewItemHandler::onDataAnalyzerOpen(VEDATreeViewItem * item)
	{
		auto parent = dynamic_cast<VEDATreeViewItem *>(item->parent());
		auto projectHandler(VEDAProjectHandler::getInstance());

		std::thread([this, item, parent, projectHandler]()
		{
			projectHandler->emitLoadingBegin();

			auto operationFile(dynamic_cast<VEDAOperationFile *>(parent->file()));
			std::string url(std::string(item->url().toLocal8Bit()));
			auto relativeUrl(SSUtils::File::getRelativeUrlOfPath(operationFile->getPath(), url));
			if (item->file() == nullptr)
			{
				if (operationFile->getLoadedDataFiles().find(relativeUrl) != operationFile->getLoadedDataFiles().cend())
				{
					item->setFile(operationFile->getLoadedDataFiles().find(relativeUrl)->second.get());
				}
				else
				{
					auto data = projectHandler->openData(operationFile, url);
					if (data == nullptr)
					{
						this->emitDataRemove(item);
					}
					else
					{
						item->setFile(data.get());
					}
				}
			}
			if (item->file() != nullptr)
			{
				this->emitDataAnalyzerOpened(dynamic_cast<VEDADataFile *>(item->file()));
			}

			projectHandler->emitLoadingEnd();
		}).detach();
	}

	void VEDATreeViewItemHandler::onOpenTriggered(void)
	{
		switch (m_currRightClickItem->type())
		{
		case VEDAFile::Type::PublicModel:
			break;
		case VEDAFile::Type::Model:
			onModelOpen(m_currRightClickItem);
			break;
		case VEDAFile::Type::Data:
			onDataOpen(m_currRightClickItem);
			break;
		case VEDAFile::Type::ReportConfiguration:
			break;
		case VEDAFile::Type::ReportData:
			break;
		case VEDAFile::Type::Project:
		case VEDAFile::Type::Process:
		case VEDAFile::Type::Operation:
		case VEDAFile::Type::Report:
		default:
			break;
		}
	}

	void VEDATreeViewItemHandler::onRenameTrigggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onInitProcessTriggered(void)
	{
		auto dialog(VEDAInitProcessDialog::getInstance(dynamic_cast<VEDAProjectFile *>(m_currRightClickItem->file())));
		connect(dialog->interface().get(), &VEDAInitProcessDialogInterface::initProcessSucceeded, this, &VEDATreeViewItemHandler::onInitProcessSucceeded);
		dialog->show();
	}

	void VEDATreeViewItemHandler::onImportProcessTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onInitPublicModelTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onImportPublicModelTreiggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onInitReportTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onImportReportTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onCloseProjectTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onInitOperationTriggered(void)
	{
		auto dialog(VEDAInitOperationDialog::getInstance(dynamic_cast<VEDAProcessFile *>(m_currRightClickItem->file())));
		connect(dialog->interface().get(), &VEDAInitOperationDialogInterface::initOperationSucceeded, this, &VEDATreeViewItemHandler::onInitOperationSucceeded);
		dialog->show();
	}

	void VEDATreeViewItemHandler::onImportOperationTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onInitModelTriggered(void)
	{
		auto processFile(dynamic_cast<VEDAProcessFile *>(m_currRightClickItem->file()));
		if (!processFile->getModelFileUrl().empty())
		{
			SSUtils::GUI::QMessageBoxUtils::information(QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("%1下已有实验因素数据模型").arg(QString::fromLocal8Bit(processFile->getName().c_str())));
			return;
		}

		auto dialog(VEDAInitModelDialog::getInstance(processFile));
		connect(dialog->interface().get(), &VEDAInitModelDialogInterface::initModelSucceeded, this, &VEDATreeViewItemHandler::onInitModelSucceeded);
		dialog->show();
	}

	void VEDATreeViewItemHandler::onImportModelTreiggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onInitDataTriggered(void)
	{
		auto dialog(VEDAInitDataDialog::getInstance(dynamic_cast<VEDAOperationFile *>(m_currRightClickItem->file())));
		connect(dialog->interface().get(), &VEDAInitDataDialogInterface::initDataSucceeded, this, &VEDATreeViewItemHandler::onInitDataSucceeded);
		dialog->show();
	}

	void VEDATreeViewItemHandler::onImportDataTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onAnalyseTriggered(void)
	{
		onDataAnalyzerOpen(m_currRightClickItem);
	}

	void VEDATreeViewItemHandler::onInitReportConfigurationTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onImportReportConfigurationTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onInitReportDataTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onImportReportDataTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onExportReportTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onRemoveTriggered(void)
	{
		// to do
	}

	void VEDATreeViewItemHandler::onDeleteTriggered(void)
	{
		// to do
	}
};
