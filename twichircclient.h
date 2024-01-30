#ifndef TWICHIRCCLIENT_H
#define TWICHIRCCLIENT_H


#include <QObject>
#include <QtCore>
#include <QtWebSockets/QWebSocket>

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

public slots:
    void connect(QString token, QString username, QString channel_name);
    void disconnect(void);

private:
    bool m_connected;
    QString oauth_token;
    QString username;
    QString channel;
    QWebSocket webSocket;
};

#endif // TWICHIRCCLIENT_H
