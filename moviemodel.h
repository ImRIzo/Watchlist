#ifndef MOVIEMODEL_H
#define MOVIEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QPixmap>

struct Movie {
    QString Title;
    QString Year;
    QString imdbID;
    QString Type;
    QPixmap Poster;
};

class MovieModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MovieRoles {
        TitleRole = Qt::UserRole + 1,
        YearRole,
        imdbIDRole,
        TypeTole,
        PosterRole
    };

    explicit MovieModel(QObject *parent = nullptr, QString jsonServerData = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addMovie(const Movie &movie);

private:
    QList<Movie> movies;
};

#endif // MOVIEMODEL_H
