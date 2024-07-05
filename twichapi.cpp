#include "twichapi.h"

#define CLIENT_ID "8vt7zqw2jmz2c3g7x3ymr5m8jg6ocy"
#define REDIRECT_URI "http://localhost:3000"
#define AUTH_URL "https://id.twitch.tv/oauth2/authorize"

#include <userconf.h>
#include <QDebug>

TwichAPI::TwichAPI(QObject *parent) : QObject{parent}, m_isAuthenticated(false)
{
    qDebug() << "Activating Twitch..." ;
    UserConf config;
    m_oauth_token = config.getAccess_token();
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

QString TwichAPI::getOauthToken()
{
    return m_oauth_token;
}

void TwichAPI::authorize()
{
    qDebug()<<"Autorizando la aplicacion..";
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

void TwichAPI::setOauthToken(QString auth_token)
{
    qDebug() << "Saving access token " +  auth_token;
    UserConf config;
    config.setAccess_token(auth_token);

    m_oauth_token = auth_token;
}
