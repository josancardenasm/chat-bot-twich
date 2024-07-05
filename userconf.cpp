#include "userconf.h"
#include <QStandardPaths>
#include <QDir>

#define SETTINGS_FORMTAT_DEFAULT    QSettings::IniFormat

UserConf::UserConf(): _settings(NULL)
{
    _settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION, APP_NAME);
}

UserConf::~UserConf()
{
    delete _settings;
}

QString UserConf::getAccess_token() const
{
    return _settings->value("auth/access_token").toString();
}

void UserConf::setAccess_token(const QString &newAccess_token)
{
    _settings->setValue("auth/access_token", newAccess_token);
}
