#pragma once

#include <QtCore/QObject>
#include <memory>
#include <utility>
#include <tuple>
#include "VEDAProjectFile.h"
#include "CARSDK\ExperimentalDesignTable.h"

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
		void emitOpenProjectFinished(const bool ok, const QString &info);
		void emitCloseProjectFinished(const bool ok, const QString &info);

	private:
		void onEmitLoadingBegin(void);
		void onEmitLoadingEnd(void);
		void onEmitOpenProjectFinished(bool, QString);
		void onEmitCloseProjectFinished(bool, QString);

	public:
		static const std::pair<bool, std::string> initProject(const std::string &name, const std::string &path, const bool newDir);
		static const std::pair<bool, std::string> initPublicModel(const std::string &name, const std::string &path, const bool newDir);
		static const std::tuple<bool, std::string, std::shared_ptr<VEDAProcessFile>> initProcess(VEDAProjectFile *projectFile, const std::string &name, const std::string &path, const bool newDir);
		static const std::tuple<bool, std::string, std::shared_ptr<VEDAModelFile>> initModel(VEDAProcessFile *processFile, const std::string &name, const std::string &path);
		static const std::tuple<bool, std::string, std::shared_ptr<VEDAOperationFile>> initOperation(VEDAProcessFile *processFile, const std::string &name, const std::string &path, const bool newDir, const std::string &methodName, const std::string &methodCategory, const std::map<std::string, std::string> &methodAttributes);
		static const std::tuple<bool, std::string, std::shared_ptr<VEDADataFile>> initData(VEDAOperationFile *operationFile, const std::string &name, const std::string &path, const std::shared_ptr<XSDFrontend::XSDModel> model, const CARSDK::ExperimentalDesignTable &table);

		void openProject(const std::string &projectFileUrl, const bool save = true);
		static std::shared_ptr<VEDAProcessFile> openProcess(VEDAProjectFile *projectFile, const std::string &processFileUrl, const bool ignoreIsChild = false);
		static std::shared_ptr<VEDAModelFile> openModel(VEDAProcessFile *processFile, const bool ignoreIsChild = false);
		static std::shared_ptr<VEDAOperationFile> openOperation(VEDAProcessFile *processFile, const std::string &operationFileUrl, const bool ignoreIsChild = false);
		static std::shared_ptr<VEDADataFile> openData(VEDAOperationFile *operationFile, const std::string &dataFileUrl, const bool ignoreIsChild = false);

		void closeCurrProject(const bool save = true);
		void saveCurrProject(void);

		inline const bool isProjectOpen(void) { return m_currProject != nullptr; }
		inline std::shared_ptr<VEDAProjectFile> currProject(void)const { return m_currProject; }
		inline const std::string &lastError(void) const { return m_lastError; }

	private:
		std::shared_ptr<VEDAProjectFile> m_currProject;
		std::string m_lastError;
	};
};
