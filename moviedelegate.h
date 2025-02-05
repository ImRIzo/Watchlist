#ifndef MOVIEDELEGATE_H
#define MOVIEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class MovieDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit MovieDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:
};

#endif // MOVIEDELEGATE_H
