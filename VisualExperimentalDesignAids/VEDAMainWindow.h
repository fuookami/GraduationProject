#pragma once

#include <QtWidgets/QMainWindow>
#include <memory>

class QWebEngineWidget;
namespace Ui
{
	class VEDAMainWindow;
};

namespace VEDA
{
	class VEDAMainWindow : public QMainWindow
	{
		Q_OBJECT;

		static const int MinimumWidth = 992 + 1; // desktop device width > 992px
		static const int MinimumHeight = MinimumWidth * 9 / 16;

	public:
		explicit VEDAMainWindow(QWidget * parent = nullptr);
		~VEDAMainWindow(void) = default;

	private:
		void onLoadFinished(bool);

	private:
		void registerContents(void);
		void initConnections(void);

	private:
		QWebEngineWidget * m_web;
		std::shared_ptr<Ui::VEDAMainWindow> m_ui;
	};
};
