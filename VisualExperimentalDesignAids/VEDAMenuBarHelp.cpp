#include "VEDAMenuBarHelp.h"
#include "VEDAAboutDialog.h"
#include "SSUtils\GUI\QMessageBoxUtils.h"
#include <boost/version.hpp>

namespace VEDA
{
	namespace MenuBar
	{
		void onAboutQtBtnClicked(void)
		{
			SSUtils::GUI::QMessageBoxUtils::aboutQt();
		}

		void onAboutBoostBtnClicked(void)
		{
			static const QString BoostInfo(""
				"<p>Boost provides free peer-reviewed portable C++ source libraries.</p>"
				"<p>We emphasize libraries that work well with the C++ Standard Library. Boost libraries are intended to be widely useful, "
				"and usable across a broad spectrum of applications.The <a href=\"http://www.boost.org/users/license.html\">Boost license</a> encourages both commercial and non-commercial use.</p>"
				"<p>We aim to establish \"existing practice\" and provide reference implementations so that Boost libraries are suitable for eventual standardization. "
				"Ten Boost libraries are included in the <a href=\"http://www.open-std.org/jtc1/sc22/wg21/\">C++ Standards Committee's</a> "
				"Library Technical Report (<a href=\"http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1745.pdf\">TR1</a>) and in the new C++11 Standard. "
				"C++11 also includes several more Boost libraries in addition to those from TR1. More Boost libraries are proposed for standardization in C++17. </p>"
				"Since 2006 an intimate week long annual conference related to Boost called <a href=\"http://cppnow.org/\">C++ Now</a> has been held in Aspen, "
				"Colorado each May. Boost has been a participant in the <a href=\"https://developers.google.com/open-source/soc/?csw=1\">annual Google Summer of Code</a> since 2007.");
			static const QString Ttile(QString::fromLocal8Bit("关于Boost"));
			static const QString Text(QString::fromLocal8Bit("<p><b>关于 Boost</b></p><p>版本：%1</p>%2").arg(BOOST_LIB_VERSION).arg(BoostInfo));
			SSUtils::GUI::QMessageBoxUtils::about(Ttile, Text);
		}

		void onAboutMaterializeBtnClicked(void)
		{
		}

		void onAboutBtnClicked(void)
		{
			auto aboutDialog(VEDAAboutDialog::getInstance());
			aboutDialog->show();
		}
	};
};
