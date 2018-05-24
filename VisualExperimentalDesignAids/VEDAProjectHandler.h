#pragma once

#include <QtCore/QObject>
#include <memory>
#include <utility>
#include "SSUtils\XSD\XSDModel.h"

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

	private:
		void emitOpenProjectFinished(const bool ok, const QString &info);
		void emitCloseProjectFinished(const bool ok, const QString &info);

	public:
		static const std::pair<bool, std::string> initProject(const std::string &name, const std::string &path, const bool newDir);
		void openProject(const std::string &projectFileUrl, const bool save = true);
		void closeCurrProject(const bool save = true);

		inline const bool isProjectOpen(void) { return m_currProject != nullptr; }
		inline std::shared_ptr<VEDAProject> currProject(void)const { return m_currProject; }

	private:
		std::shared_ptr<VEDAProject> m_currProject;
	};
};
