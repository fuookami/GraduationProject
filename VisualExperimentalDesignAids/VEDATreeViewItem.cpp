#include "VEDATreeViewItem.h"
#include "SSUtils/FileUtils.h"

namespace VEDA
{
	VEDATreeViewItem::VEDATreeViewItem(const std::string & url, const VEDAFile::Type type, VEDAFile * file)
		: VEDATreeViewItem(nullptr, url, type, file)
	{
	}

	VEDATreeViewItem::VEDATreeViewItem(QTreeWidgetItem * parent, const std::string & url, const VEDAFile::Type type, VEDAFile * file)
		: QTreeWidgetItem(parent), 
		m_url(QString::fromLocal8Bit(url.c_str())),
		m_name(QString::fromLocal8Bit(SSUtils::File::getFileNameOfUrl(url).c_str())), 
		m_type(type), m_file(file)
	{
		this->setText(0, m_name);
		this->setToolTip(0, m_url);
	}
};
