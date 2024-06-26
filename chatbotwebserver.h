#ifndef CHATBOTWEBSERVER_H
#define CHATBOTWEBSERVER_H

#include <QObject>
#include <QHttpServer>

class ChatBotWebServer
{
public:
    ChatBotWebServer();
    int start(void);
    void addRoute(const QString &path);
private:
    QHttpServer _server;
};

#endif // CHATBOTWEBSERVER_H
