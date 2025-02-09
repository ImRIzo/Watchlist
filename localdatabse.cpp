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

// insert data if data not exists
// bool LocalDatabse :: getMovieDetails(const QString& imdbID, QString& title, QString& year, QString& director) {
//     QSqlQuery query;
//     query.prepare("SELECT title, year, director FROM movies WHERE imdbID = :imdbID");
//     query.bindValue(":imdbID", imdbID);

//     if (!query.exec()) {
//         qDebug() << "Error executing query:" << query.lastError().text();
//         return false;
//     }

//     if (query.next()) {
//         title = query.value(0).toString();
//         year = query.value(1).toString();
//         director = query.value(2).toString();
//         return true;
//     }

//     return false;
// }


// Insert movie details into the database
void LocalDatabse :: insertMovieDetails( QString imdbID, QString title, QString year, QString director) {
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
