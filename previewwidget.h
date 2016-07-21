#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QtWidgets>
#include "com/graphicsview.h"

class PreviewWidget : public QWidget
{
	Q_OBJECT
	GraphicsView *view;
	QGraphicsScene *scene;

	QGroupBox *groupBox;

	QGraphicsTextItem *i;
public:
	explicit PreviewWidget(QWidget *parent = 0);
	void setKana(const QString &kana);
	void setKanji(const QString &kanji);

signals:
public slots:
	void setKanjiSlot(QString kanji);
};

#endif // PREVIEWWIDGET_H
