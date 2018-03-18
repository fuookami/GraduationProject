#include "VEDAAboutDialog.h"
#include "VEDAVersion.h"
#include "ui_VEDAAboutDialog.h"

namespace VEDA
{
	std::shared_ptr<VEDAAboutDialog> VEDAAboutDialog::getInstance(void)
	{
		std::shared_ptr<VEDAAboutDialog> instance(new VEDAAboutDialog());
		return instance;
	}

	VEDAAboutDialog::VEDAAboutDialog(void)
		: QDialog(nullptr), m_ui(new Ui::VEDAAboutDialog)
	{
		m_ui->setupUi(this);
		m_ui->Version->setText(m_ui->Version->text() + QString::fromLocal8Bit(Version.c_str()));
		m_ui->BuildDatetime->setText(m_ui->BuildDatetime->text() + QString::fromLocal8Bit(BuildDatetime.c_str()));
	}
};
