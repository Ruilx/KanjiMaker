#include "aboutwidget.h"

void AboutWidget::mouseReleaseEvent(QMouseEvent *e)
{
	static quint8 count = 0;
	if(e->button() == Qt::LeftButton){
		if(count < 10){
			count++;
		}
		QPoint p = QPoint(this->pos().x(), this->pos().y());
		QPoint p2 = QPoint(this->pos().x(), this->pos().y());
		QPoint p3 = QPoint(this->pos().x(), this->pos().y() + 15);
		QPoint p4 = QPoint(this->pos().x(), this->pos().y() - 15);

//		QSize s = this->size();
//		QSize s2 = QSize(this->size().width(), this->size().height() + 100);

//		QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
//		animation->setDuration(200);
//		animation->setEasingCurve(QEasingCurve::OutBack);
//		animation->setStartValue(s2);
//		animation->setEndValue(s);

		QPropertyAnimation *animation2 = new QPropertyAnimation(this, "pos");
		animation2->setDuration(300);
		animation2->setEasingCurve(QEasingCurve::InOutBack);
		animation2->setStartValue(p2);
		animation2->setEndValue(p);
		animation2->setKeyValueAt(0.25, p3);
		animation2->setKeyValueAt(0.5, p);
		animation2->setKeyValueAt(0.75, p4);

		QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
//		group->addAnimation(animation);
		group->addAnimation(animation2);

		group->start(/*QAbstractAnimation::DeleteWhenStopped*/);
		//animation2->start();
	}
	QDialog::mouseReleaseEvent(e);
	if(count >=5 && count < 10){
		this->setWindowTitle(tr("Press [Enter] to close the window. Or click this ->"));
	}else if(count >= 10){
		this->close();
	}

}

void AboutWidget::keyReleaseEvent(QKeyEvent *e)
{
	qDebug() << e->key() << Qt::Key_Return;
	if(e->key() == Qt::Key_Return){
		this->close();
	}
	QDialog::keyReleaseEvent(e);
}

AboutWidget::AboutWidget(QWidget *parent) : QDialog(parent)
{
	this->setFont(QFont(tr("Microsoft YaHei"), 9));

	Qt::WindowFlags flags=Qt::Dialog;
	flags |=Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	this->title = new QLabel(ApplicationName, this);
	this->title->setFont(QFont(tr("Microsoft YaHei"), 11, 100));
	const QString editionStrTable[] = {
		QString("Stable"),
		QString("Standard"),
		QString("2"),
		QString("3"),
		QString("4"),
		QString("5"),
		QString("6"),
		QString("7"),
		QString("8"),
		QString("9"),
		QString("Alpha"),
		QString("Beta"),
		QString("Commercial"),
		QString("Develop"),
		QString("Enhance"),
		QString("Final"),
		QString("Release"),
		QString("Release Candidate"),
	};
	uint edition = (ApplicationVersion & 0xFF000000) >> 24;
	QString editionStr = edition > 0x11 ? QString("Unknown") : editionStrTable[edition];
	uint majorVersion = (ApplicationVersion & 0x00FF0000) >> 16;
	uint minorVersion = (ApplicationVersion & 0x0000FF00) >> 8;
	uint revisedVersion = (ApplicationVersion & 0x000000FF);

	uint qtMajorVersion = (UsingSDKVersion & 0x00FF0000) >> 16;
	uint qtMinorVersion = (UsingSDKVersion & 0x0000FF00) >> 8;
	uint qtPatchVersion = (UsingSDKVersion & 0x000000FF);

	this->version = new QLabel(tr("Version: %1.%2.%3(%4) (Based On %5(%6.%7.%8))")
							   .arg(majorVersion).arg(minorVersion).arg(revisedVersion)
							   .arg(editionStr)
							   .arg(UsingSDK)
							   .arg(qtMajorVersion).arg(qtMinorVersion).arg(qtPatchVersion), this);
	this->author = new QLabel(tr("Made By %1<%2>, %3<%4>")
							  .arg(AuthorName).arg(AuthorEmail)
							  .arg(AuxiliaryName).arg(AuxiliaryEmail), this);
	this->webPage = new QLabel(tr("Website: %1").arg(WebPage), this);

	uint licenseMajorVersion = (UsingLicenseVersion & 0x0000FF00) >> 8;
	uint licenseMinorVersion = (UsingLicenseVersion & 0x000000FF);

	this->license = new QLabel(tr("License: %1 version %2.%3")
							   .arg(UsingLicense).arg(licenseMajorVersion).arg(licenseMinorVersion), this);

	this->repo = new QLabel("Repo: <a href='http://github.com/Ruilx/KanjiMaker'>http://github.com/Ruilx/KanjiMaker</a>", this);

	connect(this->repo, SIGNAL(linkActivated(QString)), this, SLOT(openRepoSlot(QString)));

	this->logo = new QLabel(this);
	this->logo->setPixmap(QPixmap(":/data/image/logo.png"));

	QGridLayout *lay = new QGridLayout;
	this->setLayout(lay);
	lay->addWidget(this->logo, 0, 0, 6, 1, Qt::AlignHCenter);
	lay->addWidget(this->title, 0, 1, 1, 1, Qt::AlignLeft);
	lay->addWidget(this->version, 1, 1, 1, 1, Qt::AlignLeft);
	lay->addWidget(this->author, 2, 1, 1, 1, Qt::AlignLeft);
	lay->addWidget(this->webPage, 3, 1, 1, 1, Qt::AlignLeft);
	lay->addWidget(this->license, 4, 1, 1, 1, Qt::AlignLeft);
	lay->addWidget(this->repo, 5, 1, 1, 1, Qt::AlignLeft);

	this->setWindowTitle(tr("About %1").arg(ApplicationName));

	this->layout()->setSizeConstraint(QLayout::SetFixedSize);

}

void AboutWidget::openRepoSlot(const QString &link)
{
	QDesktopServices::openUrl(QUrl(link));
}
