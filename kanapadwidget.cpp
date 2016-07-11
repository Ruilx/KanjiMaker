#include "kanapadwidget.h"

void KanaPadWidget::resizeEvent(QResizeEvent *event)
{
	//qDebug() << "Resize: W:" << event->size().width() << "H:" << event->size().height();
}

KanaPadWidget::KanaPadWidget(QWidget *parent) : QWidget(parent)
{
	const QString hiragana[5] = {QString("あかがさざただなはばぱまやらわんぁー\nゃゎ"),
								 QString("いきぎしじちぢにひびぴみ\nり\n\nぃ\n\n\n\n"),
								 QString("うくぐすずつづぬふぶぷむゆる\n\nぅ\nっゅ "),
								 QString("えけげせぜてでねへべぺめ\nれ\n\nぇ\n\n\n\n"),
								 QString("おこごそぞとどのほぼぽもよろを\nぉ\n\nょ\n"),};
	const QString katakana[5] = {QString("アカガサザタダナハバパマヤラワンァヵ\nャヮ"),
								 QString("イキギシジチヂニヒビピミ\nリ\n\nィ\n\n\n\n"),
								 QString("ウクグスズツヅヌフブプムユル\n\nゥ\nッュ\n"),
								 QString("エケゲセゼテデネヘベペメ\nレ\n\nェヶ\n\n\n"),
								 QString("オコゴソゾトドノホボポモヨロヲ\nォ\n\nェ\n"),};
	const QString youon[5][11] = {{QString("きゃ"), QString("ぎゃ"), QString("しゃ"), QString("じゃ"), QString("ちゃ"), QString("にゃ"), QString("ひゃ"), QString("びゃ"), QString("ぴゃ"), QString("みゃ"), QString("りゃ")},
								  {QString("きゅ"), QString("ぎゅ"), QString("しゅ"), QString("じゅ"), QString("ちゅ"), QString("にゅ"), QString("ひゅ"), QString("びゅ"), QString("ぴゅ"), QString("みゅ"), QString("りゅ")},
								  {QString("きょ"), QString("ぎょ"), QString("しょ"), QString("じょ"), QString("ちょ"), QString("にょ"), QString("ひょ"), QString("びょ"), QString("ぴょ"), QString("みょ"), QString("りょ")},
								  {QString("ウィ"), QString("ウェ"), QString("ウォ"), QString("シェ"), QString("チェ"), QString("ツァ"), QString("ツェ"), QString("ツォ"), QString("ティ"), QString("トゥ"), QString()},
								  {QString("ファ"), QString("フィ"), QString("フェ"), QString("フォ"), QString("ジェ"), QString("ディ"), QString("ドゥ"), QString("デュ"), QString(), QString(), QString()},};

	this->setFixedHeight(195);
	this->tabWidget = new QTabWidget(this);
	QFont font;{
		font.setFamily("Yu Gothic, A-OTF Folk Pro B, MS Gothic, Microsoft YaHei");
		font.setPixelSize(15);
	}
	QWidget *hiraganaWidget = new QWidget(this);
	QGridLayout *hiraganaLay = new QGridLayout;
	hiraganaWidget->setLayout(hiraganaLay);
	for(int i=0; i<5; i++){
		for(int j=0; j<21; j++){
			QChar kanaChar = hiragana[i].at(j);
			if(kanaChar == QChar(' ') || kanaChar == QChar('\n') || kanaChar == QChar(0)){
				kanaChar = QChar(0);
			}
			this->hiraganaPadButton[i][j] = new KanaPushButton(QString(kanaChar), this);
			//this->kanaPadButton[i][j]->setFixedSize(25, 25);
			this->hiraganaPadButton[i][j]->setFixedHeight(25);
			this->hiraganaPadButton[i][j]->setMinimumWidth(25);
			this->hiraganaPadButton[i][j]->setFont(font);
			if(kanaChar == QChar(0) || kanaChar == QChar('0') || kanaChar.isNull()){
				this->hiraganaPadButton[i][j]->setEnabled(false);
			}else{
				connect(this->hiraganaPadButton[i][j], SIGNAL(clicked(QString,bool)), this, SLOT(kanaPadClicked(QString,bool)));
				this->hiraganaPadButton[i][j]->setText(QString(kanaChar));
			}
			hiraganaLay->addWidget(this->hiraganaPadButton[i][j], i, j, 1, 1);
		}
	}
	hiraganaLay->setSpacing(2);
	//hiraganaLay->setSizeConstraint(QLayout::SetFixedSize);

	QWidget *katakanaWidget = new QWidget(this);
	QGridLayout *katakanaLay = new QGridLayout;
	katakanaWidget->setLayout(katakanaLay);
	for(int i=0; i<5; i++){
		for(int j=0; j<21; j++){
			QChar kanaChar = katakana[i].at(j);
			if(kanaChar == QChar(' ') || kanaChar == QChar('\n') || kanaChar == QChar(0)){
				kanaChar = QChar(0);
			}
			this->katakanaPadButton[i][j] = new KanaPushButton(QString(kanaChar), this);
			this->katakanaPadButton[i][j]->setFixedHeight(25);
			this->katakanaPadButton[i][j]->setMinimumWidth(25);
			this->katakanaPadButton[i][j]->setFont(font);
			if(kanaChar == char(0) || kanaChar == QChar('0') || kanaChar.isNull()){
				this->katakanaPadButton[i][j]->setEnabled(false);
			}else{
				connect(this->katakanaPadButton[i][j], SIGNAL(clicked(QString,bool)), this, SLOT(kanaPadClicked(QString,bool)));
				this->katakanaPadButton[i][j]->setText(QString(kanaChar));
			}
			katakanaLay->addWidget(this->katakanaPadButton[i][j], i, j, 1, 1);
		}
	}
	katakanaLay->setSpacing(2);

	QWidget *youonWidget = new QWidget(this);
	QGridLayout *youonLay = new QGridLayout;
	youonWidget->setLayout(youonLay);
	for(int i=0; i<5; i++){
		for(int j=0; j<11; j++){
			QString youonChar = youon[i][j];
			if(youonChar.isEmpty() || youonChar.isNull() || youonChar == "\n" || youonChar == " "){
				youonChar = QString();
			}
			this->youonPadButton[i][j] = new KanaPushButton(youonChar, this);
			this->youonPadButton[i][j]->setFixedHeight(25);
			this->youonPadButton[i][j]->setMinimumWidth(50);
			this->youonPadButton[i][j]->setFont(font);
			if(youonChar.isEmpty() || youonChar.isNull() || youonChar == ""){
				this->youonPadButton[i][j]->setEnabled(false);
			}else{
				connect(this->youonPadButton[i][j], SIGNAL(clicked(QString,bool)), this, SLOT(kanaPadClicked(QString,bool)));
				this->youonPadButton[i][j]->setText(youonChar);
			}
			youonLay->addWidget(this->youonPadButton[i][j], i, j, 1, 1);
		}
	}
	youonLay->setSpacing(2);

	this->tabWidget->addTab(hiraganaWidget, tr("ひらがな"));
	this->tabWidget->addTab(katakanaWidget, tr("カタカナ"));
	this->tabWidget->addTab(youonWidget, tr("拗音"));

	QVBoxLayout *mainLay = new QVBoxLayout;
	this->setLayout(mainLay);
	mainLay->addWidget(this->tabWidget);
	mainLay->setSpacing(0);
}

void KanaPadWidget::kanaPadClicked(QString name, bool e)
{
	emit kanaClicked(name, e);
}
