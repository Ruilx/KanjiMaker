#ifndef WORDLISTWIDGET_H
#define WORDLISTWIDGET_H

#include <QtWidgets>
#include <QGroupBox>
#include "com/listwidget.h"
#include "core/structure.h"

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
signals:
	void clicked(int index);
	void add(int index);
	void removed(int index);\
	void movedUp(int index);
	void movedDown(int index);
	void draged(int from, int to);
public slots:
	void update();
	void clearList();
	void setList(const QList<KanjiWord> &word);
	void setHead(const Head &head);
private slots:
	void addSlot();
	void removeSlot();
	void moveUpSlot();
	void moveDownSlot();
};

#endif // WORDLISTWIDGET_H
