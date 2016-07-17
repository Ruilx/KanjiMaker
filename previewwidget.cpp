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
	this->view = new View(this->scene, this);

	QVBoxLayout *lay = new QVBoxLayout;
	this->groupBox->setLayout(lay);
	lay->addWidget(this->view);

	QVBoxLayout *mainLay = new QVBoxLayout;
	this->setLayout(mainLay);
	mainLay->addWidget(this->groupBox);

	this->scene->addItem(i = new QGraphicsTextItem);

	QFont font;
	font.setFamily("A-OTF Folk Pro M, Microsoft YaHei");
	i->setFont(font);

	setKanji("カンジ　メーカー");
	//i->setFlag(QGraphicsItem::ItemIsMovable, true);

	view->setMinimumSize(0, 0);
	view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//view->resize(QSize(i->boundingRect().size()));
}

void PreviewWidget::setKana(const QString &kana)
{
	Q_UNUSED(kana);
	//TODO: this function will fill after fix the preview widget scale problem.
}

void PreviewWidget::setKanji(const QString &kanji)
{
	this->i->setPlainText(kanji);
	i->adjustSize();
	qreal marginV = i->boundingRect().height() / 4. / 2.;
	qreal marginH = i->boundingRect().width() / 4. / 2.;
	scene->setSceneRect(i->boundingRect().marginsAdded(QMarginsF(marginH, marginV, marginH, marginV)));
	view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
	//qDebug() << __PRETTY_FUNCTION__ << i->boundingRect();
}

void PreviewWidget::setKanjiSlot(QString kanji)
{
	this->setKanji(kanji);
}
