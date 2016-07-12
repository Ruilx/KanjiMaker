#ifndef MAINW_H
#define MAINW_H

#define __DEBUG__

#include <QMainWindow>
#include "wordlistwidget.h"
#include "wordpadwidget.h"
#include "kanapadwidget.h"
#include "previewwidget.h"

class MainW : public QMainWindow
{
	Q_OBJECT
	WordlistWidget *wordListWidget;
	WordPadWidget *wordPadWidget;
	KanaPadWidget *kanaPadWidget;
	PreviewWidget *previewWidget;

	QLineEdit *currentFocusWordPadLineEdit;

	QMenu *fileMenu;
	QAction *newFileAct;
	QAction *openFileAct;

	void createMenus();
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
};

#endif // MAINW_H
