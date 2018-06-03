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

	public:
		static VEDAInitDataDialog *getInstance(VEDAOperationFile *operationFile);

	private:
		VEDAInitDataDialog(VEDAOperationFile *operationFile);

	public:
		VEDAInitDataDialog(const VEDAInitDataDialog &ano) = delete;
		VEDAInitDataDialog(VEDAInitDataDialog &&ano) = delete;
		VEDAInitDataDialog &operator=(const VEDAInitDataDialog &rhs) = delete;
		VEDAInitDataDialog &operator=(VEDAInitDataDialog &&rhs) = delete;
		~VEDAInitDataDialog(void) = default;

		inline const std::shared_ptr<VEDAInitDataDialogInterface> interface(void) const { return m_interface; }

	protected:
		void registerContents(void) override;
		void initGUI(void) override;

	private:
		VEDAOperationFile * m_operationFile;
		std::shared_ptr<VEDAInitDataDialogInterface> m_interface;
	};

	class VEDAInitDataDialogInterface : public SSUtils::GUI::IWebEngineDialogInterface<VEDAInitDataDialog>
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
		
	private:
		void onInitDataSucceeded(std::shared_ptr<VEDADataFile>);

	public:
		Q_INVOKABLE void onSelectSavePathBtnClicked(void);
		Q_INVOKABLE void onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue);
		Q_INVOKABLE void onCancelBtnClicked(void);

	private:
		VEDAOperationFile *m_operationFile;
	};
};
