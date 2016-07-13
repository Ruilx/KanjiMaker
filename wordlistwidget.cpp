#include "wordlistwidget.h"

WordlistWidget::WordlistWidget(QWidget *parent) : QWidget(parent)
{
	this->setMaximumWidth(200);
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

	connect(this->wordList, SIGNAL(mouseClicked()), this, SLOT(update()));
	update();

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
				if(this->wordList->currentRow() <= 0){
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
}

void WordlistWidget::setList(const QList<KanjiWord> &word)
{
	foreach(KanjiWord w, word){
		this->wordList->addItem(w.kanji);
	}
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

}

void WordlistWidget::removeSlot()
{

}

void WordlistWidget::moveUpSlot()
{

}

void WordlistWidget::moveDownSlot()
{

}
