#include "MovieModel.h"
#include "moviedelegate.h"
#include <QPainter>

MovieDelegate::MovieDelegate(QObject *parent):QStyledItemDelegate(parent) {}

void MovieDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();
    // this portion to draw rect
    QRect rect = option.rect;
    painter->fillRect(rect, option.state & QStyle::State_Selected ? QColor(128,185,238) : QColor(85,156,228));
    // this shit draw borders
    QPen pen(QColor(173,216,255));
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawRect(rect.adjusted(1, 1, -2, -2));


    QPixmap poster = index.data(MovieModel::PosterRole).value<QPixmap>();
    poster.scaled(155,222);
    QRect posterRect(rect.left() + 10, rect.top() + 5, 50, 75);
    painter->drawPixmap(posterRect, poster.scaled(posterRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // these lines defines text starting positions
    int textX = posterRect.right() + 60;
    int fieldX = posterRect.right() + 10;

    // here we alligning rects
    QRect titleRect(fieldX, rect.top() + 10, rect.width() - textX - 10, 20);
    QRect yearfieldRect(fieldX, rect.top() + 35, rect.width() - textX - 10, 20);
    QRect yearRect(textX, rect.top() + 35, rect.width() - textX - 10, 15);
    QRect imdbidfieldRect(fieldX, rect.top() + 55, rect.width() - textX - 10, 20);
    QRect imdbID(textX, rect.top() + 55, rect.width() - textX - 10, 15);


    // here we are designing filed text e.g. Year: imdbID .....
    QFont fieldFont = painter->font();
    //fieldFont.setBold(false);
    fieldFont.setPointSize(10);
    painter->setFont(fieldFont);
    painter->setPen(QColor(1,1,1));
    painter->drawText(yearfieldRect, Qt::AlignLeft, "Year: ");
    painter->drawText(imdbidfieldRect, Qt::AlignLeft, "imdbID: ");

    // movie title design
    QFont titleFont = painter->font();
    titleFont.setBold(true);
    titleFont.setPointSize(12);
    painter->setFont(titleFont);
    painter->setPen(QColor(1,1,1));
    painter->drawText(titleRect, Qt::AlignLeft, index.data(MovieModel::TitleRole).toString());

    // details texts deign like : year = 2015, imdbid = t4556445
    QFont detailsFont = painter->font();
    detailsFont.setPointSize(10);
    painter->setFont(detailsFont);
    painter->setPen(Qt::white);
    painter->drawText(yearRect, Qt::AlignLeft, index.data(MovieModel::YearRole).toString());
    painter->drawText(imdbID, Qt::AlignLeft, index.data(MovieModel::imdbIDRole).toString());

    painter->restore();
}

QSize MovieDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(250, 85);
}

bool MovieDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                const QStyleOptionViewItem &option, const QModelIndex &index)
{
    // Check if the event is a mouse button press
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (option.rect.contains(mouseEvent->pos())) {
            //qDebug() << "Item clicked at row:" << index.row();
            emit itemClicked(index);
            return true;
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
