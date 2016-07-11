#ifndef WORDPADWIDGET_H
#define WORDPADWIDGET_H

#include <QtWidgets>
#include "com/lineedit.h"

class WordPadWidget : public QWidget
{
	Q_OBJECT

	QLabel *kanaLabel;
	QLabel *kanjiLabel;
	QLabel *chineseLabel;
	QLabel *englishLabel;
	LineEdit *kanaEdit;
	LineEdit *kanjiEdit;
	LineEdit *chineseEdit;
	LineEdit *englishEdit;

	QPushButton *saveButton;

	//void focusOutEvent(QFocusEvent *event);
public:
	explicit WordPadWidget(QWidget *parent = 0);

signals:
	void lostFocus(QLineEdit *w);
public slots:
	bool eventFilter(QObject *watched, QEvent *event);
private slots:
};

#endif // WORDPADWIDGET_H
