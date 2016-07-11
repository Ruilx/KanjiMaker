#ifndef KANAPUSHBUTTON_H
#define KANAPUSHBUTTON_H

#include <QtWidgets>
#include <QPushButton>

class KanaPushButton : public QPushButton
{
	Q_OBJECT

	QString name;
public:
	KanaPushButton(const QString &name, QWidget *parent);
signals:
	void clicked(QString name, bool e);
private slots:
	void clickedSlot(bool e);
};

#endif // KANAPUSHBUTTON_H
