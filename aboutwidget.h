#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QtWidgets>
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
public:
	explicit AboutWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // ABOUTWIDGET_H
