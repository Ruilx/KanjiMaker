#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>

class ListWidget : public QListWidget
{
	Q_OBJECT
public:
	ListWidget(QWidget *parent = nullptr);
};

#endif // LISTWIDGET_H
