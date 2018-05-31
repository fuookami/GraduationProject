#include "QLoadingDialog.h"

namespace SSUtils
{
	namespace GUI
	{
		std::shared_ptr<QLoadingDialog> QLoadingDialog::getInstance(void)
		{
			static std::shared_ptr<QLoadingDialog> ret(new QLoadingDialog());
			return ret;
		}

		QLoadingDialog::QLoadingDialog(void)
			: QDialog(nullptr)
		{
			m_label = new QLabel(this);
			m_label->setGeometry(0, 0, this->width(), this->height());

			this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
			this->setAutoFillBackground(true);
		}

		void QLoadingDialog::setUrl(const QString & url)
		{
			m_movie.reset(new QMovie(url));
			m_label->setMovie(m_movie.get());
		}

		int QLoadingDialog::exec(void)
		{
			if (m_movie != nullptr)
			{
				return 0;
			}

			if (m_location != nullptr)
			{
				int offset_x = (m_location->width() - this->width()) / 2;
				int offset_y = (m_location->height() - this->height()) / 2;
				this->setGeometry(m_location->x() + offset_x, m_location->y() + offset_y, this->width(), this->height());
			}

			m_movie->start();
			QDialog::exec();
		}

		void QLoadingDialog::closeEvent(QCloseEvent *)
		{
			if (m_movie != nullptr)
			{
				m_movie->stop();
			}
		}

		void QLoadingDialog::resizeEvent(QResizeEvent *)
		{
			m_label->resize(this->size());
		}
	};
};
