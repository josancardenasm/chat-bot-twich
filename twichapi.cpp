#include "twichapi.h"

TwichAPI::TwichAPI(QObject *parent) : QObject{parent}, m_isAuthenticated(false)
{
    // m_oauth2.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
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

void TwichAPI::setCredentials(const QString& clientId, const QString& clientSecret) {
    m_oauth2.setClientIdentifier(clientId);
    m_oauth2.setClientIdentifierSharedKey(clientSecret);
}

void TwichAPI::authorize() {
    m_oauth2.grant();
}
