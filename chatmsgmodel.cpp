#include "chatmsgmodel.h"
#include <QObject>

ChatMsgModel::ChatMsgModel(QObject *parent) : QAbstractListModel{parent}, m_msgDataSource(NULL), m_signalConnected(false)
{
    qDebug()<<"ChatMsgModel constructor";
    setchatMsgDataSource( new ChatMsgDataSource(this));
}

QHash<int, QByteArray> ChatMsgModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { UserNameRole, "userName" },
        { MsgRole, "msg" },
        };
    return roles;
}

int ChatMsgModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_msgDataSource->dataItems().size();
}

int ChatMsgModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_msgList.size() ? 1 : 0;
}

QVariant ChatMsgModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ChatMsg *msg = m_msgDataSource->dataItems().at(index.row())

    if (role == Qt::DisplayRole || role == UserNameRole)
        return msg->getUser();
    if (role == MsgRole)
        return msg->getMsg();

    return QVariant();
}

ChatMsgDataSource* ChatMsgModel::chatMsgDataSource(void) const
{
    return m_msgDataSource;
}

void ChatMsgModel::setChatMsgDataSource(ChatMsgDataSource *newMsgDataSource)
{
    beginResetModel();

    if( m_msgDataSource && m_signalConnected)
        m_msgDataSource->disconnect(this);

    m_msgDataSource = newMsgDataSource;

    connect(m_msgDataSource,&ChatMsgDataSource::preMsgAdded,this,[=](){
        const int index = newMsgDataSource->dataItems().size();
        beginInsertRows(QModelIndex(),index,index);
    });

    connect(m_msgDataSource,&ChatMsgDataSource::postMsgAdded,this,[=](){
        endInsertRows();
    });

    connect(m_msgDataSource,&ChatMsgDataSource::preMsgRemoved,this,[=](int index){
       beginRemoveRows(QModelIndex(), index, index);
    });

    connect(m_msgDataSource,&ChatMsgDataSource::postMsgRemoved,this,[=](){
       endRemoveRows();
    });

    m_signalConnected = true;

    endResetModel();
}






