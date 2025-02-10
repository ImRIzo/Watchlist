#ifndef WATCHLISTDELEGATE_H
#define WATCHLISTDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QMouseEvent>
#include <QPainterPath>


class WatchlistDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit WatchlistDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void deleteClicked(const QModelIndex &index);
    void infoClicked(const QModelIndex &index);
    void favoriteClicked(const QModelIndex &index);
    void watchedClicked(const QModelIndex &index);
};

#endif
