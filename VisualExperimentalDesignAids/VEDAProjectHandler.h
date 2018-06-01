#pragma once

#include <QtCore/QObject>
#include <memory>
#include <utility>
#include <tuple>
#include "VEDAProjectFile.h"

namespace VEDA
{
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
		VEDAProjectHandler &operator=(const VEDAProjectHandler &rhs) = delete;
		VEDAProjectHandler &operator=(VEDAProjectHandler &&rhs) = delete;
		~VEDAProjectHandler(void) = default;

	signals:
		void sig_emitLoadingBegin(void);
		void loadingBegin(void);
		void sig_emitLoadingEnd(void);
		void loadingEnd(void);
		void sig_emitOpenProjectFinished(bool, QString);
		void openProjectFinished(bool, QString);
		void sig_emitCloseProjectFinished(bool, QString);
		void closeProjectFinished(bool, QString);

	public:
		void emitLoadingBegin(void);
		void emitLoadingEnd(void);
	private:
		void emitOpenProjectFinished(const bool ok, const QString &info);
		void emitCloseProjectFinished(const bool ok, const QString &info);

	private:
		void onEmitLoadingBegin(void);
		void onEmitLoadingEnd(void);
		void onEmitOpenProjectFinished(bool, QString);
		void onEmitCloseProjectFinished(bool, QString);

	public:
		static const std::pair<bool, std::string> initProject(const std::string &name, const std::string &path, const bool newDir);
		static const std::tuple<bool, std::string, std::shared_ptr<VEDAProcessFile>> initProcess(VEDAProjectFile *projectFile, const std::string &name, const std::string &path, const bool newDir);
		static const std::tuple<bool, std::string, std::shared_ptr<VEDAModelFile>> initModel(VEDAProcessFile *processFile, const std::string &name, const std::string &path);

		void openProject(const std::string &projectFileUrl, const bool save = true);
		void closeCurrProject(const bool save = true);
		void saveCurrProject(void);

		inline const bool isProjectOpen(void) { return m_currProject != nullptr; }
		inline std::shared_ptr<VEDAProjectFile> currProject(void)const { return m_currProject; }

	private:
		std::shared_ptr<VEDAProjectFile> m_currProject;
	};
};
