#pragma once

#include <QtWidgets/QFrame>
#include <memory>
#include "VEDAModelView.h"
#include "VEDADataView.h"
#include "VEDAAnalysisView.h"

namespace VEDA
{
	class VEDAMainView : public QFrame
	{
		Q_OBJECT;

	public:
		enum class Type
		{
			Home,
			PublicModel,
			Model,
			Data,
			Analysis,
			ReportConfiguration,
			ReportData
		};

	public:
		explicit VEDAMainView(QWidget *parent = nullptr);
		VEDAMainView(const VEDAMainView &ano) = delete;
		VEDAMainView(VEDAMainView &&ano) = delete;
		VEDAMainView &operator=(const VEDAMainView &rhs) = delete;
		VEDAMainView &operator=(VEDAMainView &&rhs) = delete;
		~VEDAMainView(void) = default;

	signals:
		void loadingBegin(void);
		void loadingEnd(void);

	protected:
		void resizeEvent(QResizeEvent *event);

	public:
		void onModelOpened(VEDAModelFile *modelFile);
		void onModelRemove(std::shared_ptr<VEDAModelFile> modelFile);
		void onDataOpened(VEDADataFile *dataFile);
		void onDataRemove(std::shared_ptr<VEDADataFile> dataFile);
		void onDataAnalyzerOpened(VEDADataFile *dataFile);

	private:
		void onHomeViewLoadFinished(bool, QString);
		void onProjectClosed(bool, QString);
		void onLoadingBegin(void);
		void onLoadingEnd(void);

	private:
		void refreshCurrentView(QWidget *view);
		void closeCurrentView(void);

	private:
		VEDAFile *m_currFile;
		Type m_type;
		QWidget *m_currView;
	};
};
