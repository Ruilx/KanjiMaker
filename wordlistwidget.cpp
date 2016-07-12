#include "wordlistwidget.h"

WordlistWidget::WordlistWidget(QWidget *parent) : QWidget(parent)
{
	this->setMaximumWidth(200);
	this->setBaseSize(300, this->height());
	this->groupBox = new QGroupBox("Lesson", this);
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
}

void WordlistWidget::update()
{

}
