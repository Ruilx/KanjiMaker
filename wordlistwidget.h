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
	QPushButton *addButton;
	QPushButton *removeButton;
	QPushButton *upButton;
	QPushButton *downButton;
public:
	explicit WordlistWidget(QWidget *parent = 0);
	void update();
signals:

public slots:
};

#endif // WORDLISTWIDGET_H
