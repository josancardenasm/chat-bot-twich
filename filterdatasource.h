#ifndef FILTERDATASOURCE_H
#define FILTERDATASOURCE_H

#include <QObject>

class FilterDataSource : public QObject
{
    Q_OBJECT
public:
    explicit FilterDataSource(QObject *parent = nullptr);

signals:
};

#endif // FILTERDATASOURCE_H
