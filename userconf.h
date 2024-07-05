#ifndef USERCONF_H
#define USERCONF_H

#include <QObject>
#include <QSettings>

#define ORGANIZATION "Geeking.dev"
#define APP_NAME "chat-bot-twitch"

class UserConf
{
public:
    UserConf();
    ~UserConf();

    QString getAccess_token() const;
    void setAccess_token(const QString &newAccess_token);

private:
    QSettings *_settings;
};

#endif // USERCONF_H
