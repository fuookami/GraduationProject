#pragma once

#include "SSUtils/GUI/QWebEngineWidget.h"

namespace VEDA
{
	class VEDAHomeViewInterface;

	class VEDAHomeView : public SSUtils::GUI::QWebEngineWidget
	{
	public:
		explicit VEDAHomeView(QWidget *parent = nullptr);
		VEDAHomeView(const VEDAHomeView &ano) = delete;
		VEDAHomeView(VEDAHomeView &&ano) = delete;
		VEDAHomeView &operator=(const VEDAHomeView &rhs) = delete;
		VEDAHomeView &operator=(VEDAHomeView &&rhs) = delete;
		~VEDAHomeView(void) = default;

	private:
		std::shared_ptr<VEDAHomeViewInterface> m_interface;
	};

	class VEDAHomeViewInterface : public SSUtils::GUI::IWebEngineWidgetInterface<VEDAHomeView>
	{
		Q_OBJECT;
		friend class VEDAHomeView;

	private:
		explicit VEDAHomeViewInterface(VEDAHomeView *widget);

	public:
		VEDAHomeViewInterface(const VEDAHomeViewInterface &ano) = delete;
		VEDAHomeViewInterface(VEDAHomeViewInterface &&ano) = delete;
		VEDAHomeViewInterface &operator=(const VEDAHomeViewInterface &rhs) = delete;
		VEDAHomeViewInterface &operator=(VEDAHomeViewInterface &&rhs) = delete;
		~VEDAHomeViewInterface(void) = default;
	};
};
