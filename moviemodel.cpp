#include "moviemodel.h"
#include <QDebug>
MovieModel::MovieModel(QObject *parent): QAbstractListModel(parent){
    serverData = new serverdata(this);
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
// this shit happens when we get the json data
void MovieModel::ShowSearchResult(QString _jsonServerData){
    // Convert the JSON string to QJsonDocument
    QJsonDocument document = QJsonDocument::fromJson(_jsonServerData.toUtf8());
    if (document.isNull() || !document.isObject()) {
        qDebug() << "Invalid JSON!";
        return;
    }

    QJsonObject jsonObject = document.object();
    if (!jsonObject.contains("Search") || !jsonObject["Search"].isArray()) {
        qDebug() << "No search results found!";
        return;
    }

    // Extract the "Search" array
    QJsonArray searchArray = jsonObject["Search"].toArray();


    // Loop through each movie entry in JSON array
    for (const QJsonValue &value : searchArray) {
        if (!value.isObject()) continue;

        QJsonObject movieObj = value.toObject();

        // Parse JSON fields into Movie struct
        Movie movie;
        movie.Title = movieObj["Title"].toString();
        movie.Year = movieObj["Year"].toString();
        movie.imdbID = movieObj["imdbID"].toString();
        movie.Type = movieObj["Type"].toString();
        // postar downloading.. if no postar then return a default postar
        QPixmap poster = serverData->downloadImage(movieObj["Poster"].toString());
        if (poster.isNull()) {
            poster.load(":/images/resources/images/defaultposter.png");
            movie.Poster = poster;
        }else{
            movie.Poster = poster;
        }


        addMovie(movie);
    }

}
// Movie movie1{"Inception", "2010", "Christopher Nolan", QPixmap(":/images/inception.jpg")};
void MovieModel::addMovie(const Movie &movie) {
    beginInsertRows(QModelIndex(), movies.size(), movies.size());
    movies.append(movie);
    endInsertRows();
}
