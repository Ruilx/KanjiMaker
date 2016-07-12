#include "mainw.h"

void MainW::createMenus()
{
	this->fileMenu = new QMenu(tr("File"), this);
	this->newFileAct = new QAction(tr("New File"), this);
	this->fileMenu->addAction(this->newFileAct);

	this->openFileAct = new QAction(tr("Open File"), this);
	this->fileMenu->addAction(this->openFileAct);

	this->menuBar()->addMenu(this->fileMenu);
}

MainW::MainW(QWidget *parent)
	: QMainWindow(parent)
{
	this->resize(1024, 768);
	this->currentFocusWordPadLineEdit = nullptr;
	this->wordListWidget = new WordlistWidget(this);
	this->wordPadWidget = new WordPadWidget(this);
	this->kanaPadWidget = new KanaPadWidget(this);
	this->previewWidget = new PreviewWidget(this);

	this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	this->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

	QDockWidget *wordListDockWidget = new QDockWidget(tr("Word List"), this);
	wordListDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	wordListDockWidget->setWidget(this->wordListWidget);
	wordListDockWidget->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
	this->addDockWidget(Qt::LeftDockWidgetArea, wordListDockWidget);

	QDockWidget *wordPadDockWidget = new QDockWidget(tr("Word"), this);
	wordPadDockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
	wordPadDockWidget->setWidget(this->wordPadWidget);
	wordPadDockWidget->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
	this->addDockWidget(Qt::TopDockWidgetArea, wordPadDockWidget);
	connect(this->wordPadWidget, SIGNAL(lostFocus(QLineEdit*)), this, SLOT(wordPadLostFocus(QLineEdit*)));

	QDockWidget *kanaPadDockWidget = new QDockWidget(tr("Kana Pad"), this);
	kanaPadDockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
	kanaPadDockWidget->setWidget(this->kanaPadWidget);
	kanaPadDockWidget->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
	this->addDockWidget(Qt::BottomDockWidgetArea, kanaPadDockWidget);
	connect(this->kanaPadWidget, SIGNAL(kanaClicked(QString,bool)), this, SLOT(kanaPadClickedSlot(QString,bool)));

	this->setCentralWidget(this->previewWidget);

	this->createMenus();

#ifdef __DEBUG__
	//QWidget *w = new QWidget(this);
	//this->setCentralWidget(w);

	//connect(this->kanaPadWidget, SIGNAL(kanaClicked(QString,bool)), this, SLOT(kanaClickedSlot(QString,bool)));
	//connect(this->wordPadWidget, SIGNAL(lostFocus(QLineEdit*)), this, SLOT(wordLostFocus(QLineEdit*)));
#endif

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
