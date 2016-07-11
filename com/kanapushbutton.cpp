#include "kanapushbutton.h"

KanaPushButton::KanaPushButton(const QString &name, QWidget *parent): QPushButton(parent)
{
	this->name = name;
	connect(this, SIGNAL(clicked(bool)), this, SLOT(clickedSlot(bool)));
}

void KanaPushButton::clickedSlot(bool e)
{
	emit clicked(this->name, e);
}
