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
	void setKana(const QString &kana);
	void setKanji(const QString &kanji);
	void setChinese(const QString &chinese);
	void setEnglish(const QString &english);
	QString getKana() const;
	QString getKanji() const;
	QString getChinese() const;
	QString getEnglish() const;
signals:
	void lostFocus(QLineEdit *w);
	void saveButtonClicked();
public slots:
	bool eventFilter(QObject *watched, QEvent *event);
private slots:
};

#endif // WORDPADWIDGET_H
