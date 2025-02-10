#ifndef MOVIEMODEL_H
#define MOVIEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "serverdata.h"

struct Movie {
    QString Title;
    QString Year;
    QString imdbID;
    QString Type;
    QPixmap Poster;
    QString Seen;
};

struct MovieDetails {
    QString Title;
    QString Year;
    QString Genre;
    QString Runtime;
    QPixmap Poster;
    QString Director;
    QString Language;
    QString Country;
    QString Awards;
    QString Actors;
    QString Plot;
    QVector<QPair<QString, QString>> Ratings;
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
        PosterRole,
        SeenRole
    };

    enum DataType{
        SearchData,
        DetailsData
    };

    explicit MovieModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // this function shows the result
    void ShowSearchResult(QString _jsonServerData, DataType dataType);
    void ShowWatchListResult(const QList<Movie>& movieList);
    MovieDetails movieDetailedShow(QString _jsonServerData) const;

private:
    QList<Movie> movies;
    QString jsonServerData;
    void addMovie(const Movie &movie);
    serverdata *serverData;    
};

#endif
