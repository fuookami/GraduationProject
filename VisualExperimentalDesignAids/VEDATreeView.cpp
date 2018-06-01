#include "VEDATreeView.h"

namespace VEDA
{
	VEDATreeView::VEDATreeView(QWidget *parent)
		: QTreeWidget(parent), m_itemHandler(VEDATreeViewItemHandler::getInstance())
	{
		this->setHeaderHidden(true);
	}

	const std::map<VEDAFile::Type, std::vector<std::shared_ptr<QAction>>>& VEDATreeViewItemHandler::Type2Action(void)
	{
		static const std::map<VEDAFile::Type, std::vector<std::shared_ptr<QAction>>> ret = initActionMap();
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
		
		QString typeDisplay(QString::fromLocal8Bit(VEDAFile::Type2Display.left.find(m_currItem->type())->second.c_str()));
		m_remove->setText(QString::fromLocal8Bit("卸载%1").arg(typeDisplay));
		m_delete->setText(QString::fromLocal8Bit("删除%1").arg(typeDisplay));
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
			const auto &actions(actionsIt->second);
			for (const auto action : actions)
			{
				menu->addAction(action.get());
			}
		}

		return menu;
	}

	void VEDATreeViewItemHandler::initActions(void)
	{
		m_initProcess.reset(new QAction());
		m_initProcess->setText(QString::fromLocal8Bit("新建实验流程"));

		m_initPublicModel.reset(new QAction());
		m_initPublicModel->setText(QString::fromLocal8Bit("新建公共模型"));

		m_closeProject.reset(new QAction());
		m_closeProject->setText(QString::fromLocal8Bit("关闭实验项目"));

		m_remove.reset(new QAction());
		m_delete.reset(new QAction());
	}

	std::map<VEDAFile::Type, std::vector<std::shared_ptr<QAction>>> VEDATreeViewItemHandler::initActionMap(void)
	{
		auto instance(VEDATreeViewItemHandler::getInstance());

		std::map<VEDAFile::Type, std::vector<std::shared_ptr<QAction>>> ret =
		{
			std::make_pair(VEDAFile::Type::Project, std::vector<std::shared_ptr<QAction>>(
				{
					instance->m_initProcess, instance->m_initPublicModel, instance->m_closeProject
				})),
			std::make_pair(VEDAFile::Type::PublicModel, std::vector<std::shared_ptr<QAction>>(
				{
					instance->m_remove, instance->m_delete
				})),
			std::make_pair(VEDAFile::Type::Process, std::vector<std::shared_ptr<QAction>>(
				{
					instance->m_remove
				})),
			std::make_pair(VEDAFile::Type::Model, std::vector<std::shared_ptr<QAction>>(
				{
					instance->m_remove, instance->m_delete
				})),
			std::make_pair(VEDAFile::Type::Operation, std::vector<std::shared_ptr<QAction>>(
				{
					instance->m_remove
				})),
			std::make_pair(VEDAFile::Type::Data, std::vector<std::shared_ptr<QAction>>(
				{
					instance->m_remove, instance->m_delete
				})),
			std::make_pair(VEDAFile::Type::Report, std::vector<std::shared_ptr<QAction>>(
				{
					instance->m_remove
				})),
			std::make_pair(VEDAFile::Type::ReportConfiguration, std::vector<std::shared_ptr<QAction>>(
				{
					instance->m_remove
				})),
			std::make_pair(VEDAFile::Type::ReportData, std::vector<std::shared_ptr<QAction>>(
				{
					instance->m_remove, instance->m_delete
				}))
		};

		return ret;
	}
};
