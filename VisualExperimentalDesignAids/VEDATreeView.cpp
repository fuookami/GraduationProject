#include "VEDATreeView.h"

namespace VEDA
{
	VEDATreeView::VEDATreeView(QWidget *parent)
		: QTreeWidget(parent), m_projectHandler(VEDAProjectHandler::getInstance()), m_itemHandler(VEDATreeViewItemHandler::getInstance())
	{
		this->setHeaderHidden(true);

		connect(m_projectHandler.get(), &VEDAProjectHandler::openProjectFinished, this, &VEDATreeView::onOpenProjectFinished);
		connect(m_projectHandler.get(), &VEDAProjectHandler::closeProjectFinished, this, &VEDATreeView::onCloseProjectFinished);
	}

	void VEDATreeView::onOpenProjectFinished(bool ok, QString url)
	{
		// to do
	}

	void VEDATreeView::onCloseProjectFinished(bool ok, QString url)
	{
		this->clear();
		m_itemHandler->setCurrentItem(nullptr);
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

	void VEDATreeViewItemHandler::setCurrentItem(VEDATreeViewItem * currItem)
	{
		m_currItem = currItem;
		
		if (m_currItem != nullptr)
		{
			QString typeDisplay(QString::fromLocal8Bit(VEDAFile::Type2Display.left.find(m_currItem->type())->second.c_str()));
			m_remove->setText(QString::fromLocal8Bit("卸载%1").arg(typeDisplay));
			m_delete->setText(QString::fromLocal8Bit("删除%1").arg(typeDisplay));
		}
	}

	std::shared_ptr<QMenu> VEDATreeViewItemHandler::getCurrentItemRightClickMenu(VEDATreeViewItem * currItem)
	{
		std::shared_ptr<QMenu> menu(new QMenu());
		if (currItem != nullptr && m_currItem != currItem)
		{
			setCurrentItem(currItem);
		}

		auto actionsIt(Type2Action().find(m_currItem->type()));
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

		{
			m_initProcess.reset(new QAction());
			m_initProcess->setText(QString::fromLocal8Bit("新建实验流程"));

			m_importProcess.reset(new QAction());
			m_importProcess->setText(QString::fromLocal8Bit("添加现有实验流程"));

			m_initPublicModel.reset(new QAction());
			m_initPublicModel->setText(QString::fromLocal8Bit("新建公共模型"));

			m_importPublicModel.reset(new QAction());
			m_importPublicModel->setText(QString::fromLocal8Bit("添加现有公共模型"));

			m_initReport.reset(new QAction());
			m_initReport->setText(QString::fromLocal8Bit("新建实验报告"));

			m_importReport.reset(new QAction());
			m_importReport->setText(QString::fromLocal8Bit("添加现有实验报告"));

			m_closeProject.reset(new QAction());
			m_closeProject->setText(QString::fromLocal8Bit("关闭实验项目"));
		}

		{
			m_initOperation.reset(new QAction());
			m_initOperation->setText(QString::fromLocal8Bit("新建实验操作"));

			m_importOperation.reset(new QAction());
			m_importOperation->setText(QString::fromLocal8Bit("添加现有实验操作"));

			m_initModel.reset(new QAction());
			m_initModel->setText(QString::fromLocal8Bit("新建实验因素数据模型"));

			m_importModel.reset(new QAction());
			m_importModel->setText(QString::fromLocal8Bit("添加现有实验因素数据模型"));
		}

		{
			m_initData.reset(new QAction());
			m_initData->setText(QString::fromLocal8Bit("新建实验数据"));

			m_importData.reset(new QAction());
			m_importData->setText(QString::fromLocal8Bit("添加现有实验数据"));
		}

		{
			m_analyse.reset(new QAction());
			m_analyse->setText(QString::fromLocal8Bit("分析实验数据"));
		}
		
		{
			m_initReportConfiguration.reset(new QAction());
			m_initReportConfiguration->setText(QString::fromLocal8Bit("新建实验报告设计"));

			m_importReportConfiguration.reset(new QAction());
			m_importReportConfiguration->setText(QString::fromLocal8Bit("添加现有实验报告设计"));
		}

		{
			m_initReportData.reset(new QAction());
			m_initReportData->setText(QString::fromLocal8Bit("新建实验报告数据"));

			m_importReportData.reset(new QAction());
			m_importReportData->setText(QString::fromLocal8Bit("添加现有实验报告数据"));
		}

		m_exportReport.reset(new QAction());
		m_exportReport->setText(QString::fromLocal8Bit("导出实验报告"));

		m_remove.reset(new QAction());
		m_delete.reset(new QAction());
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
					std::vector<std::shared_ptr<QAction>>({ instance->m_closeProject })
				})),
			std::make_pair(VEDAFile::Type::PublicModel, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_open }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove, instance->m_delete })
				})),
			std::make_pair(VEDAFile::Type::Process, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_initOperation, instance->m_initModel }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_importOperation, instance->m_importModel }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove })
				})),
			std::make_pair(VEDAFile::Type::Model, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_open }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove, instance->m_delete })
				})),
			std::make_pair(VEDAFile::Type::Operation, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_initData }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_importData }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove })
				})),
			std::make_pair(VEDAFile::Type::Data, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_open }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_analyse }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove, instance->m_delete })
				})),
			std::make_pair(VEDAFile::Type::Report, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_initReportConfiguration }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_importReportConfiguration }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove })
				})),
			std::make_pair(VEDAFile::Type::ReportConfiguration, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{
					std::vector<std::shared_ptr<QAction>>({ instance->m_open }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_initReportData }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_importReportData }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove })
				})),
			std::make_pair(VEDAFile::Type::ReportData, std::vector<std::vector<std::shared_ptr<QAction>>>(
				{

					std::vector<std::shared_ptr<QAction>>({ instance->m_open }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_exportReport }),
					std::vector<std::shared_ptr<QAction>>({ instance->m_remove, instance->m_delete })
				}))
		};

		return ret;
	}
};
