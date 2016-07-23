#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QtWidgets>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include "core/about.h"

class AboutWidget : public QDialog
{
	Q_OBJECT

	QLabel *title;
	QLabel *version;
	QLabel *author;
	QLabel *webPage;
	QLabel *license;
	QLabel *repo;
	QLabel *logo;

	void mouseReleaseEvent(QMouseEvent *e);
	void keyReleaseEvent(QKeyEvent *e);

public:
	explicit AboutWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // ABOUTWIDGET_H
