#include "readsavefile.h"

ReadSaveFile::ReadSaveFile(QString filePath, QObject *parent) : QObject(parent)
{
	this->filePath = filePath;
}

bool ReadSaveFile::saveFile(const QList<KanjiWord> &fileData, const Head &fileHead)
{
	QFile f(this->filePath);
	if(f.open(QIODevice::WriteOnly)){
		QTextStream ts(&f);
		QJsonObject data;
		for(int i=0; i<fileData.length(); i++){
			QJsonObject node;
			node["kana"] = fileData.at(i).kana;
			node["kanji"] = fileData.at(i).kanji;
			node["chinese"] = fileData.at(i).chinese;
			node["english"] = fileData.at(i).english;
			node["time"] = fileData.at(i).timeStamp.toString(Qt::ISODate);

			data[QString::number(i)] = node;
		}

		QJsonObject head;
		head["name"] = fileHead.name;

		QJsonObject obj;
		obj["head"] = head;
		obj["data"] = data;

		QJsonDocument doc(obj);
		ts << doc.toJson(QJsonDocument::Compact);

		f.close();

		return true;
	}else{
		return false;
	}
}

bool ReadSaveFile::loadFile(QList<KanjiWord> *fileData, Head *fileHead)
{
	QFile f(this->filePath);
	if(f.open(QIODevice::ReadOnly)){
		QJsonParseError error;
		QTextStream ts(&f);
		QJsonDocument doc = QJsonDocument::fromJson(ts.readAll().toUtf8(), &error);
		f.close();
		if(doc.isNull() || doc.isEmpty()){
			qDebug() << "[DEBUG]ReadSaveFile::loadFile doc.isNull or isEmpty";
			qDebug() << "[DEBUG]ReadSaveFile::loadFile error:" << error.errorString();
			return false;
		}
		if(doc.isArray()){
			qDebug() << "[DEBUG]ReadSaveFile::loadFile doc.isArray";
			return false;
		}
		QJsonObject obj = doc.object();
		if(obj.isEmpty()){
			qDebug() << "[DEBUG]ReadSaveFile::loadFile obj.isEmpty";
			return false;
		}
		QJsonObject head = obj.value("head").toObject();
		QJsonObject data = obj.value("data").toObject();
		if(head.isEmpty()){
			qDebug() << "[DEBUG]ReadSaveFile::loadFile head.isEmpty";
			return false;
		}
		if(data.isEmpty()){
			qDebug() << "[DEBUG]ReadSaveFile::loadFile data.isEmpty";
			return false;
		}
		fileHead->name = head.value("name").toString();

		if(!fileData->isEmpty()){
			fileData->clear();
		}

		for(int i=0; i<data.length(); i++){
			KanjiWord word;
			QJsonObject node = data.value(QString::number(i)).toObject();
			if(node.isEmpty()){
				return false;
			}
			word.kana = node.value("kana").toString();
			word.kanji = node.value("kanji").toString();
			word.chinese = node.value("chinese").toString();
			word.english = node.value("english").toString();
			word.timeStamp = QDateTime::fromString(node.value("timeStamp").toString(), Qt::ISODate);
			fileData->append(word);
		}

		return true;
	}else{
		qDebug() << "[DEBUG]ReadSaveFile::loadFile file cannot open.";
		return false;
	}

}
