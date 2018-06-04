#pragma once

#include "SSUtils/GUI/QWebEngineWidget.h"
#include "VEDAModelFile.h"

namespace VEDA
{
	class VEDAModelViewInterface;

	class VEDAModelView : public SSUtils::GUI::QWebEngineWidget
	{
	public:
		explicit VEDAModelView(VEDAModelFile *file, QWidget *parent = nullptr);
		VEDAModelView(const VEDAModelView &ano) = delete;
		VEDAModelView(VEDAModelView &&ano) = delete;
		VEDAModelView &operator=(const VEDAModelView &rhs) = delete;
		VEDAModelView &operator=(VEDAModelView &&rhs) = delete;
		~VEDAModelView(void) = default;

	private:
		VEDAModelFile *m_file;
		std::shared_ptr<VEDAModelViewInterface> m_interface;
	};

	class VEDAModelViewInterface :public SSUtils::GUI::IWebEngineWidgetInterface<VEDAModelView>
	{
		Q_OBJECT;
		friend class VEDAModelView;

	private:
		explicit VEDAModelViewInterface(VEDAModelFile *file, VEDAModelView *widget);
		
	public:
		VEDAModelViewInterface(const VEDAModelViewInterface &ano) = delete;
		VEDAModelViewInterface(VEDAModelViewInterface &&ano) = delete;
		VEDAModelViewInterface &operator=(const VEDAModelViewInterface &rhs) = delete;
		VEDAModelViewInterface &operator=(VEDAModelViewInterface &&rhs) = delete;
		~VEDAModelViewInterface(void) = default;

	signals:
		void dataResponse(QString);

	public:
		Q_INVOKABLE void dataRequested(void);
		Q_INVOKABLE void dataSubmit(QJsonValue dataValue);

	public:
		VEDAModelFile *m_file;
	};
};
