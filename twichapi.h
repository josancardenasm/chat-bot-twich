#ifndef TWICHAPI_H
#define TWICHAPI_H

#include <QObject>

#include <QtCore>
#include <QtNetwork>
#include <QtQml/qqml.h>

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
    void authorize();
    QString generateAuthURL(void);
    void setOauthToken(QString auth_token);
    QString getOauthToken();

private:
    bool m_isAuthenticated;
    QString m_oauth_token;
};

#endif // TWICHAPI_H
