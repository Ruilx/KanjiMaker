#ifndef WORDLISTWIDGET_H
#define WORDLISTWIDGET_H

#include <QtWidgets>
#include <QGroupBox>
#include "com/listwidget.h"

class WordlistWidget : public QWidget
{
	Q_OBJECT

	QGroupBox *groupBox;
	ListWidget *wordList;
public:
	explicit WordlistWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // WORDLISTWIDGET_H
