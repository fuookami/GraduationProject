#pragma once

#include <QtWidgets/QWidget>
#include <memory>

namespace VEDA
{
	class VEDAMainView : public QWidget
	{
		Q_OBJECT;

	public:
		explicit VEDAMainView(void);
		VEDAMainView(const VEDAMainView &ano) = delete;
		VEDAMainView(VEDAMainView &&ano) = delete;
		VEDAMainView &operator=(const VEDAMainView &rhs) = delete;
		VEDAMainView &operator=(VEDAMainView &&rhs) = delete;
		~VEDAMainView(void) = default;
	};
};
