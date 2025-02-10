#ifndef WATCHLISTDELEGATE_H
#define WATCHLISTDELEGATE_H

#include <QObject>

class WatchlistDelegate : public QObject
{
    Q_OBJECT
public:
    explicit WatchlistDelegate(QObject *parent = nullptr);

signals:
};

#endif // WATCHLISTDELEGATE_H
