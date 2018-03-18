#pragma once

#include <QtWidgets/QDialog>
#include <memory>

namespace Ui
{
	class VEDAAboutDialog;
};

namespace VEDA
{
	class VEDAAboutDialog : public QDialog
	{
	public:
		static std::shared_ptr<VEDAAboutDialog> getInstance(void);

	private:
		VEDAAboutDialog(void);
		
	public:
		VEDAAboutDialog(const VEDAAboutDialog &ano) = delete;
		VEDAAboutDialog(VEDAAboutDialog &&ano) = delete;
		~VEDAAboutDialog(void) = default;

	private:
		std::shared_ptr<Ui::VEDAAboutDialog> m_ui;
	};
};
