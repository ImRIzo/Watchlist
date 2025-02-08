#ifndef MOVIEDELEGATE_H
#define MOVIEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QMouseEvent>
#include <QPainterPath>

class MovieDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit MovieDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void itemClicked(const QModelIndex &index);
};

#endif // MOVIEDELEGATE_H
