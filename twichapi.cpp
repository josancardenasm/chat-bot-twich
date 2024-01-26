#include "twichapi.h"

#define CLIENT_ID "8vt7zqw2jmz2c3g7x3ymr5m8jg6ocy"
#define REDIRECT_URI "http://localhost:3000"
#define AUTH_URL "https://id.twitch.tv/oauth2/authorize"

// #include <QDesktopServices>
// #include <QUrl>
// #include <QUrlQuery>
#include <QDebug>
//#include <QWebEngineView>

TwichAPI::TwichAPI(QObject *parent) : QObject{parent}, m_isAuthenticated(false)
{
    qDebug() << "Activando twich" ;
}

void TwichAPI::setAuthenticated(bool isAuthenticated) {
    if (m_isAuthenticated != isAuthenticated) {
        m_isAuthenticated = isAuthenticated;
        emit isAuthenticatedChanged();
    }
}

bool TwichAPI::isAuthenticated() const {
    return m_isAuthenticated;
}

void TwichAPI::authorize()
{
    qDebug()<<"Autorizando la aplicacion..";

    // QUrl authorizationUrl("https://id.twitch.tv/oauth2/authorize");
    // QUrlQuery query;
    // query.addQueryItem("client_id", CLIENT_ID);
    // query.addQueryItem("redirect_uri", REDIRECT_URI);
    // query.addQueryItem("response_type", "token");
    // query.addQueryItem("scope", "chat:read");  // Add the required scopes
    // authorizationUrl.setQuery(query);

    // // Carga la URL de autorización en el navegador
    // QWebEngineView view;

    // view.load(authorizationUrl);

    // Conecta una función lambda al evento de carga terminada
    // QObject::connect(&view, &QWebEngineView::urlChanged, [&redirectUrl](const QUrl& url) {
    //     // Comprueba si la URL contiene la URL de redirección
    //     if (url.toString().startsWith(redirectUrl.toString())) {
    //         // Aquí puedes manejar la URL de redirección
    //         qDebug() << "URL de redirección detectada:" << url.toString();
    //     }
    // });

    // view.show();

    // QUrl authorizationUrl("https://id.twitch.tv/oauth2/authorize");
    // QUrlQuery query;
    // query.addQueryItem("client_id", CLIENT_ID);
    // query.addQueryItem("redirect_uri", REDIRECT_URI);
    // query.addQueryItem("response_type", "token");
    // query.addQueryItem("scope", "chat:read");  // Add the required scopes
    // authorizationUrl.setQuery(query);

    // QDesktopServices::openUrl(authorizationUrl);

    // m_oauth2.grant();
}

QString TwichAPI::generateAuthURL(void)
{
    QUrl authorizationUrl("https://id.twitch.tv/oauth2/authorize");
    QUrlQuery query;
    query.addQueryItem("client_id", CLIENT_ID);
    query.addQueryItem("redirect_uri", REDIRECT_URI);
    query.addQueryItem("response_type", "token");
    query.addQueryItem("scope", "chat:read");  // Add the required scopes
    authorizationUrl.setQuery(query);
    return authorizationUrl.toString();
}
