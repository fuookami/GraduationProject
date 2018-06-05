#include "VEDADataView.h"
#include "VEDAGUIGlobal.h"
#include "CARSDK/DataHandlingModule.h"
#include "VEDAProjectHandler.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <thread>

namespace VEDA
{
	VEDADataView::VEDADataView(VEDADataFile * file, QWidget * parent)
		: QWebEngineWidget(parent), m_file(file), m_interface(new VEDADataViewInterface(file, this))
	{
		registerObject(m_interface);

		load(QString::fromLocal8Bit(GUIEntrance::DataViewUrl.c_str()));
	}

	const QString VEDADataViewInterface::ReadOnlyFactorsTag("read_only_factors");
	const QString VEDADataViewInterface::FactorsTag("factors");
	const QString VEDADataViewInterface::BatchesTag("batches");
	const QString VEDADataViewInterface::ContentTag("content");
	const QString VEDADataViewInterface::AttributesTag("attributes");

	VEDADataViewInterface::VEDADataViewInterface(VEDADataFile * file, VEDADataView * widget)
		: IWebEngineWidgetInterface(widget), m_file(file)
	{
	}

	void VEDADataViewInterface::emitDataResponse(const QString & data)
	{
		emit dataResponse(data);
	}

	void VEDADataViewInterface::emitSubmitRespnse(const bool ok, const QString & data)
	{
		emit submitResponse(ok, data);
	}

	void VEDADataViewInterface::dataRequested(void)
	{
		std::thread([this]() 
		{
			auto dataFile(this->m_file);
			auto instance = CARSDK::DataHandlingModule::instance();
			auto projectHandler = VEDAProjectHandler::getInstance();

			projectHandler->emitLoadingBegin();
			this->m_table = instance->analyze(dataFile->getModel(), dataFile->getData());

			QJsonObject json;
			QJsonArray readOnlyFactors;
			QJsonArray factors;
			QJsonArray batches;

			for (const auto &typeName : this->m_table.readOnlyTypeNames())
			{
				readOnlyFactors.push_back(QString::fromLocal8Bit(typeName.c_str()));
			}
			for (const auto &typeName : this->m_table.typeNames())
			{
				factors.push_back(QString::fromLocal8Bit(typeName.c_str()));
			}
			for (const auto &thisBatch : this->m_table.batches())
			{
				QJsonArray cells;
				for (const auto &thisCell : thisBatch)
				{
					QJsonObject cell;
					QJsonObject attribute;
					cell.insert(ContentTag, QString::fromLocal8Bit(thisCell.content.c_str()));
					for (const auto &pair : thisCell.attrs)
					{
						attribute.insert(QString::fromLocal8Bit(pair.first.c_str()), QString::fromLocal8Bit(pair.second.c_str()));
					}
					cell.insert(AttributesTag, attribute);
					cells.push_back(cell);
				}
				batches.push_back(cells);
			}

			json.insert(ReadOnlyFactorsTag, readOnlyFactors);
			json.insert(FactorsTag, factors);
			json.insert(BatchesTag, batches);
			QJsonDocument document;
			document.setObject(json);
			this->emitDataResponse(QString(document.toJson(QJsonDocument::Compact)));
			projectHandler->emitLoadingEnd();
		}).detach();
	}

	void VEDADataViewInterface::dataSubmited(QJsonValue dataValue)
	{
		std::thread([this, dataValue]()
		{
			auto instance = CARSDK::DataHandlingModule::instance();
			auto projectHandler = VEDAProjectHandler::getInstance();

			projectHandler->emitLoadingBegin();

			auto data = QJsonDocument::fromJson(dataValue.toString().toLocal8Bit().data()).toVariant().toList();
			for (SSUtils::uint32 i(0), j(data.size()); i != j; ++i)
			{
				auto batch = data[i].toStringList();
				for (SSUtils::uint32 p(0), q(batch.size()); p != q; ++p)
				{
					this->m_table.batches()[i][p].content.assign(batch[p].toLocal8Bit());
				}
			}

			auto newData(instance->normalize(this->m_file->getModel(), this->m_table));
			if (newData == nullptr)
			{
				this->emitSubmitRespnse(false, QString::fromLocal8Bit("实验方案设计表错误"));
				return;
			}
			this->m_file->setData(newData);
			this->m_file->save();
			this->emitSubmitRespnse(true, QString());
			projectHandler->emitLoadingEnd();
		}).detach();
	}
};
