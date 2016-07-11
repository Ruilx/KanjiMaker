#ifndef KANAPADWIDGET_H
#define KANAPADWIDGET_H

#include <QtWidgets>
#include "com/kanapushbutton.h"

class KanaPadWidget : public QWidget
{
	Q_OBJECT
	QTabWidget *tabWidget;

	KanaPushButton* hiraganaPadButton[5][21];
	KanaPushButton* katakanaPadButton[5][21];
	KanaPushButton* youonPadButton[5][11];

	void resizeEvent(QResizeEvent *event);
public:
	explicit KanaPadWidget(QWidget *parent = 0);

signals:
	void kanaClicked(QString name, bool e);
private slots:
	void kanaPadClicked(QString name, bool e);
public slots:

};

#endif // KANAPADWIDGET_H
