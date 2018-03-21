#pragma once

#include <QtCore/QObject>
#include <memory>
#include <utility>

namespace VEDA
{
	class VEDAProject;

	class VEDAProjectHandler : public QObject
	{
		Q_OBJECT;

	public:
		static std::shared_ptr<VEDAProjectHandler> getInstance(void);

	private:
		VEDAProjectHandler(void);
	public:
		VEDAProjectHandler(const VEDAProjectHandler &ano) = delete;
		VEDAProjectHandler(VEDAProjectHandler &&ano) = delete;
		~VEDAProjectHandler(void) = default;

	signals:
		void openProjectFinished(bool, QString);
		void closeProjectFinished(bool, QString);

	public:
		static const std::pair<bool, std::string> initProject(const std::string &name, const std::string &location, const bool newDir);
		void openProject(const std::string &projectFileUrl);
		void closeCurrProject(const bool save = true);

		inline const bool isProjectOpen(void) { return m_currProject != nullptr; }
		inline std::shared_ptr<VEDAProject> currProject(void)const { return m_currProject; }


	private:
		std::shared_ptr<VEDAProject> m_currProject;
	};
};
