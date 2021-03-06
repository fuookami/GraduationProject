#pragma once

#include "SSUtils\GUI\IWebEngineDialogWidget.h"
#include <QtCore/QObject>
#include <memory>

namespace VEDA
{
	class VEDAAboutDialogInterface;

	class VEDAAboutDialog final : public SSUtils::GUI::IWebEngineDialogWidget
	{
		static const int Width = 650;
		static const int Height = 375;
		static const std::string DialogTitle;

	public:
		static VEDAAboutDialog *getInstance(void);

	private:
		VEDAAboutDialog(void);

	public:
		VEDAAboutDialog(const VEDAAboutDialog &ano) = delete;
		VEDAAboutDialog(VEDAAboutDialog &&ano) = delete;
		VEDAAboutDialog &operator=(const VEDAAboutDialog &ano) = delete;
		VEDAAboutDialog &operator=(VEDAAboutDialog &&ano) = delete;
		~VEDAAboutDialog(void) = default;

	protected:
		void registerContents(void) override;
		void initGUI(void) override;

	private:
		std::shared_ptr<VEDAAboutDialogInterface> m_interface;
	};

	class VEDAAboutDialogInterface : public SSUtils::GUI::IWebEngineDialogInterface<VEDAAboutDialog>
	{
		Q_OBJECT;
		friend class VEDAAboutDialog;

	private:
		explicit VEDAAboutDialogInterface(VEDAAboutDialog *dialog);

	public:
		VEDAAboutDialogInterface(const VEDAAboutDialogInterface &ano) = delete;
		VEDAAboutDialogInterface(VEDAAboutDialogInterface &&ano) = delete;
		VEDAAboutDialogInterface &operator=(const VEDAAboutDialogInterface &ano) = delete;
		VEDAAboutDialogInterface &operator=(VEDAAboutDialogInterface &&ano) = delete;
		~VEDAAboutDialogInterface(void) = default;

	public:
		Q_INVOKABLE void onConfirmBtnClicked(void);
		Q_INVOKABLE void onGithubBtnClicked(void);
		Q_INVOKABLE void onCodingBtnClicked(void);
	};
};
