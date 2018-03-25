#pragma once

#include "QWebEngineWidget.h"
#include <QtCore/QObject>
#include <QtWidgets/QWidget>
#include <QtGui/QCloseEvent>

class IWebEngineDialogWidget;
template <typename T, typename std::enable_if<std::is_base_of<IWebEngineDialogWidget, T>::value, T>::type* = nullptr>
class IWebEngineDialogInterface : public QObject
{
protected:
	IWebEngineDialogInterface(T *dialog)
		: QObject(nullptr), m_dialog(dialog) {};

public:
	IWebEngineDialogInterface(const IWebEngineDialogInterface &ano) = delete;
	IWebEngineDialogInterface(IWebEngineDialogInterface &&ano) = delete;
	virtual ~IWebEngineDialogInterface(void) = default;

protected:
	T * m_dialog;
};

class IWebEngineDialogWidget : public QWidget
{
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
