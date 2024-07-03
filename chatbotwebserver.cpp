#include "chatbotwebserver.h"

#include <QFile>
#include <QMimeDatabase>
#include <QMimeType>

#define PORT 3000

QString loadHtmlFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }
    QTextStream in(&file);
    return in.readAll();
}

ChatBotWebServer::ChatBotWebServer() {}

int ChatBotWebServer::start()
{
    //AuthServer
    addRoute("auth");

    //Listen
    qDebug() << "Starting web server on http://localhost:" << PORT;
    if (!_server.listen(QHostAddress::Any, PORT)) {
        qCritical() << "Could not start server";
        return -1;
    }

    qDebug() << "Server is running on http://localhost:" << PORT;
    return 0;
}

void ChatBotWebServer::addRoute(const QString &path)
{
    _server.route("/" + path, [path]() {
        QString qstr_uurl = ":/geeking.dev/imports/chat-bot-twich/resources/web/auth/index.html";
        QString htmlContent = loadHtmlFile(qstr_uurl);
        if (htmlContent.isEmpty()) {
            qDebug() << qstr_uurl + " was not found!";
            return QHttpServerResponse("text/plain", "File not found", QHttpServerResponse::StatusCode::NotFound);
        }
        return QHttpServerResponse("text/html", htmlContent.toUtf8());
    });

    // Route to serve other files in the html directory
    _server.route("/" + path + "<arg>", [path](const QString &arg) {
        QString filePath = "resources/web/" + path + arg;
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            return QHttpServerResponse("text/plain", "File not found", QHttpServerResponse::StatusCode::NotFound);
        }

        // Determine the mime type
        QMimeDatabase mimeDatabase;
        QMimeType mimeType = mimeDatabase.mimeTypeForFile(filePath);

        return QHttpServerResponse(mimeType.name().toUtf8(), file.readAll());
    });
}
