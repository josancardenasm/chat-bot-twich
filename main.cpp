#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <chatbot.h>
#include <twichircclient.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    /*
    Custom app startup
    */

    Chatbot chatbot;
    engine.rootContext()->setContextProperty("chatbot", &chatbot);

    TwichIRCClient irc;
    irc.connect(QUrl("wss://irc-ws.chat.twitch.tv:443"));


    /*
    End of custom startup
    */


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("chat-bot-twich", "Main");

    return app.exec();
}
