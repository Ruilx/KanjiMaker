#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <QtCore>

typedef struct KanjiWord_t{
	QString kana;
	QString kanji;
	QString chinese;
	QString english;
	QDateTime timeStamp;
}KanjiWord;

typedef struct Head_t{
	QString name;

}Head;

#endif // STRUCTURE_H
