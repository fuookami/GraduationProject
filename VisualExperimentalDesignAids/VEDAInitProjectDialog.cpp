#include "VEDAInitProjectDialog.h"
#include "ui_VEDAInitProjectDialog.h"

namespace VEDA
{
	std::shared_ptr<VEDAInitProjectDialog> VEDAInitProjectDialog::getInstance(void)
	{
		std::shared_ptr<VEDAInitProjectDialog> instance(new VEDAInitProjectDialog());
		return instance;
	}

	VEDAInitProjectDialog::VEDAInitProjectDialog(void)
		: QDialog(nullptr), m_ui(new Ui::VEDAInitProjectDialog())
	{
		m_ui->setupUi(this);
	}
};
