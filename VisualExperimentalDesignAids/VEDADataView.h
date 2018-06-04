#pragma once

#include "SSUtils/GUI/QWebEngineWidget.h"
#include "VEDADataFile.h"

namespace VEDA
{
	class VEDADataViewInterface;

	class VEDADataView : public SSUtils::GUI::QWebEngineWidget
	{
	public:
		explicit VEDADataView(VEDADataFile *file, QWidget *parent = nullptr);
		VEDADataView(const VEDADataView &ano) = delete;
		VEDADataView(VEDADataView &&ano) = delete;
		VEDADataView &operator=(const VEDADataView &rhs) = delete;
		VEDADataView &operator=(VEDADataView &&rhs) = delete;
		~VEDADataView(void) = default;

	private:
		VEDADataFile * m_file;
		std::shared_ptr<VEDADataViewInterface> m_interface;
	};

	class VEDADataViewInterface :public SSUtils::GUI::IWebEngineWidgetInterface<VEDADataView>
	{
		Q_OBJECT;
		friend class VEDADataView;

	private:
		explicit VEDADataViewInterface(VEDADataFile *file, VEDADataView *widget);

	public:
		VEDADataViewInterface(const VEDADataViewInterface &ano) = delete;
		VEDADataViewInterface(VEDADataViewInterface &&ano) = delete;
		VEDADataViewInterface &operator=(const VEDADataViewInterface &rhs) = delete;
		VEDADataViewInterface &operator=(VEDADataViewInterface &&rhs) = delete;
		~VEDADataViewInterface(void) = default;

	signals:
		void dataResponse(QString);

	public:
		Q_INVOKABLE void dataRequested(void);
		Q_INVOKABLE void dataSubmit(QJsonValue dataValue);

	public:
		VEDADataFile * m_file;
	};
};
