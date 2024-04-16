#ifndef CHATMSGDATASOURCE_H
#define CHATMSGDATASOURCE_H

#include <QObject>
#include <chatmsg.h>
#include <filterdatasource.h>
#include <twichircclient.h>

class ChatMsgDataSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TwichIRCClient* twichIRCClient READ twichIRCClient WRITE setTwichIRCClient NOTIFY twichIRCClientChanged)
public:
    explicit ChatMsgDataSource(QObject *parent = nullptr);
    QList<ChatMsg *> dataItems();
    void addMsg( ChatMsg *msg);
    Q_INVOKABLE void removeMsg(int index);
    void setTwichIRCClient(TwichIRCClient *newIrcClient);
    TwichIRCClient* twichIRCClient(void) const;

signals:
    void preMsgAdded();
    void postMsgAdded();
    void preMsgRemoved(int index);
    void postMsgRemoved();
    void twichIRCClientChanged();

private:
    QList<ChatMsg *> m_msgList;
    FilterDataSource *m_filters;
    QPointer<TwichIRCClient> m_ircClient;
    QMetaObject::Connection m_newMsgConnection;
};

#endif // CHATMSGDATASOURCE_H
