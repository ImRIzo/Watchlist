#include "localdatabse.h"

LocalDatabse::LocalDatabse(QObject *parent): QObject{parent}
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(getDatabasePath());

    if (!db.open()) {
        qDebug() << "Error: Unable to connect to database!";
    } else {
        qDebug() << "Connected to database successfully!";
    }
}

// get the database path ...
QString LocalDatabse :: getDatabasePath() {
    // Get the app data directory (user-specific)
    QString appDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // Ensure the directory exists
    QDir dir(appDataDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Define the path for the database file
    QString dbPath = appDataDir + "/"+ DB_FILE_NAME;

    // If the database doesn't exist, copy it
    if (!QFile::exists(dbPath)) {
        QString dbfileTemplate = QCoreApplication::applicationDirPath() + "/"+DB_FILE_NAME;
        QFile::copy(dbfileTemplate, dbPath);
        //qDebug() << "Database copied to app data folder!";
    }

    return dbPath;
}

// get the local poster path ...
QString LocalDatabse :: getPosterPath() {
    // Get the app data directory (user-specific)
    QString appDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    // Define the path for the database file
    QString posterPath = appDataDir + "/Poster/";
    // Ensure the directory exists
    QDir dir(posterPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    return posterPath;
}



// Insert movie details into the database
void LocalDatabse :: insertMovieDetails( QString imdbID, QString title, QString year, QString director, QPixmap poster) {
    QSqlQuery query;
    query.prepare("INSERT INTO my_watchlist (imdbID, title, year, director) VALUES (:imdbID, :title, :year, :director)");
    query.bindValue(":imdbID", imdbID);
    query.bindValue(":title", title);
    query.bindValue(":year", year);
    query.bindValue(":director", director);

    if (!query.exec()) {
        qDebug() << "Error inserting data:" << query.lastError().text();
        return;
    }

    // save the poster as PNG to the local disk -> appdata folder
    poster.save(getPosterPath()+imdbID+".png", "PNG");

    emit(dataInsertedLocally());
}


bool LocalDatabse :: checkIfMovieExists(QString imdbID) {
    QSqlQuery query;
    query.prepare("SELECT 1 FROM my_watchlist WHERE imdbID = :imdbID");
    query.bindValue(":imdbID", imdbID);

    if (!query.exec()) {
        //qDebug() << "Error executing query:" << query.lastError().text();
    }
// it return bool if row is found
    return query.next();
}

void LocalDatabse :: deleteData(QString imdbID){
    QSqlQuery query;
    query.prepare("DELETE FROM my_watchlist WHERE imdbID = :imdbID");
    query.bindValue(":imdbID", imdbID);

    if (!query.exec()) {
        //qDebug() << "Error executing query:" << query.lastError().text();
    }
}


void LocalDatabse::updateSeen(const QString& imdbID, const QString& _watched) {
    QSqlQuery query;
    query.prepare("UPDATE my_watchlist SET watched = :watched WHERE imdbID = :imdbID");
    query.bindValue(":imdbID", imdbID);
    query.bindValue(":watched", _watched);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        qDebug() << "Query: " << query.lastQuery();
    }
    qDebug() << "Query: " << imdbID << _watched;
}



QList<Movie> LocalDatabse::fetchWatchlist() {
    QList<Movie> movies;

    // Example of querying the database to fetch movie info
    QSqlQuery query("SELECT * FROM my_watchlist");
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return movies;
    }

    // Loop through the result set and create Movie objects
    while (query.next()) {
        Movie movie;
        movie.Title = query.value("title").toString();
        movie.Year = query.value("year").toString();
        movie.imdbID = query.value("imdbID").toString();
        movie.Seen = query.value("watched").toString();

        // Download poster if available or use a default one
        QPixmap poster;
        poster.load(getPosterPath()+movie.imdbID+".png");
        if (poster.isNull()) {
        // poster na thakle ki korbo segula pore hobe....ekhon default ta diye rakhlam
            poster.load(":/images/resources/images/defaultposter.png");
            movie.Poster = poster;
        } else {
            movie.Poster = poster;
        }

        movies.append(movie);
    }

    return movies;
}

