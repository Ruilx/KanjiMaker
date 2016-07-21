#include "mainw.h"

void MainW::createMenus()
{
	this->fileMenu = new QMenu(tr("&File"), this);
	this->newFileAct = new QAction(tr("&New File"), this);
	this->newFileAct->setShortcut(QKeySequence(QKeySequence::New));
	connect(this->newFileAct, SIGNAL(triggered(bool)), this, SLOT(newFileSlot()));
	this->fileMenu->addAction(this->newFileAct);

	this->openFileAct = new QAction(tr("&Open File"), this);
	this->openFileAct->setShortcut(QKeySequence(QKeySequence::Open));
	connect(this->openFileAct, SIGNAL(triggered(bool)), this, SLOT(openFileSlot()));
	this->fileMenu->addAction(this->openFileAct);

	this->saveFileAct = new QAction(tr("&Save"), this);
	this->saveFileAct->setShortcut(QKeySequence(QKeySequence::Save));
	connect(this->saveFileAct, SIGNAL(triggered(bool)), this, SLOT(saveFileSlot()));
	this->fileMenu->addAction(this->saveFileAct);

	this->menuBar()->addMenu(this->fileMenu);

	this->windowMenu = new QMenu(tr("&Window"), this);
	this->wordListWindowAct = new QAction(tr("Word &List"), this);
	this->wordListWindowAct->setShortcut(QKeySequence("Alt+L"));
	this->wordListWindowAct->setCheckable(true);
	connect(this->wordListWindowAct, SIGNAL(triggered(bool)), this, SLOT(wordListWindowSlot(bool)));
	this->windowMenu->addAction(this->wordListWindowAct);

	this->wordPadWindowAct = new QAction(tr("Word &Pad"), this);
	this->wordPadWindowAct->setShortcut(QKeySequence("Alt+W"));
	this->wordPadWindowAct->setCheckable(true);
	connect(this->wordPadWindowAct, SIGNAL(triggered(bool)), this, SLOT(wordPadWindowSlot(bool)));
	this->windowMenu->addAction(this->wordPadWindowAct);

	this->kanaPadWindowAct = new QAction(tr("&Kana Pad"), this);
	this->kanaPadWindowAct->setShortcut(QKeySequence("Alt+K"));
	this->kanaPadWindowAct->setCheckable(true);
	connect(this->kanaPadWindowAct, SIGNAL(triggered(bool)), this, SLOT(kanaPadWindowSlot(bool)));
	this->windowMenu->addAction(this->kanaPadWindowAct);

	this->menuBar()->addMenu(this->windowMenu);

	this->helpMenu = new QMenu(tr("&Help"), this);
	this->aboutAct = new QAction(tr("&About..."), this);
	this->aboutAct->setShortcut(QKeySequence("F11"));
	connect(this->aboutAct, SIGNAL(triggered(bool)), this, SLOT(aboutSlot()));
	this->helpMenu->addAction(this->aboutAct);

	this->aboutQtAct = new QAction(tr("About &Qt..."), this);
	this->aboutQtAct->setShortcut(QKeySequence("F12"));
	connect(this->aboutQtAct, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
	this->helpMenu->addAction(this->aboutQtAct);

	this->menuBar()->addMenu(this->helpMenu);
}

MainW::MainW(QWidget *parent)
	: QMainWindow(parent)
{
	this->resize(1024, 768);
	this->setWindowIcon(QIcon(":/data/image/logo.png"));
	this->setWindowTitle(ApplicationName);
	this->currentFocusWordPadLineEdit = nullptr;
	this->currentWordIndex = -1;
	this->wordListWidget = new WordlistWidget(this);
	this->wordPadWidget = new WordPadWidget(this);
	this->kanaPadWidget = new KanaPadWidget(this);
	this->previewWidget = new PreviewWidget(this);

	this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	this->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

	this->wordListDockWidget = new QDockWidget(tr("Word List"), this);
	wordListDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	wordListDockWidget->setWidget(this->wordListWidget);
	wordListDockWidget->setFeatures(/*QDockWidget::DockWidgetClosable |*/ QDockWidget::DockWidgetMovable);
	this->addDockWidget(Qt::LeftDockWidgetArea, wordListDockWidget);
	connect(this->wordListWidget, SIGNAL(hideSig()), this, SLOT(wordListCloseSlot()));

	this->wordPadDockWidget = new QDockWidget(tr("Word"), this);
	wordPadDockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
	wordPadDockWidget->setWidget(this->wordPadWidget);
	wordPadDockWidget->setFeatures(/*QDockWidget::DockWidgetClosable |*/ QDockWidget::DockWidgetMovable);
	this->addDockWidget(Qt::TopDockWidgetArea, wordPadDockWidget);
	connect(this->wordPadWidget, SIGNAL(lostFocus(QLineEdit*)), this, SLOT(wordPadLostFocus(QLineEdit*)));
	connect(this->wordPadWidget, SIGNAL(hideSig()), this, SLOT(wordPadCloseSlot()));

	this->kanaPadDockWidget = new QDockWidget(tr("Kana Pad"), this);
	kanaPadDockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
	kanaPadDockWidget->setWidget(this->kanaPadWidget);
	kanaPadDockWidget->setFeatures(/*QDockWidget::DockWidgetClosable |*/ QDockWidget::DockWidgetMovable);
	this->addDockWidget(Qt::BottomDockWidgetArea, kanaPadDockWidget);
	connect(this->kanaPadWidget, SIGNAL(kanaClicked(QString,bool)), this, SLOT(kanaPadClickedSlot(QString,bool)));
	connect(this->kanaPadWidget, SIGNAL(hideSig()), this, SLOT(kanaPadCloseSlot()));

	this->setCentralWidget(this->previewWidget);

	this->createMenus();

#ifdef __DEBUG__
	//QWidget *w = new QWidget(this);
	//this->setCentralWidget(w);

	//connect(this->kanaPadWidget, SIGNAL(kanaClicked(QString,bool)), this, SLOT(kanaClickedSlot(QString,bool)));
	//connect(this->wordPadWidget, SIGNAL(lostFocus(QLineEdit*)), this, SLOT(wordLostFocus(QLineEdit*)));
#endif

	this->fileNotOpenStatement();

	this->wordListWidget->clearList();

	connect(this->wordListWidget, SIGNAL(clicked(int)), this, SLOT(wordListClicked(int)));
	connect(this->wordListWidget, SIGNAL(removed(int)), this, SLOT(wordListRemoved(int)));
	connect(this->wordListWidget, SIGNAL(movedUp(int)), this, SLOT(wordListMovedUp(int)));
	connect(this->wordListWidget, SIGNAL(movedDown(int)), this, SLOT(wordListMovedDown(int)));
	connect(this->wordListWidget, SIGNAL(draged(int,int)), this, SLOT(wordListDraged(int,int)));
	connect(this->wordListWidget, SIGNAL(add(int)), this, SLOT(wordListAdded(int)));
	connect(this->wordListWidget, SIGNAL(listEmpty()), this, SLOT(wordListEmpty()));

	connect(this->wordPadWidget, SIGNAL(saveButtonClicked()), this, SLOT(saveToList()));
	connect(this->wordPadWidget, SIGNAL(textChangedSig(QString)), this->previewWidget, SLOT(setKanjiSlot(QString)));
}

MainW::~MainW()
{

}

void MainW::wordPadLostFocus(QLineEdit *w)
{
	this->currentFocusWordPadLineEdit = w;
}

void MainW::kanaPadClickedSlot(QString kana, bool e)
{
	Q_UNUSED(e);
	if(this->currentFocusWordPadLineEdit != nullptr){
		this->currentFocusWordPadLineEdit->insert(kana);
	}
}

#ifdef __DEBUG__
void MainW::kanaClickedSlot(QString kana, bool e)
{
	Q_UNUSED(e);
	QMessageBox::information(this, "KanaPad Clicked get in Main", QString("You Clicked this char just now:%1").arg(kana), QMessageBox::Ok);
}

void MainW::wordLostFocus(QLineEdit *w)
{
	w->insert("R");
	QMessageBox::information(this, "WordPad Lost Focus in Main", QString("QLineEdit's Text:%1").arg(w->text()), QMessageBox::Ok);
}
#endif

void MainW::newFileSlot()
{
	if(this->statement & FileModified){
		int cancelled = 0;
		int result = QMessageBox::question(this, ApplicationName, tr("You have modified the project, are you really want to create new file?"), QMessageBox::Yes | QMessageBox::Save | QMessageBox::Cancel);
		switch(result){
			case QMessageBox::Yes:
			case QMessageBox::Discard: cancelled = 0; break;
			case QMessageBox::Save:
				//save file
				{
					bool isSaved = this->saveFileSlot();
					if(isSaved == false){
						cancelled = 1;
					}
				}
				break;
			case QMessageBox::No:
			case QMessageBox::Cancel: cancelled = 1; break;
		}
		if(cancelled == 1){
			return;
		}
	}
	QString headName = QInputDialog::getText(this, ApplicationName, tr("Please enter this project's name:"));
	if(headName.isEmpty()){
		QMessageBox::warning(this, "Kanji Maker", tr("Please enter an name for this project."), QMessageBox::Ok);
		return;
	}
	this->head.name = headName;
	this->word.clear();
	this->wordListWidget->clearList();
	this->wordListWidget->setList(this->word);
	this->wordListWidget->setHead(this->head);
	//this->previewWidget->setFontSize(30);
	this->previewWidget->setKanji(tr("新しいエントリの左のリストをクリックします"));
	this->fileOpenStatement();
}

bool MainW::openFileSlot()
{
	if(this->statement & FileModified){
		int cancelled = 0;
		int result = QMessageBox::question(this,  ApplicationName, tr("You have modified the project, are you really want to open file?"), QMessageBox::Yes | QMessageBox::Save | QMessageBox::Cancel);
		switch(result){
			case QMessageBox::Yes:
			case QMessageBox::Discard: cancelled = 0; break;
			case QMessageBox::Save:
				//save file
				{
					bool isSaved = this->saveFileSlot();
					if(isSaved == false){
						cancelled = 1;
					}
				}
				break;
			case QMessageBox::No:
			case QMessageBox::Cancel: cancelled = 1; break;
		}
		if(cancelled == 1){
			return false;
		}
	}
	QString filename = QFileDialog::getOpenFileName(this, "Open Word File", QDir::currentPath(), "Kanji Word File(*.kji);;Kanji Json File(*.json);;All Files(*.*)");
	if(filename.isEmpty()){
		return false;
	}
	this->head.name.clear();
	this->word.clear();
	this->wordListWidget->clearList();
	ReadSaveFile readFile(filename);
	if(!readFile.loadFile(&this->word, &this->head)){
		QMessageBox::critical(this, ApplicationName, "This file is not vaild.", QMessageBox::Ok);
		return false;
	}
	this->fileOpenStatement();
	this->wordListWidget->setHead(this->head);
	this->wordListWidget->setList(this->word);
	//this->previewWidget->setFontSize(30);
	this->previewWidget->setKanji(tr("エントリを表示するには、左側のをクリックして"));
	return true;
}

bool MainW::saveFileSlot()
{
	if(this->word.isEmpty()){
		QMessageBox::information(this, ApplicationName, "Your word list is empty...", QMessageBox::Ok);
		return false;
	}
	if(this->statement & FileModified){
		QString filename = QFileDialog::getSaveFileName(this, "Save Word File", QDir::currentPath(), "Kanji Word File(*.kji);;Kanji Json File(*.json);;All Files(*.*)");
		ReadSaveFile saveFile(filename);
		if(!saveFile.saveFile(this->word, this->head)){
			QMessageBox::critical(this, ApplicationName, tr("Save Failed..."), QMessageBox::Ok);
			return false;
		}else{
			QMessageBox::information(this, ApplicationName, tr("Word File Saved."), QMessageBox::Ok);
			this->fileOpenStatement();
			return true;
		}
	}
	return false;
}

void MainW::wordListCloseSlot()
{
	this->wordListDockWidget->hide();
	this->wordListWindowAct->setChecked(false);
}

void MainW::wordPadCloseSlot()
{
	this->wordPadDockWidget->hide();
	this->wordPadWindowAct->setChecked(false);
}

void MainW::kanaPadCloseSlot()
{
	this->kanaPadDockWidget->hide();
	this->kanaPadWindowAct->setChecked(false);
}

void MainW::wordListWindowSlot(bool e)
{
	if(e){
		this->wordListDockWidget->show();
	}else{
		this->wordListDockWidget->hide();
	}
}

void MainW::wordPadWindowSlot(bool e)
{
	if(e){
		this->wordPadDockWidget->show();
	}else{
		this->wordPadDockWidget->hide();
	}
}

void MainW::kanaPadWindowSlot(bool e)
{
	if(e){
		this->kanaPadDockWidget->show();
	}else{
		this->kanaPadDockWidget->hide();
	}
}

void MainW::aboutSlot()
{
	AboutWidget about(this);
	about.exec();
}

void MainW::fileNotOpenStatement()
{
	this->saveFileAct->setEnabled(false);
	this->wordListDockWidget->hide();
	this->wordListWindowAct->setChecked(false);
	this->wordPadDockWidget->hide();
	this->wordPadWindowAct->setChecked(false);
	this->kanaPadDockWidget->hide();
	this->kanaPadWindowAct->setChecked(false);
	this->statement = FileNotOpen;
}

void MainW::fileOpenStatement()
{
	this->saveFileAct->setEnabled(false);
	this->wordListDockWidget->show();
	this->wordListWindowAct->setChecked(true);
	this->wordPadDockWidget->hide();
	this->wordPadWindowAct->setChecked(false);
	this->kanaPadDockWidget->show();
	this->kanaPadWindowAct->setChecked(true);
	this->statement = FileOpen;
}

void MainW::fileModifiedStatement()
{
	this->saveFileAct->setEnabled(true);
	this->statement = FileModified;
}

void MainW::wordModifiedStatement(){
	this->wordPadDockWidget->show();
	this->saveFileAct->setEnabled(true);
	this->statement = WordModified;
}

void MainW::wordListClicked(int index)
{
	qDebug() << "[DEBUG]MainW::wordListClicked word[" << index << "]";
	if(index >= this->word.length()){
		qDebug() << "Word List: index:" << index << "not found, will update word list.";
		this->wordListWidget->setList(this->word);
		return;
	}
	KanjiWord w = this->word.at(index);
	this->wordPadWidget->setKana(w.kana);
	this->wordPadWidget->setKanji(w.kanji);
	this->wordPadWidget->setChinese(w.chinese);
	this->wordPadWidget->setEnglish(w.english);
	//this->previewWidget->setFontSize(40);
	this->previewWidget->setKana(w.kana);
	this->previewWidget->setKanji(w.kanji);
	this->wordPadDockWidget->show();
	this->wordPadWindowAct->setChecked(true);
	this->currentWordIndex = index;
}

void MainW::wordListRemoved(int index)
{
	qDebug() << "[DEBUG]MainW::wordListRemoved word[" << index << "]";
	if(index >= this->word.length()){
		qDebug() << "Word List: index:" << index << "not found, will update word list.";
		this->wordListWidget->setList(this->word);
		return;
	}
	KanjiWord w = this->word.at(index);
	if(w.kana != this->wordPadWidget->getKana()){
		qDebug() << "Kanji Word: Kana:" << w.kana << "is not same to" << this->wordPadWidget->getKana();
		return;
	}
	if(w.kanji != this->wordPadWidget->getKanji()){
		qDebug() << "Kanji Word: Kanji:" << w.kanji << "is not same to" << this->wordPadWidget->getKanji();
		return;
	}
	if(w.chinese != this->wordPadWidget->getChinese()){
		qDebug() << "Kanji Word: Chinese:" << w.chinese << "is not same to" << this->wordPadWidget->getChinese();
		return;
	}
	if(w.english != this->wordPadWidget->getEnglish()){
		qDebug() << "Kanji Word: English:" << w.english << "is not same to" << this->wordPadWidget->getEnglish();
		return;
	}
	this->word.removeAt(index);

	this->wordListWidget->setList(this->word);
}

void MainW::wordListMovedUp(int index)
{
	qDebug() << "[DEBUG]MainW::wordListMovedUp word[" << index << "]";
	if(index >= this->word.length()){
		qDebug() << "Word List: index:" << index << "not found, will update word list.";
		this->wordListWidget->setList(this->word);
		return;
	}
	if(index == 0){
		qDebug() << "Word List: index:" << index << "is the first one. cannot move up.";
		return;
	}
	this->word.swap(index, index -1);
	this->wordListWidget->setList(this->word);
}

void MainW::wordListMovedDown(int index)
{
	qDebug() << "[DEBUG]MainW::wordListMovedDown word[" << index << "]";
	if(index >= this->word.length()){
		qDebug() << "Word List: index:" << index << "not found, will update word list.";
		this->wordListWidget->setList(this->word);
		return;
	}
	if(index == this->word.length() -1){
		qDebug() << "Word List: index:" << index << "is the last one. cannot move down.";
		return;
	}
	this->word.swap(index, index +1);
	this->wordListWidget->setList(this->word);
}

void MainW::wordListDraged(int from, int to)
{
	qDebug() << "[DEBUG]MainW::wordListDraged word[" << from << "] swapped with [" << to << "].";
	if(from >= this->word.length() || to >= this->word.length()){
		qDebug() << "Word List: index:" << from << "and:" << to << "not found, will update word list.";
		this->wordListWidget->setList(this->word);
		return;
	}
	this->word.swap(from, to);
	this->wordListWidget->setList(this->word);
}

void MainW::wordListAdded(int index)
{
	qDebug() << "[DEBUG]MainW::wordListAdded word[" << index << "]";
	KanjiWord w;
	if(index >= this->word.length()){
		this->word.append(w);
		this->wordListWidget->setList(this->word);
	}else{
		this->word.insert(index, w);
		this->wordListWidget->setList(this->word);
	}
}

void MainW::wordListEmpty()
{
	this->currentWordIndex = -1;
	this->wordPadWidget->setKana("");
	this->wordPadWidget->setKanji("");
	this->wordPadWidget->setChinese("");
	this->wordPadWidget->setEnglish("");
	this->previewWidget->setKana("");
	this->previewWidget->setKanji(tr("リストは空です"));
	this->wordPadDockWidget->hide();
	this->wordPadWindowAct->setChecked(false);
	this->kanaPadDockWidget->hide();
	this->kanaPadWindowAct->setChecked(false);
}

void MainW::saveToList()
{
	qDebug() << "[DEBUG]MainW::saveToList word[" << this->currentWordIndex << "]";
	if(this->currentWordIndex == -1){
		return;
	}
	this->word[this->currentWordIndex].kana = this->wordPadWidget->getKana();
	this->word[this->currentWordIndex].kanji = this->wordPadWidget->getKanji();
	this->word[this->currentWordIndex].chinese = this->wordPadWidget->getChinese();
	this->word[this->currentWordIndex].english = this->wordPadWidget->getEnglish();
	this->wordListWidget->setList(this->word);
	this->wordModifiedStatement();
}
