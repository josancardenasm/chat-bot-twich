#include "twichircclient.h"
#include <QObject>

TwichIRCClient::TwichIRCClient()
{
    //Conectar a la señal de mensaje recibido
    QObject::connect(&webSocket, &QWebSocket::textMessageReceived, [&](const QString &message) {
        // Procesar el mensaje del chat aquí
        qDebug() << "Mensaje recibido:" << message;
    });

    //Conectar a la señal de conexión establecida
    QObject::connect(&webSocket, &QWebSocket::connected, [&]() {
        // Autenticarse en el servidor de chat

        qDebug() << "Socket conectado!";
        //        webSocket.sendTextMessage("PASS <oauth_token>");
        //        webSocket.sendTextMessage("NICK <your_username>");
        //        webSocket.sendTextMessage("JOIN #<channel_name>");
    });

    // Conectar a la señal de error
    QObject::connect(&webSocket, &QWebSocket::disconnected, [&]() {
        qDebug() << "Socket desconectado!";
    });

    // Conectar a la señal de error
    QObject::connect(&webSocket, &QWebSocket::errorOccurred, [&](QAbstractSocket::SocketError error) {
        qDebug() << "Error de conexión:" << error;
    });
}

//QUrl url("wss://irc-ws.chat.twitch.tv:443");
bool TwichIRCClient::connect(QUrl url)
{
    // Conectar al servidor de chat
    qDebug("Conectando a twich...");
    webSocket.open(url);
    return false;
}

bool TwichIRCClient::disconnect(void)
{
    qDebug("Desconectando de twich...");
    webSocket.close();
    return false;
}
