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
		if(this->currentRow() <= 0){
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
	emit this->mouseClicked();
	emit this->dropd(currentRow, destRow);

}

void ListWidget::mousePressEvent(QMouseEvent *event)
{
	if(this->itemAt(event->x(), event->y()) == nullptr){
		//鼠标按下的地方没有项目
		this->selected = false;
		this->clearSelection();
	}else{
		//反之
		this->selected = true;
	}
	QListWidget::mousePressEvent(event);
	emit mouseClicked();
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
}

bool ListWidget::isSelected()
{
	return this->selected;
}

void ListWidget::insertSlot()
{
	emit this->insert();
}

void ListWidget::removeSlot()
{
	emit this->remove();
}

void ListWidget::moveUpSlot()
{
	emit this->moveUp();
}

void ListWidget::moveDownSlot()
{
	emit this->moveDown();
}
