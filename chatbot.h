#ifndef CHATBOT_H
#define CHATBOT_H

#include <QObject>
#include <QStringList>

class Chatbot : public QObject
{
    Q_OBJECT
public:
    explicit Chatbot(QObject *parent = nullptr);

public slots:
    void addKeyword(const QString &keyword);
    void processChatMessage(const QString &message);

signals:
    void messageReceived(const QString &message);

private:
    QStringList keywordList;
};

#endif // CHATBOT_H
