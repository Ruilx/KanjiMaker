#include "wordlistwidget.h"

WordlistWidget::WordlistWidget(QWidget *parent) : QWidget(parent)
{
	//this->setMaximumWidth(400);
	this->setBaseSize(300, this->height());
	this->groupBox = new QGroupBox("Lesson", this);
	this->wordList = new ListWidget(this);

	QVBoxLayout *wordlistLay = new QVBoxLayout;
	this->groupBox->setLayout(wordlistLay);

	wordlistLay->addWidget(this->wordList);

	QVBoxLayout *mainLay = new QVBoxLayout;
	this->setLayout(mainLay);

	mainLay->addWidget(this->groupBox);


}
