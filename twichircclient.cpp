#include "twichircclient.h"
#include <QObject>

#define MSG_POOL_SIZE_DEFAULT 5000

void TwichIRCClient::onPrivmsgCommand (const QString &msg)
{
    //ChatMsg msg
    //:foo!foo@foo.tmi.twitch.tv PRIVMSG #bar :bleedPurple
    //"foo" wrote a message. So it's the user
    //PRIVMSG is the command
    //msg

    static QRegularExpression re(R"(:([^!]*)![^ ]* PRIVMSG #([^ ]*) :([^\r]*))");
    QRegularExpressionMatch match = re.match(msg);
    if(!match.hasMatch()){
        qDebug()<<"PRIVMSG doesn't match with regex";
        return;
    }

    QString matchedUserName = match.captured(1);
    QString matchedChannelName = match.captured(2);
    QString matchedMsg = match.captured(3);

    qDebug() << "Captured: User=(" + matchedUserName + "); matchedChannelName=(" + matchedChannelName + "); matchedMsg=(" + matchedMsg + ")";

    ChatMsg decodedMsg = ChatMsg(matchedUserName, matchedMsg);
    emit newMsgAdded(decodedMsg);
}

void TwichIRCClient::onPingCommand(const QString &msg)
{
    QString response = "PONG " + msg.sliced(5);
    qDebug()<< "Processing onPingCommand response=(" << response << ")";
    this->sendString(response);
}

void TwichIRCClient::addCommand(ChatMsg msg)
{
    // if((msgPool.size() + 1) >= msgMaxPoolSize)
    // {
    //     msgPool.removeFirst();
    // }

    // msgPool.append(msg);
    emit newMsgAdded(msg);
}

void TwichIRCClient::processCommand (const QString &msg)
{
    qDebug()<< "Processing command (" << msg << ")";

    //Parse command
    if(msg.startsWith("PING"))
    {
        onPingCommand(msg);
        return;
    }
    else if(msg.contains("PRIVMSG"))
    {
        onPrivmsgCommand(msg);
    }
}

TwichIRCClient::TwichIRCClient() : m_connected(false), msgMaxPoolSize(MSG_POOL_SIZE_DEFAULT)
{
    //Conectar a la señal de mensaje recibido
    QObject::connect(&webSocket, &QWebSocket::textMessageReceived, [&](const QString &message) {
        // Procesar el mensaje del chat aquí
        qDebug() << "Mensaje recibido:" << message;

        processCommand(message);

    });

    //Conectar a la señal de conexión establecida
    QObject::connect(&webSocket, &QWebSocket::connected, [&]() {
        // Autenticarse en el servidor de chat

        qDebug() << "Socket conectado!";
        setConnected(true);

        QString webSocketMsg = "PASS oauth:" + oauth_token;
        qDebug() << "Enviando (" + webSocketMsg + ")";
        webSocket.sendTextMessage(webSocketMsg.trimmed()); //"PASS <oauth_token>"

        webSocketMsg = "NICK " + username;
        qDebug() << "Enviando (" + webSocketMsg + ")";
        webSocket.sendTextMessage(webSocketMsg); //"NICK <your_username>"

        webSocketMsg = "JOIN #" + channel;
        qDebug() << "Enviando (" + webSocketMsg + ")";
        webSocket.sendTextMessage(webSocketMsg); //"JOIN #<channel_name>"
    });

    // Conectar a la señal de error
    QObject::connect(&webSocket, &QWebSocket::disconnected, [&]() {
        qDebug() << "Socket desconectado!";
        setConnected(false);
    });

    // Conectar a la señal de error
    QObject::connect(&webSocket, &QWebSocket::errorOccurred, [&](QAbstractSocket::SocketError error) {
        qDebug() << "Error de conexión:" << error;
    });
}

bool TwichIRCClient::isConnected()
{
    return m_connected;
}

void TwichIRCClient::setConnected(bool isConnected)
{
    if (m_connected != isConnected) {
        m_connected = isConnected;
        emit connectedChanged();
        if(m_connected)
        {
            emit connected();
        }
        else
        {
            emit disconnected();
        }
    }
}

//QUrl url("wss://irc-ws.chat.twitch.tv:443");
void TwichIRCClient::connect(QString token, QString username, QString channel_name)
{
    if(m_connected)
    {
        qDebug("El servidor ya está conectado a twich...");
        return;
    }
    // Conectar al servidor de chat
    qDebug("Conectando a twich...");
    webSocket.open(QUrl("wss://irc-ws.chat.twitch.tv:443"));

    this->oauth_token = token.trimmed();
    this->username = username.trimmed();
    this->channel = channel_name.trimmed();
}

void TwichIRCClient::disconnect(void)
{
    qDebug("Desconectando de twich...");
    webSocket.close();
}

void TwichIRCClient::sendString(QString string)
{
    if(!m_connected)
    {
        return;
    }
    webSocket.sendTextMessage(string);
}
