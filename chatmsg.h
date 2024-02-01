#ifndef CHATMSG_H
#define CHATMSG_H

#include <QString>
#include <QDateTime>

class ChatMsg
{
public:
    ChatMsg(QString user, QString msg);

    QString getUser() const;
    QDateTime getTimestamp() const;
    QString getMsg() const;

private:
    QString user;
    QDateTime timestamp;
    QString msg;
};

#endif // CHATMSG_H
