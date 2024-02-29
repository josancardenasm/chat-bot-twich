#ifndef TWICHIRCCLIENT_H
#define TWICHIRCCLIENT_H


#include <QObject>
#include <QtCore>
#include <QtWebSockets/QWebSocket>
#include <chatmsg.h>


typedef enum
{
    TWIRC_DISCONNECTED,
    TWIRC_CONNECTING,
    TWIRC_CONNECTED,
    TWIRC_DISCONNECTING
}ConnectedState;

class TwichIRCClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ConnectedState connectedState READ connectedState NOTIFY connectedStateChanged)

public:
    TwichIRCClient();
    void sendString(QString string);
    ConnectedState connectedState(void);

signals:
    void connectedStateChanged(ConnectedState state);
    void newMsgAdded (ChatMsg msg);

public slots:
    void connect(QString token, QString username, QString channel_name);
    void disconnect(void);

private:
    QString oauth_token;
    QString username;
    QString channel;
    ConnectedState m_connectedState;
    ConnectedState m_connectedStateLast;

    QWebSocket webSocket;
    void addCommand(ChatMsg msg);
    void processCommand (const QString &msg);
    void onPingCommand(const QString &msg);
    void onPrivmsgCommand (const QString &msg);
    void reconnect(void);

};

#endif // TWICHIRCCLIENT_H
