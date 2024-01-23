#include "chatbot.h"
#include "qdebug.h"

Chatbot::Chatbot(QObject *parent) : QObject(parent) {}

void Chatbot::addKeyword(const QString &keyword) {
    keywordList.append(keyword.toLower());
    qDebug() << "Hola!";
    qDebug() << "Keyword agregado:" << keyword;
}

void Chatbot::processChatMessage(const QString &message) {
    for (const QString &keyword : keywordList) {
        if (message.toLower().contains(keyword)) {
            emit messageReceived(message);
            return;
        }
    }
}
