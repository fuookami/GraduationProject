#pragma once

#include <QtWidgets/QWidget>
#include <QtGui/QCloseEvent>

class QWebEngineView;
class QWebEngineWidget;

namespace NSSPCDCreator
{
	class IWebEngineDialogWidget : public QWidget
	{
		Q_OBJECT;

		static const int MinimumWidth = 992 + 21; // desktop device width > 992px + 20px
		static const int MinimumHeight = MinimumWidth * 9 / 16;

	public:
		explicit IWebEngineDialogWidget(const QString &guiEntrance, QWidget *parent = nullptr);
		virtual ~IWebEngineDialogWidget(void) = default;

	protected:
		void resizeEvent(QResizeEvent *event) override;
		virtual void initGUI(void) = 0;
		virtual void registerContents(void) = 0;

		void showEvent(QShowEvent *event);
		void closeEvent(QCloseEvent *event);

	private:
		void onLoadFinished(bool);

	protected:
		QWebEngineWidget * m_webWidget;
		QWebEngineView * m_web;
		QString m_guiEntrance;
	};
};
