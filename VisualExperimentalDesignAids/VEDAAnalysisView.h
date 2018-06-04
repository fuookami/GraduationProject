#pragma once

#include "SSUtils/GUI/QWebEngineWidget.h"
#include "VEDADataFile.h"

namespace VEDA
{
	class VEDAAnalysisViewInterface;

	class VEDAAnalysisView : public SSUtils::GUI::QWebEngineWidget
	{
	public:
		explicit VEDAAnalysisView(VEDADataFile *file, QWidget *parent = nullptr);
		VEDAAnalysisView(const VEDAAnalysisView &ano) = delete;
		VEDAAnalysisView(VEDAAnalysisView &&ano) = delete;
		VEDAAnalysisView &operator=(const VEDAAnalysisView &rhs) = delete;
		VEDAAnalysisView &operator=(VEDAAnalysisView &&rhs) = delete;
		~VEDAAnalysisView(void) = default;

	private:
		VEDADataFile *m_file;
		std::shared_ptr<VEDAAnalysisViewInterface> m_interface;
	};

	class VEDAAnalysisViewInterface :public SSUtils::GUI::IWebEngineWidgetInterface<VEDAAnalysisView>
	{
		Q_OBJECT;
		friend class VEDAAnalysisView;

	private:
		explicit VEDAAnalysisViewInterface(VEDADataFile *file, VEDAAnalysisView *widget);

	public:
		VEDAAnalysisViewInterface(const VEDAAnalysisViewInterface &ano) = delete;
		VEDAAnalysisViewInterface(VEDAAnalysisViewInterface &&ano) = delete;
		VEDAAnalysisViewInterface &operator=(const VEDAAnalysisViewInterface &rhs) = delete;
		VEDAAnalysisViewInterface &operator=(VEDAAnalysisViewInterface &&rhs) = delete;
		~VEDAAnalysisViewInterface(void) = default;

	signals:
		void analyzerResponse(QString);
		void analysisResponse(QString);

	public:
		Q_INVOKABLE void analyzerRequested(void);
		Q_INVOKABLE void analysisRequested(QJsonValue analyzerValue);

	public:
		VEDADataFile *m_file;
	};
};
