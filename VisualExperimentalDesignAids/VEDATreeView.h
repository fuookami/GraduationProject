#pragma once

#include "VEDATreeViewItem.h"
#include "VEDAProjectHandler.h"
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <memory>
#include <map>

namespace VEDA
{
	class VEDATreeViewItemHandler;

	class VEDATreeView : public QTreeWidget
	{
		Q_OBJECT;

	public:
		explicit VEDATreeView(QWidget *parent = nullptr);
		VEDATreeView(const VEDATreeView &ano) = delete;
		VEDATreeView(VEDATreeView &&ano) = delete;
		VEDATreeView &operator=(const VEDATreeView &rhs) = delete;
		VEDATreeView &operator=(VEDATreeView &&rhs) = delete;
		~VEDATreeView(void) = default;

	private:
		void onOpenProjectFinished(bool, QString);
		void onCloseProjectFinished(bool, QString);

	private:
		std::shared_ptr<VEDAProjectHandler> m_projectHandler;
		std::shared_ptr<VEDATreeViewItemHandler> m_itemHandler;
	};

	class VEDATreeViewItemHandler : public QObject
	{
		Q_OBJECT;

	public:
		static const std::map<VEDAFile::Type, std::vector<std::vector<std::shared_ptr<QAction>>>> &Type2Action(void);

	public:
		static std::shared_ptr<VEDATreeViewItemHandler> getInstance(void);

	private:
		explicit VEDATreeViewItemHandler(void);
	public:
		VEDATreeViewItemHandler(const VEDATreeViewItemHandler &ano) = delete;
		VEDATreeViewItemHandler(VEDATreeViewItemHandler &&ano) = delete;
		VEDATreeViewItemHandler &operator=(const VEDATreeViewItemHandler &rhs) = delete;
		VEDATreeViewItemHandler &operator=(VEDATreeViewItemHandler &&rhs) = delete;
		~VEDATreeViewItemHandler(void) = default;

		void setCurrentItem(VEDATreeViewItem *currItem);
		std::shared_ptr<QMenu> getCurrentItemRightClickMenu(VEDATreeViewItem *currItem = nullptr);

	private:
		void initActions(void);
		static std::map<VEDAFile::Type, std::vector<std::vector<std::shared_ptr<QAction>>>> initActionMap(void);

	private:
		VEDATreeViewItem *m_currItem;

		std::shared_ptr<QAction> m_open;

		std::shared_ptr<QAction> m_initProcess;
		std::shared_ptr<QAction> m_importProcess;
		std::shared_ptr<QAction> m_initPublicModel;
		std::shared_ptr<QAction> m_importPublicModel;
		std::shared_ptr<QAction> m_initReport;
		std::shared_ptr<QAction> m_importReport;
		std::shared_ptr<QAction> m_closeProject;

		std::shared_ptr<QAction> m_initOperation;
		std::shared_ptr<QAction> m_importOperation;
		std::shared_ptr<QAction> m_initModel;
		std::shared_ptr<QAction> m_importModel;

		std::shared_ptr<QAction> m_initData;
		std::shared_ptr<QAction> m_importData;

		std::shared_ptr<QAction> m_analyse;

		std::shared_ptr<QAction> m_initReportConfiguration;
		std::shared_ptr<QAction> m_importReportConfiguration;

		std::shared_ptr<QAction> m_initReportData;
		std::shared_ptr<QAction> m_importReportData;

		std::shared_ptr<QAction> m_exportReport;

		std::shared_ptr<QAction> m_remove;
		std::shared_ptr<QAction> m_delete;
	};
};
