#include "chatmsgdatasource.h"

ChatMsgDataSource::ChatMsgDataSource(QObject *parent)
    : QObject{parent}, m_filters(NULL), m_twitchIRCClient(NULL)
{
}

QList<QSharedPointer<ChatMsg>> ChatMsgDataSource::dataItems()
{
    return m_msgList;
}

void ChatMsgDataSource::addMsg(QSharedPointer<ChatMsg> msg)
{
    qDebug()<<"ChatMsgDataSource: Received msg from " + msg->getUser() + " with content " + msg->getMsg();
    emit preMsgAdded();
    m_msgList.append(msg);
    emit postMsgAdded();
}

void ChatMsgDataSource::addMsg(ChatMsg* msg)
{
    if(msg == NULL)
    {
        qFatal()<<"ChatMsgDataSource: null msg!";
        return;
    }

    addMsg(QSharedPointer<ChatMsg>(msg));
}

void ChatMsgDataSource::addMsg(ChatMsg msg)
{
    addMsg(QSharedPointer<ChatMsg>(new ChatMsg(msg)));
}

void ChatMsgDataSource::removeMsg(int index)
{
    if(index >= m_msgList.size())
    {
        qDebug() << "removeMsg index is not in range";
        return;
    }

    emit preMsgRemoved(index);
    m_msgList.remove(index);
    emit postMsgRemoved();
}



void ChatMsgDataSource::setTwichIRCClient(TwichIRCClient *newIrcClient)
{
    qDebug()<<"ChatMsgDataSource::setIrcClient";
    if (m_twitchIRCClient != newIrcClient) {
        QMetaObject::Connection connection = QObject::connect(newIrcClient, &TwichIRCClient::newMsgAdded, [&](ChatMsg msg) {
            qDebug()<<"ChatMsgDataSource: Received msg from " + msg.getUser() + " with content " + msg.getMsg();

            //Hack
            if(!msg.getMsg().toLower().contains("!pregunta"))
                return;
            //End Hack

            addMsg(msg);
        });

        if(!connection)
            return;

        if(m_twitchIRCClient)
            QObject::disconnect(this->m_newMsgConnection);

        this->m_newMsgConnection = connection;
        m_twitchIRCClient = newIrcClient;
        emit twichIRCClientChanged();
    }
}

TwichIRCClient *ChatMsgDataSource::twichIRCClient() const
{
    return m_twitchIRCClient;
}

