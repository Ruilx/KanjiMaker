#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QtWidgets>

class PreviewWidget : public QWidget
{
	Q_OBJECT
	QGraphicsView *view;
	QGraphicsScene *scene;

	QGroupBox *groupBox;

public:
	explicit PreviewWidget(QWidget *parent = 0);
	void setKana(QString kana);
	void setKanji(QString kanji);

signals:

public slots:
};

#endif // PREVIEWWIDGET_H
