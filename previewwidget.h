#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QtWidgets>

class PreviewWidget : public QWidget
{
	Q_OBJECT
	QGraphicsView *view;
	QGraphicsScene *scene;

	QGroupBox *groupBox;

	void resizeEvent(QResizeEvent *event);

	QGraphicsTextItem *i;
public:
	explicit PreviewWidget(QWidget *parent = 0);
	void setKana(const QString &kana);
	void setKanji(const QString &kanji);
	void setFontSize(int pixelSize);

signals:
public slots:
	void setKanjiSlot(QString kanji);
};

#endif // PREVIEWWIDGET_H
