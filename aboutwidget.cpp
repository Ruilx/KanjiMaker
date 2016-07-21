#include "aboutwidget.h"

void AboutWidget::resizeEvent(QResizeEvent *e)
{
	qDebug() << e->size();
}

AboutWidget::AboutWidget(QWidget *parent) : QDialog(parent)
{
	this->setFixedSize(491, 156);
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

	this->repo = new QLabel("Repo: http://github.com/Ruilx/KanjiMaker", this);

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

}
