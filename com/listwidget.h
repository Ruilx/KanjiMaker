#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QtWidgets>
class ListWidget : public QListWidget
{
	Q_OBJECT
	bool selected;

	QMenu *popMenu;
	QAction *insertAct;
	QAction *removeAct;
	QAction *moveUpwardAct;
	QAction *moveDownwardAct;

	void contextMenuEvent(QContextMenuEvent *);
	void dropEvent(QDropEvent *event);
	void mousePressEvent(QMouseEvent *event);
public:
	ListWidget(QWidget *parent = nullptr);
	bool isSelected();

signals:
	void mouseClicked(int index);
	void draged(int from, int to);
	void insert(int index);
	void remove(int index);
	void moveUp(int index);
	void moveDown(int index);
private slots:
	void insertSlot();
	void removeSlot();
	void moveUpSlot();
	void moveDownSlot();
};

#endif // LISTWIDGET_H
