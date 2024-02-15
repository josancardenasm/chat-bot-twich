#ifndef TWICHIRCCLIENT_H
#define TWICHIRCCLIENT_H


#include <QObject>
#include <QtCore>
#include <QtWebSockets/QWebSocket>
#include <chatmsg.h>

class TwichIRCClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ isConnected WRITE setConnected NOTIFY connectedChanged)

public:
    TwichIRCClient();
    bool isConnected(void);
    void setConnected(bool isConnected);
    void sendString(QString string);

signals:
    void connectedChanged(void);
    void connected();
    void disconnected();
    void newMsgAdded (ChatMsg msg);

public slots:
    void connect(QString token, QString username, QString channel_name);
    void disconnect(void);

private:
    bool m_connected;
    bool m_connectedRequest;
    QString oauth_token;
    QString username;
    QString channel;
    QWebSocket webSocket;
    QList<ChatMsg> msgPool;
    size_t msgMaxPoolSize;

    void addCommand(ChatMsg msg);
    void processCommand (const QString &msg);
    void onPingCommand(const QString &msg);
    void onPrivmsgCommand (const QString &msg);
    void reconnect(void);

};

#endif // TWICHIRCCLIENT_H
