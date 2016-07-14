#include "wordpadwidget.h"

//void WordPadWidget::focusOutEvent(QFocusEvent *event)
//{
//	if(event->lostFocus()){
//		QMessageBox::information(this, "", "Focus Out!", QMessageBox::Ok);
//	}
//}

void WordPadWidget::closeEvent(QCloseEvent *event)
{
	emit this->hideSig();
	event->ignore();
}

WordPadWidget::WordPadWidget(QWidget *parent) : QWidget(parent)
{
	this->setMinimumWidth(500);
	this->setFocusPolicy(Qt::ClickFocus);
	QFont kanaFontLabel;{
		kanaFontLabel.setFamily("Microsoft YaHei, Courier New");
		kanaFontLabel.setPixelSize(14);
	}
	QFont kanaFontEdit;{
		kanaFontEdit.setFamily("Kozuka Gothic Pr6N M, MS UI Gothic");
		kanaFontEdit.setPixelSize(18);
	}
	QFont normalFontLabel;{
		normalFontLabel.setFamily("Microsoft YaHei, Courier New");
		normalFontLabel.setPixelSize(14);
	}
	QFont normalFontEdit;{
		normalFontEdit.setFamily("Microsoft YaHei, Courier New");
		normalFontEdit.setPixelSize(14);
	}

	this->kanaLabel = new QLabel(tr("Kana"), this);
	this->kanaLabel->setFont(kanaFontLabel);
	this->kanaEdit = new LineEdit(this);
	this->kanaEdit->setFont(kanaFontEdit);
	this->kanaEdit->installEventFilter(this);

	this->kanjiLabel = new QLabel(tr("Kanji"), this);
	this->kanjiLabel->setFont(kanaFontLabel);
	this->kanjiEdit = new LineEdit(this);
	this->kanjiEdit->setFont(kanaFontEdit);
	this->kanjiEdit->installEventFilter(this);

	this->chineseLabel = new QLabel(tr("Chinese"), this);
	this->chineseLabel->setFont(normalFontLabel);
	this->chineseEdit = new LineEdit(this);
	this->chineseEdit->setFont(normalFontEdit);
	this->chineseEdit->installEventFilter(this);

	this->englishLabel = new QLabel(tr("English"), this);
	this->englishLabel->setFont(normalFontLabel);
	this->englishEdit = new LineEdit(this);
	this->englishEdit->setFont(normalFontEdit);
	this->englishEdit->installEventFilter(this);

	this->saveButton = new QPushButton(tr("Save"), this);
	this->saveButton->setFont(normalFontLabel);

	QGridLayout *mainLay = new QGridLayout;
	this->setLayout(mainLay);

	mainLay->addWidget(this->kanaLabel, 0, 0, 1, 1, Qt::AlignRight);
	mainLay->addWidget(this->kanaEdit, 0, 1, 1, 1);
	mainLay->addWidget(this->kanjiLabel, 1, 0, 1, 1, Qt::AlignRight);
	mainLay->addWidget(this->kanjiEdit, 1, 1, 1, 1);
	mainLay->addWidget(this->chineseLabel, 2, 0, 1, 1, Qt::AlignRight);
	mainLay->addWidget(this->chineseEdit, 2, 1, 1, 1);
	mainLay->addWidget(this->englishLabel, 3, 0, 1, 1, Qt::AlignRight);
	mainLay->addWidget(this->englishEdit, 3, 1, 1, 1);
	mainLay->addWidget(this->saveButton, 4, 0, 1, 2, Qt::AlignRight);

	connect(this->saveButton, SIGNAL(clicked(bool)), this, SLOT(saveButtonSlot()));
	connect(this->kanjiEdit, SIGNAL(textChanged(QString)), this, SLOT(textChangedSlot(QString)));

}

void WordPadWidget::setKana(const QString &kana)
{
	this->kanaEdit->setText(kana);
}

void WordPadWidget::setKanji(const QString &kanji)
{
	this->kanjiEdit->setText(kanji);
}

void WordPadWidget::setChinese(const QString &chinese)
{
	this->chineseEdit->setText(chinese);
}

void WordPadWidget::setEnglish(const QString &english)
{
	this->englishEdit->setText(english);
}

QString WordPadWidget::getKana() const
{
	return this->kanaEdit->text();
}

QString WordPadWidget::getKanji() const
{
	return this->kanjiEdit->text();
}

QString WordPadWidget::getChinese() const
{
	return this->chineseEdit->text();
}

QString WordPadWidget::getEnglish() const
{
	return this->englishEdit->text();
}

bool WordPadWidget::eventFilter(QObject *watched, QEvent *event)
{
	if(watched == this->kanaEdit){
		if(event->type() == QEvent::FocusOut){
			//emit this->lostFocus(qobject_cast<QLineEdit*> watched);
			emit this->lostFocus(this->kanaEdit);
		}
	}else if(watched == this->kanjiEdit){
		if(event->type() == QEvent::FocusOut){
			//emit this->lostFocus(qobject_cast<QLineEdit*> watched);
			emit this->lostFocus(this->kanjiEdit);
		}
	}else if(watched == this->chineseEdit){
		if(event->type() == QEvent::FocusOut){
			//emit this->lostFocus(qobject_cast<QLineEdit*> watched);
			emit this->lostFocus(this->chineseEdit);
		}
	}else if(watched == this->englishEdit){
		if(event->type() == QEvent::FocusOut){
			//emit this->lostFocus(qobject_cast<QLineEdit*> watched);
			emit this->lostFocus(this->englishEdit);
		}
	}else{

	}

	return QWidget::eventFilter(watched,event);
}

void WordPadWidget::textChangedSlot(QString str)
{
	emit this->textChangedSig(str);
}

void WordPadWidget::saveButtonSlot()
{
	emit this->saveButtonClicked();
}
