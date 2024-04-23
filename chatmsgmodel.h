#ifndef CHATMSGMODEL_H
#define CHATMSGMODEL_H

#include <QAbstractListModel>
#include <twichircclient.h>
#include <chatmsg.h>
#include <QtCore>
#include <QtQml/qqml.h>
#include <chatmsgdatasource.h>

class ChatMsgModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ChatMsgDataSource* chatMsgDataSource READ chatMsgDataSource WRITE setChatMsgDataSource NOTIFY chatMsgDataSourceChanged)

    //Roles enumeration
    enum {
        UserNameRole = Qt::UserRole + 1,    //User Name
        MsgRole,                            //Content of the message
    };
public:
    explicit ChatMsgModel(QObject *parent = nullptr);
    void setChatMsgDataSource(ChatMsgDataSource *newMsgDataSource);
    ChatMsgDataSource* chatMsgDataSource(void) const;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QPointer<ChatMsgDataSource> m_msgDataSource;
    bool m_signalConnected;
signals:
    void chatMsgDataSourceChanged(void);
};

#endif // CHATMSGMODEL_H
