#include "previewwidget.h"

PreviewWidget::PreviewWidget(QWidget *parent) : QWidget(parent)
{
	this->groupBox = new QGroupBox(tr("Preview"), this);
	this->scene = new QGraphicsScene(this);
	this->view = new GraphicsView(this->scene, this);

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
	const qreal adjustV = -3.0f;
	const qreal adjustH = 0.0f;
	this->i->setPlainText(kanji);
	i->adjustSize();
	qreal marginV = i->boundingRect().height() / 4.f / 2.f;
	qreal marginH = i->boundingRect().width() / 4.f / 2.f;
	scene->setSceneRect(i->boundingRect().marginsAdded(QMarginsF(marginH + adjustH, marginV + adjustV, marginH, marginV)));
	view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

	//qDebug() << __PRETTY_FUNCTION__ << i->boundingRect();
}

void PreviewWidget::setKanjiSlot(QString kanji)
{
	this->setKanji(kanji);
}
