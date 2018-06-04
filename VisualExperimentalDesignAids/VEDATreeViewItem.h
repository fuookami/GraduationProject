#pragma once

#include <QtWidgets/QTreeWidgetItem>
#include "VEDAFile.h"

namespace VEDA
{
	class VEDATreeViewItem : public QTreeWidgetItem
	{
	public:
		static VEDATreeViewItem *generateProjectItem(std::shared_ptr<VEDAProjectFile> projectFile);
		static VEDATreeViewItem *generatePublicModelItem(VEDATreeViewItem *projectItem, const std::string &url, VEDAFile *file = nullptr);
		static VEDATreeViewItem *generateProcessItem(VEDATreeViewItem *projectItem, std::shared_ptr<VEDAProcessFile> processFile);
		static VEDATreeViewItem *genearteModelItem(VEDATreeViewItem *processItem, const std::string &url, VEDAFile *file = nullptr);
		static VEDATreeViewItem *generateOperationItem(VEDATreeViewItem *processItem, std::shared_ptr<VEDAOperationFile> operationFile);
		static VEDATreeViewItem *generateDataItem(VEDATreeViewItem *operationItem, const std::string &url, VEDAFile *file = nullptr);

	public:
		explicit VEDATreeViewItem(const std::string &url, const VEDAFile::Type type, VEDAFile *file = nullptr);
		explicit VEDATreeViewItem(QTreeWidgetItem *parent, const std::string &url, const VEDAFile::Type type, VEDAFile *file = nullptr);
		VEDATreeViewItem(const VEDATreeViewItem &ano) = delete;
		VEDATreeViewItem(VEDATreeViewItem &&ano) = delete;
		VEDATreeViewItem &operator=(const VEDATreeViewItem &rhs) = delete;
		VEDATreeViewItem &operator=(VEDATreeViewItem &&rhs) = delete;
		~VEDATreeViewItem(void) = default;

		inline const QString &url(void) const { return m_url; }
		inline const QString &name(void) const { return m_name; }
		inline const VEDAFile::Type type(void) const { return m_type; }
		inline VEDAFile *file(void) const { return m_file; }
		inline void setFile(VEDAFile *file) { m_file = file; }

	private:
		QString m_url;
		QString m_name;
		VEDAFile::Type m_type;
		VEDAFile *m_file;
	};
};
