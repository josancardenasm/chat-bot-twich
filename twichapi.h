#ifndef TWICHAPI_H
#define TWICHAPI_H

#include <QObject>

#include <QtCore>
#include <QtNetwork>
#include <QtQml/qqml.h>

#include <QOAuth2AuthorizationCodeFlow>

class TwichAPI : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool isAuthenticated READ isAuthenticated WRITE setAuthenticated NOTIFY isAuthenticatedChanged)

public:
    explicit TwichAPI(QObject *parent = nullptr);
    void setAuthenticated(bool isAuthenticated);
    bool isAuthenticated() const;

signals:
    void isAuthenticatedChanged();

public slots:
    void setCredentials(const QString& clientId, const QString& clientSecret);
    void authorize();

private:
    QOAuth2AuthorizationCodeFlow m_oauth2;
    bool m_isAuthenticated;
};

#endif // TWICHAPI_H
