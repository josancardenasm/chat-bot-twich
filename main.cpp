#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
//#include <chatbot.h>
#include <twichircclient.h>
#include <twichapi.h>

#include <QFile>
#include <QTextStream>

void messageHander(QtMsgType type, const QMessageLogContext& context, const QString& message) {
    QString levelText;
    switch (type) {
    case QtDebugMsg:
        levelText = "Debug";
        break;
    case QtInfoMsg:
        levelText = "Info";
        break;
    case QtWarningMsg:
        levelText = "Warning";
        break;
    case QtCriticalMsg:
        levelText = "Critical";
        break;
    case QtFatalMsg:
        levelText = "Fatal";
        break;
    }
    QString text = QString("[%1] %2")
                       .arg(levelText)
                       .arg(message);
    QFile file("app.log");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&file);
    textStream << text << Qt::endl;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //qInstallMessageHandler(messageHander);

    QQmlApplicationEngine engine;

    /*
    Custom app startup
    */

    // Chatbot chatbot;
    // engine.rootContext()->setContextProperty("chatbot", &chatbot);

    TwichAPI twichapi;
    engine.rootContext()->setContextProperty("twichapi", &twichapi);

    TwichIRCClient twichircclient;
    engine.rootContext()->setContextProperty("twichircclient", &twichircclient);



    // AthorizationForm authForm;
    // engine.rootContext()->setContextProperty("AuthorizationForm", &authForm);

    // TwichIRCClient irc;
    // irc.connect(QUrl("wss://irc-ws.chat.twitch.tv:443"));


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
