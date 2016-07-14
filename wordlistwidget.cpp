#include "wordlistwidget.h"

void WordlistWidget::closeEvent(QCloseEvent *event)
{
	emit this->hideSig();
	event->ignore();
}

WordlistWidget::WordlistWidget(QWidget *parent) : QWidget(parent)
{
	this->setMaximumWidth(250);
	this->setBaseSize(300, this->height());
	this->groupBox = new QGroupBox("", this);
	this->wordList = new ListWidget(this);
	this->addButton = new QPushButton("+", this);
	this->addButton->setToolTip(tr("Add"));
	this->addButton->setMinimumWidth(23);
	this->removeButton = new QPushButton("-", this);
	this->removeButton->setToolTip(tr("Remove"));
	this->removeButton->setMinimumWidth(23);
	this->upButton = new QPushButton("↑", this);
	this->upButton->setToolTip(tr("Move Upward"));
	this->upButton->setMinimumWidth(23);
	this->downButton = new QPushButton("↓", this);
	this->downButton->setToolTip(tr("Move Downward"));
	this->downButton->setMinimumWidth(23);

	QGridLayout *wordlistLay = new QGridLayout;
	this->groupBox->setLayout(wordlistLay);

	wordlistLay->addWidget(this->addButton, 0, 0, 1, 1);
	wordlistLay->addWidget(this->removeButton, 0, 1, 1, 1);
	wordlistLay->addWidget(this->upButton, 0, 2, 1, 1);
	wordlistLay->addWidget(this->downButton, 0, 3, 1, 1);
	wordlistLay->addWidget(this->wordList, 1, 0, 1, 4);

	QVBoxLayout *mainLay = new QVBoxLayout;
	this->setLayout(mainLay);

	mainLay->addWidget(this->groupBox);

	connect(this->wordList, SIGNAL(mouseClicked(int)), this, SLOT(update()));
	update();

	connect(this->addButton, SIGNAL(clicked(bool)), this, SLOT(addSlot()));
	connect(this->removeButton, SIGNAL(clicked(bool)), this, SLOT(removeSlot()));
	connect(this->upButton, SIGNAL(clicked(bool)), this, SLOT(moveUpSlot()));
	connect(this->downButton, SIGNAL(clicked(bool)), this, SLOT(moveDownSlot()));

	connect(this->wordList, SIGNAL(insert(int)), this, SLOT(popInsertSlot(int)));
	connect(this->wordList, SIGNAL(remove(int)), this, SLOT(popRemoveSlot(int)));
	connect(this->wordList, SIGNAL(moveUp(int)), this, SLOT(popMoveUpSlot(int)));
	connect(this->wordList, SIGNAL(moveDown(int)), this, SLOT(popMoveDoenSlot(int)));
	connect(this->wordList, SIGNAL(draged(int,int)), this, SLOT(dragedSlot(int, int)));
	//connect(this->wordList, SIGNAL(mouseClicked(int)), this, SLOT(mouseClickedSlot(int)));
	connect(this->wordList, SIGNAL(currentRowChanged(int)), this, SLOT(mouseClickedSlot(int)));
}

void WordlistWidget::update()
{
	if(this->wordList->count() == 0){
		this->removeButton->setEnabled(false);
		this->upButton->setEnabled(false);
		this->downButton->setEnabled(false);
	}else{
		if(this->wordList->isSelected()){
			if(this->wordList->currentRow() != -1){
				if(this->wordList->count() == 1){
					this->addButton->setEnabled(true);
					this->removeButton->setEnabled(true);
					this->upButton->setEnabled(false);
					this->downButton->setEnabled(false);
				}else if(this->wordList->currentRow() <= 0){
					this->addButton->setEnabled(true);
					this->removeButton->setEnabled(true);
					this->upButton->setEnabled(false);
					this->downButton->setEnabled(true);
				}else if(this->wordList->currentRow() >= this->wordList->count() -1){
					this->addButton->setEnabled(true);
					this->removeButton->setEnabled(true);
					this->upButton->setEnabled(true);
					this->downButton->setEnabled(false);
				}else{
					this->addButton->setEnabled(true);
					this->removeButton->setEnabled(true);
					this->upButton->setEnabled(true);
					this->downButton->setEnabled(true);
				}
			}else{
				return;
			}
		}else{
			this->addButton->setEnabled(true);
			this->removeButton->setEnabled(false);
			this->upButton->setEnabled(false);
			this->downButton->setEnabled(false);
		}
	}
}

void WordlistWidget::clearList()
{
	this->wordList->clear();
	this->update();
	emit this->listEmpty();
}

void WordlistWidget::setList(const QList<KanjiWord> &word)
{
	this->wordList->clear();
	foreach(KanjiWord w, word){
		if(w.kanji.isEmpty()){
			this->wordList->addItem(tr("名前しない"));
		}else{
			this->wordList->addItem(w.kanji);
		}
	}
	this->update();
}

void WordlistWidget::setHead(const Head &head)
{
	QString nameHere = head.name;
	if(nameHere.length() > 15){
		nameHere = nameHere.left(15).append("...");
	}
	this->groupBox->setTitle(nameHere);
}

void WordlistWidget::addSlot()
{
	emit this->add(this->wordList->count());
}

void WordlistWidget::removeSlot()
{
	if(this->wordList->isSelected()){
		emit this->removed(this->wordList->currentRow());
	}
	if(this->wordList->count() == 0){
		emit this->listEmpty();
	}
}

void WordlistWidget::moveUpSlot()
{
	if(this->wordList->isSelected()){
		int currentRow = this->wordList->currentRow();
		emit this->movedUp(currentRow);
		this->wordList->setCurrentRow(currentRow -1);
		this->update();
	}
}

void WordlistWidget::moveDownSlot()
{
	if(this->wordList->isSelected()){
		int currentRow = this->wordList->currentRow();
		emit this->movedDown(currentRow);
		this->wordList->setCurrentRow(currentRow +1);
		this->update();
	}

}

void WordlistWidget::popInsertSlot(int index)
{
	if(this->wordList->isSelected()){
		emit this->add(index);
	}
}

void WordlistWidget::popRemoveSlot(int index)
{
	if(this->wordList->isSelected()){
		emit this->removed(index);
	}
}

void WordlistWidget::popMoveUpSlot(int index)
{
	if(this->wordList->isSelected()){
		emit this->movedUp(index);
	}
}

void WordlistWidget::popMoveDoenSlot(int index)
{
	if(this->wordList->isSelected()){
		emit this->movedDown(index);
	}
}

void WordlistWidget::dragedSlot(int from, int to)
{
	emit this->draged(from, to);
}

void WordlistWidget::mouseClickedSlot(int index)
{
	if(index == -1){
		return;
	}else{
		emit this->clicked(index);
	}
}
