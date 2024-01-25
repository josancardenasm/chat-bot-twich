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
    // m_oauth2.setAuthorizationUrl(QUrl("https://id.twitch.tv/oauth2/authorize"));
    // m_oauth2.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
    // m_oauth2.setScope("user-top-read");

    // m_oauth2.setReplyHandler(new QOAuthHttpServerReplyHandler(8000, this));
    // m_oauth2.setModifyParametersFunction([&](QAbstractOAuth::Stage stage, QMultiMap<QString, QVariant> *parameters) {
    //     if(stage == QAbstractOAuth::Stage::RequestingAuthorization) {
    //         parameters->insert("duration", "permanent");
    //     }
    // });

    // connect(&m_oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);
    // connect(&m_oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, [=](QAbstractOAuth::Status status) {
    //     if (status == QAbstractOAuth::Status::Granted) {
    //         setAuthenticated(true);
    //     } else {
    //         setAuthenticated(false);
    //     }
    // });

    // Construct the authorization URL
    //QUrl authorizationUrl("https://id.twitch.tv/oauth2/authorize");
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

// void TwichAPI::setCredentials(const QString& clientId, const QString& clientSecret) {
//     // m_oauth2.setClientIdentifier(clientId);
//     // m_oauth2.setClientIdentifierSharedKey(clientSecret);
// }

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
