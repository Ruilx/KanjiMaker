#ifndef READSAVEFILE_H
#define READSAVEFILE_H

#include <QObject>
#include <QtCore>
#include "structure.h"

class ReadSaveFile : public QObject
{
	Q_OBJECT

	QString filePath;
public:
	explicit ReadSaveFile(QString filePath, QObject *parent = 0);
	bool saveFile(const QList<KanjiWord> &fileData, const Head &head);
	bool loadFile(QList<KanjiWord> *fileData, Head *fileHead);
signals:

public slots:

};

#endif // READSAVEFILE_H
