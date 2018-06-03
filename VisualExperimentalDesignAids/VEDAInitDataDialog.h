#pragma once

#include "SSUtils\GUI\IWebEngineDialogWidget.h"
#include "VEDAOperationFile.h"
#include "VEDADataFile.h"
#include <QtCore/QObject>
#include <QtCore/QJsonValue>
#include <memory>

namespace VEDA
{
	class VEDAInitDataDialogInterface;

	class VEDAInitDataDialog final : public SSUtils::GUI::IWebEngineDialogWidget
	{
		static const int Width = 650;
		static const int Height = 375;
		static const std::string DialogTitle;
	};

	class VEDAInitDataDialogInterface : public SSUtils::GUI::IWebEngineWidgetInterface<VEDAInitDataDialog>
	{
		Q_OBJECT;
		friend class VEDAInitDataDialog;

	private:
		explicit VEDAInitDataDialogInterface(VEDAInitDataDialog *dialog, VEDAOperationFile *operationFile);

	public:
		VEDAInitDataDialogInterface(const VEDAInitDataDialogInterface &ano) = delete;
		VEDAInitDataDialogInterface(VEDAInitDataDialogInterface &&ano) = delete;
		VEDAInitDataDialogInterface &operator=(const VEDAInitDataDialogInterface &rhs) = delete;
		VEDAInitDataDialogInterface &operator=(VEDAInitDataDialogInterface &&rhs) = delete;
		~VEDAInitDataDialogInterface(void) = default;

	signals:
		void savePathSelected(QString);
		void initDataFailed(QString);
		void initDataSucceeded(std::shared_ptr<VEDADataFile>);

	public:
		void emitInitDataFailed(const QString &info);
		void emitInitDataSucceeded(std::shared_ptr<VEDADataFile>);
		
	public:
		Q_INVOKABLE void onSelectSavePathBtnClicked(void);
		Q_INVOKABLE void onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue);
		Q_INVOKABLE void onCancelBtnClicked(void);

	private:
		VEDAProcessFile * m_processFile;
	};
};
