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

		inline const std::shared_ptr<VEDATreeViewItemHandler> getHandler(void) const { return m_itemHandler; }

	private:
		void onOpenProjectFinished(bool, QString);
		void onCloseProjectFinished(bool, QString);

		void onItemPressed(QTreeWidgetItem *_item, int column);

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

		inline VEDATreeViewItem *getCurrentClickItem(void) const { return m_currClickItem; }
		void setCurrentClickItem(VEDATreeViewItem *currItem);

		inline VEDATreeViewItem *getCurrentRightClickItem(void) const { return m_currRightClickItem; }
		void setCurrentRightClickItem(VEDATreeViewItem *currItem) { m_currRightClickItem = currItem; }
		static std::shared_ptr<QMenu> getItemMenu(VEDATreeViewItem *item);

	private:
		void initActions(void);
		void initConnections(void);
		static std::map<VEDAFile::Type, std::vector<std::vector<std::shared_ptr<QAction>>>> initActionMap(void);

	signals:
		void modelOpened(VEDAModelFile *modelFile);
		void modelRemove(std::shared_ptr<VEDAModelFile> modelFile);
		void sig_modelRemove(VEDATreeViewItem *item);
		void dataOpened(VEDADataFile *dataFile);
		void dataRemove(std::shared_ptr<VEDADataFile> dataFile);
		void sig_dataRemove(VEDATreeViewItem *item);
		void dataAnalyzerOpened(VEDADataFile *dataFile);

	private:
		void onInitProcessSucceeded(std::shared_ptr<VEDAProcessFile>);
		void onInitModelSucceeded(std::shared_ptr<VEDAModelFile>);
		void onInitOperationSucceeded(std::shared_ptr<VEDAOperationFile>);
		void onInitDataSucceeded(std::shared_ptr<VEDADataFile>);

	public:
		void emitModelOpened(VEDAModelFile *modelFile);
		void emitModelRemove(VEDATreeViewItem *item);
		void emitDataOpened(VEDADataFile *dataFile);
		void emitDataRemove(VEDATreeViewItem *item);
		void emitDataAnalyzerOpened(VEDADataFile *dataFile);

	private:
		void onModelOpen(VEDATreeViewItem *item);
		void onModelRemove(VEDATreeViewItem *item);
		void onDataOpen(VEDATreeViewItem *item);
		void onDataRemove(VEDATreeViewItem *item);
		void onDataAnalyzerOpen(VEDATreeViewItem *item);

	private:
		void onOpenTriggered(void);

		void onRenameTrigggered(void);

		void onInitProcessTriggered(void);
		void onImportProcessTriggered(void);
		void onInitPublicModelTriggered(void);
		void onImportPublicModelTreiggered(void);
		void onInitReportTriggered(void);
		void onImportReportTriggered(void);
		void onCloseProjectTriggered(void);

		void onInitOperationTriggered(void);
		void onImportOperationTriggered(void);
		void onInitModelTriggered(void);
		void onImportModelTreiggered(void);

		void onInitDataTriggered(void);
		void onImportDataTriggered(void);

		void onAnalyseTriggered(void);

		void onInitReportConfigurationTriggered(void);
		void onImportReportConfigurationTriggered(void);

		void onInitReportDataTriggered(void);
		void onImportReportDataTriggered(void);

		void onExportReportTriggered(void);

		void onRemoveTriggered(void);
		void onDeleteTriggered(void);

	private:
		VEDATreeViewItem * m_currClickItem;
		VEDATreeViewItem *m_currRightClickItem;

		std::shared_ptr<QAction> m_open;

		std::shared_ptr<QAction> m_rename;

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
