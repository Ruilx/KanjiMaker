#ifndef MAINW_H
#define MAINW_H

#define __DEBUG__

#include <QMainWindow>
#include "wordlistwidget.h"
#include "wordpadwidget.h"
#include "kanapadwidget.h"
#include "previewwidget.h"
#include "core/structure.h"
#include "core/readsavefile.h"
#include "aboutwidget.h"

class MainW : public QMainWindow
{
	Q_OBJECT
	enum Statement{
		FileNotOpen = 0x01,
		FileOpen = 0x02,
		FileModified = 0x04,
		WordEditted = 0x08,
		WordModified = WordEditted | FileModified,
	};
	Statement statement;

	WordlistWidget *wordListWidget;
	QDockWidget *wordListDockWidget;
	WordPadWidget *wordPadWidget;
	QDockWidget *wordPadDockWidget;
	KanaPadWidget *kanaPadWidget;
	QDockWidget *kanaPadDockWidget;
	PreviewWidget *previewWidget;

	QLineEdit *currentFocusWordPadLineEdit;

	QMenu *fileMenu;
	QAction *newFileAct;
	QAction *openFileAct;
	QAction *saveFileAct;

	QMenu *windowMenu;
	QAction *wordListWindowAct;
	QAction *wordPadWindowAct;
	QAction *kanaPadWindowAct;

	QMenu *helpMenu;
	QAction *aboutAct;
	QAction *aboutQtAct;

	int currentWordIndex;
	QList<KanjiWord> word;
	Head head;

	void createMenus();
	void closeEvent(QCloseEvent *event);
public:
	MainW(QWidget *parent = 0);
	~MainW();

private slots:
	void wordPadLostFocus(QLineEdit *w);
	void kanaPadClickedSlot(QString kana, bool e);
#ifdef __DEBUG__
	void kanaClickedSlot(QString kana, bool e);
	void wordLostFocus(QLineEdit *w);
#endif
	void newFileSlot();
	bool openFileSlot();
	bool saveFileSlot();

	void wordListCloseSlot();
	void wordPadCloseSlot();
	void kanaPadCloseSlot();
	void wordListWindowSlot(bool e);
	void wordPadWindowSlot(bool e);
	void kanaPadWindowSlot(bool e);

	void aboutSlot();

private slots:
	void fileNotOpenStatement();
	void fileOpenStatement();
	void fileModifiedStatement();
	void wordModifiedStatement();

	void wordListClicked(int index);
	void wordListRemoved(int index);
	void wordListMovedUp(int index);
	void wordListMovedDown(int index);
	void wordListDraged(int from, int to);
	void wordListAdded(int index);
	void wordListEmpty();

	void saveToList();


};

#endif // MAINW_H
