#ifndef CHATMSGMODEL_H
#define CHATMSGMODEL_H

#include <QAbstractListModel>
#include <twichircclient.h>
#include <chatmsg.h>
#include <QtCore>
#include <QtQml/qqml.h>

class ChatMsgModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(TwichIRCClient* twichIRCClient READ twichIRCClient WRITE setIrcClient NOTIFY twichIRCClientChanged)

public:
    explicit ChatMsgModel(QObject *parent = nullptr);
    void setIrcClient(TwichIRCClient *newIrcClient);
    TwichIRCClient* twichIRCClient(void) const;

    //Roles enumeration
    enum {
        UserNameRole = Qt::UserRole + 1,    //User Name
        MsgRole,                            //Content of the message
    };

    //Overrides
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

public slots:
    void removeMsg(size_t index);
    void addMsg(ChatMsg msg);

signals:
    void twichIRCClientChanged();

private:
    QMetaObject::Connection m_newMsgConnection;
    QPointer<TwichIRCClient> m_ircClient;
    QList<ChatMsg> m_msgList;   //La lista de mensajes
};

#endif // CHATMSGMODEL_H
