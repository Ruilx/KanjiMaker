#ifndef ABOUT_H
#define ABOUT_H

#include <QtCore>

#define ApplicationName QObject::tr("Kanji Maker")
#define OrganizationName "GT-Soft Studio"
#define AuthorName "Ruilx"
#define AuthorEmail "zrrabbit@gmail.com"
#define AuxiliaryName "zhiyb"
#define AuxiliaryEmail "zhiyb@qq.com"
#define ApplicationBugReportEmail "zrrabbit@gmail.com"
#define WebPage "http://www.Ruilx.pw"
#define UsingLicense "GNU General Public License"
#define UsingLicenseVersion 0x00000300
#define UsingSDK "Qt"
#define UsingSDKVersion QT_VERSION
#define ApplicationVersion 0x0A01025E60
//                            | | | +-Revised Version (Patch)
//                            | | +---Minor Version
//                            | +-----Major Version
//                            +-------Edition:
//  0x00 = Stable
//  0x01 = Standard
//  0x0A = Alpha
//  0x0B = Beta
//  0x0C = Commercial (OpenSource)
//  0x0D = Develop
//  0x0E = Enhance
//  0x0F = Final
//  0x10 = Release
//  0x11 = RC (Release Candidate)
#define Version ApplicationVersion
#define ApplicationLanguage 0x1033

#endif // ABOUT_H
