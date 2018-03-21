#pragma once

#include <QtWidgets/QDialog>
#include <memory>

namespace Ui
{
	class VEDAInitProjectDialog;
};

namespace VEDA
{
	class VEDAInitProjectDialog : public QDialog
	{
	public:
		static std::shared_ptr<VEDAInitProjectDialog> getInstance(void);

	private:
		explicit VEDAInitProjectDialog(void);

	public:
		VEDAInitProjectDialog(const VEDAInitProjectDialog &ano) = delete;
		VEDAInitProjectDialog(VEDAInitProjectDialog &&ano) = delete;
		~VEDAInitProjectDialog(void) = default;

	private:
		void onSelectLocationBtnClicked(void);
		void onComfirmBtnClicked(void);
		void onCancelBtnClicked(void);

	private:
		std::shared_ptr<Ui::VEDAInitProjectDialog> m_ui;
	};
}
