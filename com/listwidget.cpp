#include "listwidget.h"

void ListWidget::contextMenuEvent(QContextMenuEvent *)
{
	QPoint currentMousePos = this->mapFromGlobal(QCursor::pos());
	if(this->itemAt(currentMousePos) == nullptr){
		//鼠标右键点击到了一个空白的地方
		this->removeAct->setEnabled(false);
		this->moveUpwardAct->setEnabled(false);
		this->moveDownwardAct->setEnabled(false);
		this->insertAct->setEnabled(true);
	}else{
		this->setCurrentItem(this->itemAt(currentMousePos));
		this->removeAct->setEnabled(true);
		if(this->count() == 1){
			//只有一个项目
			this->moveUpwardAct->setEnabled(false);
			this->moveDownwardAct->setEnabled(false);
		}else if(this->currentRow() <= 0){
			//选择了第一个项目
			this->moveUpwardAct->setEnabled(false);
			this->moveDownwardAct->setEnabled(true);
		}else if(this->currentRow() >= this->count() -1){
			//选择了最后一个项目
			this->moveDownwardAct->setEnabled(false);
			this->moveUpwardAct->setEnabled(true);
		}else{
			//选择了中间的项目
			this->moveUpwardAct->setEnabled(true);
			this->moveDownwardAct->setEnabled(true);
		}
	}
	this->popMenu->exec(QCursor::pos());
}

void ListWidget::dropEvent(QDropEvent *event)
{
	int currentRow = this->row(this->currentItem());
	this->takeItem(currentRow);
	QListWidget::dropEvent(event);
	int destRow = this->row(this->itemAt(event->pos()));
	this->setCurrentRow(destRow);
	emit this->mouseClicked(destRow);
	emit this->draged(currentRow, destRow);
}

void ListWidget::mousePressEvent(QMouseEvent *event)
{
	int index = -1;
	if(this->itemAt(event->x(), event->y()) == nullptr){
		//鼠标按下的地方没有项目
		this->selected = false;
		this->clearSelection();
		index = -1;
	}else{
		//反之
		this->selected = true;
		index = this->currentRow();
	}
	QListWidget::mousePressEvent(event);
	emit mouseClicked(index);
}

ListWidget::ListWidget(QWidget *parent): QListWidget(parent)
{
	this->setDragEnabled(true);
	this->setMovement(QListView::Free);

	this->popMenu = new QMenu(this);
	this->insertAct = new QAction("Insert Word", this);
	this->removeAct = new QAction("Remove Word", this);
	this->moveUpwardAct = new QAction("Move Upward", this);
	this->moveDownwardAct = new QAction("Move Downward", this);
	this->popMenu->addAction(this->insertAct);
	this->popMenu->addAction(this->removeAct);
	this->popMenu->addAction(this->moveUpwardAct);
	this->popMenu->addAction(this->moveDownwardAct);

	//connect(this, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemSelected()));
	connect(this->insertAct, SIGNAL(triggered(bool)), this, SLOT(insertSlot()));
	connect(this->removeAct, SIGNAL(triggered(bool)), this, SLOT(removeSlot()));
	connect(this->moveUpwardAct, SIGNAL(triggered(bool)), this, SLOT(moveUpSlot()));
	connect(this->moveDownwardAct, SIGNAL(triggered(bool)), this, SLOT(moveDownSlot()));
}

bool ListWidget::isSelected()
{
	return this->selected;
}

void ListWidget::insertSlot()
{
	emit this->insert(this->currentRow());
}

void ListWidget::removeSlot()
{
	emit this->remove(this->currentRow());
}

void ListWidget::moveUpSlot()
{
	emit this->moveUp(this->currentRow());
}

void ListWidget::moveDownSlot()
{
	emit this->moveDown(this->currentRow());
}
