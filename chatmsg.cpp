#include "chatmsg.h"

ChatMsg::ChatMsg(QString user, QString msg)
{
    this->user = user;
    this->msg = msg;

    this->timestamp = QDateTime::currentDateTime();
}

QString ChatMsg::getUser() const
{
    return user;
}

QDateTime ChatMsg::getTimestamp() const
{
    return timestamp;
}

QString ChatMsg::getMsg() const
{
    return msg;
}
