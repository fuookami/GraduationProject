#pragma once

#include <QtWidgets/QMainWindow>
#include <memory>

namespace Ui
{
	class VEDAMainWindow;
};

namespace VEDA
{
	class VEDAProjectHandler;
	class VEDAMainWidget;

	class VEDAMainWindow : public QMainWindow
	{
		Q_OBJECT;

		static const int MinimumWidth; // desktop device width > 992px
		static const int MinimumHeight;

	public:
		static std::shared_ptr<VEDAMainWindow> getInstance(void);

	private:
		explicit VEDAMainWindow(void);

	public:
		VEDAMainWindow(const VEDAMainWindow &ano) = delete;
		VEDAMainWindow(VEDAMainWindow &&ano) = delete;
		VEDAMainWindow &operator=(const VEDAMainWindow &rhs) = delete;
		VEDAMainWindow &operator=(VEDAMainWindow &&rhs) = delete;
		~VEDAMainWindow(void) = default;

	private:
		void initLoadingWidget(void);
		void initConnections(void);
		void initOthers(void);

	protected:
		void resizeEvent(QResizeEvent *event);

	public:
		static void onLoadingBegin(void);
		static void onLoadingEnd(void);
		static void onOpenProjectFinished(bool, QString);

	private:
		std::shared_ptr<Ui::VEDAMainWindow> m_ui;
		std::shared_ptr<VEDAProjectHandler> m_projectHandler;
		VEDAMainWidget *m_mainWidget;
	};
};
