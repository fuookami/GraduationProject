#pragma once

#include <QtWidgets/QMainWindow>
#include "QWebEngineWidget.h"
#include <memory>

namespace Ui
{
	class VEDAMainWindow;
};

namespace VEDA
{
	class VEDAProjectHandler;

	class VEDAMainWindow : public QMainWindow
	{
		Q_OBJECT;

		static const int MinimumWidth = 992 + 1; // desktop device width > 992px
		static const int MinimumHeight = MinimumWidth * 9 / 16;

	public:
		static std::shared_ptr<VEDAMainWindow> getInstance(void);

	private:
		explicit VEDAMainWindow(void);

	public:
		VEDAMainWindow(const VEDAMainWindow &ano) = delete;
		VEDAMainWindow(VEDAMainWindow &&ano) = delete;
		~VEDAMainWindow(void) = default;

	public:
		inline QWebEngineView *web(void) { return m_web->view(); }

	private:
		void onLoadFinished(bool);

	private:
		void registerContents(void);
		void initConnections(void);

	private:
		QWebEngineWidget * m_web;
		std::shared_ptr<Ui::VEDAMainWindow> m_ui;
		std::shared_ptr<VEDAProjectHandler> m_projectHandler;
	};
};
