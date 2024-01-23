#ifndef TWICHIRCCLIENT_H
#define TWICHIRCCLIENT_H

#include <QtWebSockets/QWebSocket>

class TwichIRCClient
{
public:
    TwichIRCClient();
    bool connect(QUrl url);
    bool disconnect(void);
private:
    QWebSocket webSocket;
};

#endif // TWICHIRCCLIENT_H
