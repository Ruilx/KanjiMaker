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
	void mouseClicked();
	void dropd(int from, int to);
	void insert();
	void remove();
	void moveUp();
	void moveDown();
private slots:
	void insertSlot();
	void removeSlot();
	void moveUpSlot();
	void moveDownSlot();
};

#endif // LISTWIDGET_H
