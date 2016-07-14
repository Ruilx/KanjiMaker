#include "previewwidget.h"


void PreviewWidget::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event);
//	qDebug() << "Widget: W:" << event->size().width() << "H:" << event->size().height();
//	qDebug() << "Scene:  W:" << this->scene->width() << "H:" << this->scene->height();
//	qDebug() << "View:   W:" << this->view->width() << "H:" << this->view->height();
//	i->setPlainText(QString("View Width: %1, Height: %2.").arg(this->view->width()).arg(this->view->height()));
//	QRectF r = i->boundingRect();
//	QSize v(this->view->width() - 20, this->view->height() - 20);
//	QFont f = i->font();
//	if(v.width() > v.height()){
//		if(r.width() > r.height()){
//			if(r.width() > v.width() && r.height() < v.height()){
//				this->view->scale((qreal)v.width() / (qreal)r.width(), (qreal)v.width() / (qreal)r.width());
//			}else if(r.width() > v.width() && r.height() > v.height()){
//				qreal widthScale = v.width() / r.width();
//				qreal heightScale = v.height() / r.height();
//				this->view->scale(qMin(widthScale, heightScale), qMin(widthScale, heightScale));
//			}else if(r.width() < v.width() && r.height() < v.height()){
//				this->view->scale((qreal)v.width() / (qreal)r.width(), (qreal)v.width() / (qreal)r.width());
//			}else if(r.width() < v.width() && r.height() > v.height()){
//				qreal widthScale = v.width() / r.width();
//				qreal heightScale = v.height() / r.height();
//				this->view->scale(qMin(widthScale, heightScale), qMin(widthScale, heightScale));
//			}
//		}
	//	}
}

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
		font.setPixelSize(52);
	}
	i = new QGraphicsTextItem;
	i->setPlainText("カンジ　メーカー");
	i->setFont(font);
	//i->setFlag(QGraphicsItem::ItemIsMovable, true);

	this->scene->addItem(i);

	this->view->resize(this->scene->width(), this->scene->height());

}

void PreviewWidget::setKana(QString kana)
{
	Q_UNUSED(kana);
}

void PreviewWidget::setKanji(QString kanji)
{
	this->i->setPlainText(kanji);
	QFont font = this->i->font();
	font.setPixelSize(40);
	this->i->setFont(font);
}
