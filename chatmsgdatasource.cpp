#include "chatmsgdatasource.h"

ChatMsgDataSource::ChatMsgDataSource(QObject *parent)
    : QObject{parent}, m_filters(NULL), m_twitchIRCClient(NULL)
{
    
    //setIrcClient(new TwichIRCClient(this));
}

QList<ChatMsg *> ChatMsgDataSource::dataItems()
{
    return m_msgList;
}

void ChatMsgDataSource::addMsg( ChatMsg *msg)
{
    if(msg == NULL)
    {
        qError()<<"ChatMsgDataSource: null msg!"
        return;
    }
        
    qDebug()<<"ChatMsgDataSource: Received msg from " + msg->getUser() + " with content " + msg->getMsg();
    emit preMsgAdded();
    m_msgList.append(msg);
    emit postMsgAdded();
}

void ChatMsgDataSource::removeMsg(size_t index)
{
    if(index >= m_msgList.size())
    {
        qDebug() << "removeMsg index is not in range";
        return;
    }

    emit preMsgRemoved(index);
    m_msgList.remove(index);
    emit postMsgRemoved();
    //TODO: free???
}



void ChatMsgDataSource::setTwichIRCClient(TwichIRCClient *newIrcClient)
{
    qDebug()<<"ChatMsgDataSource::setIrcClient";
    if (m_ircClient != newIrcClient) {
        //QMetaObject::Connection connection = QObject::connect(newIrcClient, SIGNAL(newMsgAdded), this, SLOT(addMsg));
        QMetaObject::Connection connection = QObject::connect(newIrcClient, &TwichIRCClient::newMsgAdded, [&](ChatMsg msg) {
            qDebug()<<"ChatMsgDataSource: Received msg from " + msg.getUser() + " with content " + msg.getMsg();

            //Hack
            if(!msg.getMsg().toLower().contains("!pregunta"))
                return;
            //End Hack

            //TODO:puntero?
            addMsg(msg);
        });

        if(!connection)
            return;

        if(m_ircClient)
            QObject::disconnect(this->m_newMsgConnection);

        this->m_newMsgConnection = connection;
        m_ircClient = newIrcClient;
        emit twichIRCClientChanged();
    }
}

TwichIRCClient *ChatMsgDataSource::twichIRCClient() const
{
    return m_ircClient;
}

