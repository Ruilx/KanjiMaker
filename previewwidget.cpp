#include "previewwidget.h"


PreviewWidget::PreviewWidget(QWidget *parent) : QWidget(parent)
{
	this->groupBox = new QGroupBox(tr("Preview"), this);
	this->scene = new QGraphicsScene(this);
	this->view = new QGraphicsView(this->scene, this);

	QVBoxLayout *lay = new QVBoxLayout;
	this->groupBox->setLayout(lay);
	lay->addWidget(this->view);

	QVBoxLayout *mainLay = new QVBoxLayout;
	this->setLayout(mainLay);
	mainLay->addWidget(this->groupBox);

	QFont font;{
		font.setFamily("A-OTF Folk Pro M, Microsoft YaHei");
		font.setPixelSize(30);
	}
	QGraphicsTextItem *i = new QGraphicsTextItem;
	i->setPlainText("私はルィンリコスです，これは漢字です。");
	i->setFont(font);

	this->scene->addItem(i);
}
