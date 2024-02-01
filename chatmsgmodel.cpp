#include "chatmsgmodel.h"
#include <QObject>

ChatMsgModel::ChatMsgModel(QObject *parent) : QAbstractListModel{parent}, m_ircClient(NULL)
{
    qDebug()<<"ChatMsgModel constructor...";
}

void ChatMsgModel::removeMsg(size_t index)
{
    if(index >= m_msgList.size())
    {
        qDebug() << "removeMsg index is not in range";
        return;
    }

    m_msgList.remove(index);
}

void ChatMsgModel::addMsg(ChatMsg msg)
{
    qDebug()<<"ChatMsgModel: Received msg from " + msg.getUser() + " with content " + msg.getMsg();
    m_msgList.append(msg);
}

void ChatMsgModel::setIrcClient(TwichIRCClient *newIrcClient)
{
    qDebug()<<"ChatMsgModel::setIrcClient";
    if (m_ircClient != newIrcClient) {

        //QMetaObject::Connection connection = QObject::connect(newIrcClient, SIGNAL(newMsgAdded), this, SLOT(addMsg));
        QMetaObject::Connection connection = QObject::connect(newIrcClient, &TwichIRCClient::newMsgAdded, [&](ChatMsg msg) {
            qDebug()<<"ChatMsgModel: Received msg from " + msg.getUser() + " with content " + msg.getMsg();

            //Hack
            if(!msg.getMsg().toLower().contains("!pregunta"))
                return;
            //End Hack

            beginResetModel();
            m_msgList.append(msg);
            endResetModel();
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

TwichIRCClient *ChatMsgModel::twichIRCClient() const
{
    return m_ircClient;
}

QHash<int, QByteArray> ChatMsgModel::roleNames() const
{
    static const QHash<int, QByteArray> names {
        { UserNameRole, "userName" },
        { MsgRole, "msg" },
        };
    return names;
}

int ChatMsgModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_msgList.size();
}

int ChatMsgModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_msgList.size() ? 1 : 0;
}

QVariant ChatMsgModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);

    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == UserNameRole) {
        return m_msgList.at(index.row()).getUser();
    }

    if (role == MsgRole) {
        return m_msgList.at(index.row()).getMsg();
    }

    return QVariant();
}




