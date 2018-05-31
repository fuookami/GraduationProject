#pragma once

#include <QtWidgets/QFrame>
#include <memory>

namespace VEDA
{
	class VEDAMainView : public QFrame
	{
		Q_OBJECT;

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

	private:
		void onHomeViewLoadFinished(bool, QString);
		void onLoadingBegin(void);
		void onLoadingEnd(void);

	private:
		QWidget *m_currView;
	};
};
