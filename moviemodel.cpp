#include "moviemodel.h"


MovieModel::MovieModel(QObject *parent, QString jsonServerData): QAbstractListModel(parent){

}

int MovieModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : movies.size();
}

QVariant MovieModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= movies.size())
        return QVariant();

    const Movie &movie = movies.at(index.row());

    switch (role) {
        case TitleRole: return movie.Title;
        case YearRole: return movie.Year;
        case imdbIDRole: return movie.imdbID;
        case TypeTole: return movie.Type;
        case PosterRole: return movie.Poster;
        default: return QVariant();
    }
}

void MovieModel::addMovie(const Movie &movie) {
    beginInsertRows(QModelIndex(), movies.size(), movies.size());
    movies.append(movie);
    endInsertRows();
}
