#include "twichircclient.h"
#include <QObject>

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
        qDebug() << "PRIVMSG doesn't match with regex";
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

TwichIRCClient::TwichIRCClient() : m_connectedState(TWIRC_DISCONNECTED), m_connectedStateLast(TWIRC_DISCONNECTED)
{

    QObject::connect(&webSocket, &QWebSocket::textMessageReceived, [&](const QString &message) {
        qDebug() << "Message received:" << message;
        processCommand(message);
    });

    QObject::connect(&webSocket, &QWebSocket::connected, [&]() {

        qDebug() << "Socket connected!";

        //Chat server authentication...
        QString webSocketMsg = "PASS oauth:" + oauth_token;
        qDebug() << "Sending (" + webSocketMsg + ")";
        webSocket.sendTextMessage(webSocketMsg.trimmed()); //"PASS <oauth_token>"

        webSocketMsg = "NICK " + username;
        qDebug() << "Sending (" + webSocketMsg + ")";
        webSocket.sendTextMessage(webSocketMsg); //"NICK <your_username>"

        webSocketMsg = "JOIN #" + channel;
        qDebug() << "Sending (" + webSocketMsg + ")";
        webSocket.sendTextMessage(webSocketMsg); //"JOIN #<channel_name>"

        m_connectedStateLast = m_connectedState;
        m_connectedState = TWIRC_CONNECTED;
        emit connectedStateChanged(m_connectedState);
    });

    QObject::connect(&webSocket, &QWebSocket::disconnected, [&]() {
        qDebug() << "Socket disconnected!";

        m_connectedStateLast = m_connectedState;
        m_connectedState = TWIRC_DISCONNECTED;
        emit connectedStateChanged(m_connectedState);

        //Something happened....
        if (m_connectedStateLast == TWIRC_CONNECTED)
        {
            qDebug() << "Intentando volver a conectar...";
            this->reconnect();
        }

    });

    // Connect to error signal
    QObject::connect(&webSocket, &QWebSocket::errorOccurred, [&](QAbstractSocket::SocketError error) {
        qDebug() << "Connection error:" << error;
    });
}

void TwichIRCClient::reconnect(void)
{
    //TODO: Start a timer to reconnect
    //this->connect(this->oauth_token, this->username, this->channel);
}

TwichIRCClient::ConnectedState TwichIRCClient::connectedState(void)
{
    return m_connectedState;
}

//QUrl url("wss://irc-ws.chat.twitch.tv:443");
void TwichIRCClient::connect(QString token, QString username, QString channel_name)
{
    if(m_connectedState == TWIRC_CONNECTING || m_connectedState == TWIRC_CONNECTED || m_connectedState == TWIRC_DISCONNECTING)
    {
        qDebug("Server is not disconnected yet!...");
        return;
    }

    // Connect to chat server
    qDebug("Connecting to twitch...");
    webSocket.open(QUrl("wss://irc-ws.chat.twitch.tv:443"));

    this->oauth_token = token.trimmed();
    this->username = username.trimmed();
    this->channel = channel_name.trimmed();

    m_connectedStateLast = m_connectedState;
    m_connectedState = TWIRC_CONNECTING;
    emit connectedStateChanged(m_connectedState);
}

void TwichIRCClient::disconnect(void)
{
    if(m_connectedState == TWIRC_DISCONNECTED ||  m_connectedState == TWIRC_DISCONNECTING)
    {
        qDebug("Server is already disconnected or disconnecting!...");
        return;
    }

    qDebug("Disconnecting from twitch...");
    webSocket.close();

    m_connectedStateLast = m_connectedState;
    m_connectedState = TWIRC_DISCONNECTING;
    emit connectedStateChanged(m_connectedState);
}

void TwichIRCClient::sendString(QString string)
{
    if(m_connectedState != TWIRC_CONNECTED)
    {
        return;
    }
    webSocket.sendTextMessage(string);
}
