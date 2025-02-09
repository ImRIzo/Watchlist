#ifndef LOCALDATABSE_H
#define LOCALDATABSE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QCoreApplication>

const QString DB_FILE_NAME = "watchlist_data_v0.1.db";

class LocalDatabse : public QObject
{
    Q_OBJECT
public:
    explicit LocalDatabse(QObject *parent = nullptr);

    bool checkIfMovieExists(QString imdbID);
    void insertMovieDetails(QString imdbID, QString title, QString year, QString director);
signals:
    void dataInsertedLocally();

private:
    QString getDatabasePath();
    QSqlDatabase db;
};

#endif
