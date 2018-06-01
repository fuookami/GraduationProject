#pragma once

#include "SSUtils\GUI\IWebEngineDialogWidget.h"
#include <QtCore/QObject>
#include <QtCore/QJsonValue>
#include <memory>

namespace VEDA
{
	class VEDAInitProjectDialogInterface;

	class VEDAInitProjectDialog final : public SSUtils::GUI::IWebEngineDialogWidget
	{
		static const int Width = 650;
		static const int Height = 375;
		static const std::string DialogTitle;

	public:
		static VEDAInitProjectDialog *getInstance(void);

	private:
		VEDAInitProjectDialog(void);

	public:
		VEDAInitProjectDialog(const VEDAInitProjectDialog &ano) = delete;
		VEDAInitProjectDialog(VEDAInitProjectDialog &&ano) = delete;
		VEDAInitProjectDialog &operator=(const VEDAInitProjectDialog &rhs) = delete;
		VEDAInitProjectDialog &operator=(VEDAInitProjectDialog &&rhs) = delete;
		~VEDAInitProjectDialog(void) = default;

	protected:
		void registerContents(void) override;
		void initGUI(void) override;

	private:
		std::shared_ptr<VEDAInitProjectDialogInterface> m_interface;
	};

	class VEDAInitProjectDialogInterface : public SSUtils::GUI::IWebEngineDialogInterface<VEDAInitProjectDialog>
	{
		Q_OBJECT;
		friend class VEDAInitProjectDialog;

	private:
		explicit VEDAInitProjectDialogInterface(VEDAInitProjectDialog *dialog);

	public:
		VEDAInitProjectDialogInterface(const VEDAInitProjectDialogInterface &ano) = delete;
		VEDAInitProjectDialogInterface(VEDAInitProjectDialogInterface &&ano) = delete;
		VEDAInitProjectDialogInterface &operator=(const VEDAInitProjectDialogInterface &rhs) = delete;
		VEDAInitProjectDialogInterface &operator=(VEDAInitProjectDialogInterface &&rhs) = delete;
		~VEDAInitProjectDialogInterface(void) = default;

	signals:
		void savePathSelected(QString);
		void initProjectFailed(QString);
		void initProjectSucceeded(QString);

	public:
		void emitInitProjectFailed(const QString &info);
		void emitInitProjectSucceeded(const std::string &newProjectUrl);

	private:
		void onInitProjectSucceeded(QString newProjectUrl);

	public:
		Q_INVOKABLE void onSelectSavePathBtnClicked(void);
		Q_INVOKABLE void onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue, bool newDir);
		Q_INVOKABLE void onCancelBtnClicked(void);
	};
}
