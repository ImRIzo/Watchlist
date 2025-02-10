#include "watchlistdelegate.h"
#include "MovieModel.h"
#include <QPainter>
#include <qapplication.h>

WatchlistDelegate::WatchlistDelegate(QObject *parent) : QStyledItemDelegate{parent} {}

void WatchlistDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();

    // Draw rounded rect

    QRect rect = option.rect;
    rect.setTop(rect.top() + 2);
    rect.setLeft(rect.left() + 2);
    rect.setRight(rect.right() -2);
    QPainterPath path;
    path.addRoundedRect(rect, 5, 5);
    painter->setClipPath(path);
    painter->fillRect(rect, option.state & QStyle::State_Selected ? QColor(128,185,238) : QColor(85,156,228));

    // Draw border
    QPen pen(QColor(173,216,255));
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawRect(rect.adjusted(1, 1, -2, -2));

    // Draw poster
    QPixmap poster = index.data(MovieModel::PosterRole).value<QPixmap>();
    QRect posterRect(rect.left() + 10, rect.top() + 5, 50, 75);
    painter->drawPixmap(posterRect, poster.scaled(posterRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Define text positions
    int textX = posterRect.right() + 60;
    int fieldX = posterRect.right() + 10;
    QRect titleRect(fieldX, rect.top() + 10, rect.width() - textX - 10, 20);
    QRect yearfieldRect(fieldX, rect.top() + 35, rect.width() - textX - 10, 20);
    QRect yearRect(textX, rect.top() + 35, rect.width() - textX - 10, 15);
    QRect imdbidfieldRect(fieldX, rect.top() + 55, rect.width() - textX - 10, 20);
    QRect imdbID(textX, rect.top() + 55, rect.width() - textX - 10, 15);

    // Draw field labels
    QFont fieldFont = painter->font();
    fieldFont.setPointSize(10);
    painter->setFont(fieldFont);
    painter->setPen(QColor(1,1,1));
    painter->drawText(yearfieldRect, Qt::AlignLeft, "Year: ");
    painter->drawText(imdbidfieldRect, Qt::AlignLeft, "IMDb ID: ");

    // Draw movie title (with strikeout if watched)
    QFont titleFont = painter->font();
    titleFont.setBold(true);
    titleFont.setPointSize(12);
    // if (index.data(MovieModel::WatchedRole).toBool()) {
    //     titleFont.setStrikeOut(true);
    // }
    painter->setFont(titleFont);
    painter->setPen(QColor(1,1,1));
    painter->drawText(titleRect, Qt::AlignLeft, index.data(MovieModel::TitleRole).toString());

    // Draw details (year, IMDb ID)
    QFont detailsFont = painter->font();
    detailsFont.setPointSize(10);
    painter->setFont(detailsFont);
    painter->setPen(Qt::white);
    painter->drawText(yearRect, Qt::AlignLeft, index.data(MovieModel::YearRole).toString());
    painter->drawText(imdbID, Qt::AlignLeft, index.data(MovieModel::imdbIDRole).toString());

    // **Draw Buttons (Aligned to the Right)**
    int buttonSize = 32;
    int spacing = 5;
    int rightPadding = 15;

    QRect deleteButtonRect(rect.right() - rightPadding - buttonSize, rect.center().y() - buttonSize / 2, buttonSize, buttonSize);
    QRect infoButtonRect(deleteButtonRect.left() - buttonSize - spacing, deleteButtonRect.top(), buttonSize, buttonSize);
    QRect favoriteButtonRect(infoButtonRect.left() - buttonSize - spacing, deleteButtonRect.top(), buttonSize, buttonSize);
    QRect watchedButtonRect(favoriteButtonRect.left() - buttonSize - spacing, deleteButtonRect.top(), buttonSize, buttonSize);

    QPixmap deleteIcon(":/images/resources/images/delete.png");
    QPixmap infoIcon(":/images/resources/images/info.png");
    QPixmap favoriteIcon(":/images/resources/images/favorite.png");
    QPixmap watchedIcon(":/images/resources/images/seen.png");

    painter->drawPixmap(deleteButtonRect, deleteIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    painter->drawPixmap(infoButtonRect, infoIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    painter->drawPixmap(favoriteButtonRect, favoriteIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    painter->drawPixmap(watchedButtonRect, watchedIcon.scaled(buttonSize, buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    painter->restore();
}

QSize WatchlistDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(250, 85);
}

bool WatchlistDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {

    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        int buttonSize = 32;
        int spacing = 5;
        int rightPadding = 15;

        QRect deleteButtonRect(option.rect.right() - rightPadding - buttonSize, option.rect.center().y() - buttonSize / 2, buttonSize, buttonSize);
        QRect infoButtonRect(deleteButtonRect.left() - buttonSize - spacing, deleteButtonRect.top(), buttonSize, buttonSize);
        QRect favoriteButtonRect(infoButtonRect.left() - buttonSize - spacing, deleteButtonRect.top(), buttonSize, buttonSize);
        QRect watchedButtonRect(favoriteButtonRect.left() - buttonSize - spacing, deleteButtonRect.top(), buttonSize, buttonSize);

        if (deleteButtonRect.contains(mouseEvent->pos())) {
            emit deleteClicked(index);
            return true;
        } else if (infoButtonRect.contains(mouseEvent->pos())) {
            emit infoClicked(index);
            return true;
        } else if (favoriteButtonRect.contains(mouseEvent->pos())) {
            emit favoriteClicked(index);
            return true;
        } else if (watchedButtonRect.contains(mouseEvent->pos())) {
            emit watchedClicked(index);
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
