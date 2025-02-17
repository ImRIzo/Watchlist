#ifndef WATCHLIST_H
#define WATCHLIST_H

#include <QMainWindow>
#include <QListView>
#include "MovieModel.h"
#include "MovieDelegate.h"
#include "watchlistdelegate.h"
#include "localdatabse.h"
#include <QDesktopServices>
#include <QLineEdit>
#include <QDebug>
#include <QLabel>
#include <QMovie>
#include <QFile.h>
#include "dialog.h"
#include <QApplication>


QT_BEGIN_NAMESPACE
namespace Ui {
class WatchList;
}
QT_END_NAMESPACE

class WatchList : public QMainWindow
{
    Q_OBJECT

public:
    QString apiKey;

    WatchList(QWidget *parent = nullptr);
    void InitilizeApp();
    ~WatchList();

private slots:
    void on_searchBtn_clicked();
    void onDataReceived(QString jsonData);
    void onMovieItemClicked(const QModelIndex &index);
    void showMovieDetails(QString imdbID);
    void on_localdata_insert();
    void on_back_button_clicked();
    void on_youtube_button_clicked();
    void on_google_button_clicked();
    void on_download_button_clicked();
    void on_searchBox_returnPressed();
    void on_addwatchlist_button_clicked();
    void on_deleteClicked(const QModelIndex &index);
    //void on_infoClicked(const QModelIndex &index);
    void on_favoriteClicked(const QModelIndex &index);
    void on_watchedClicked(const QModelIndex &index);
    void openWebsite();

private:
    Ui::WatchList *ui;
    QListView *listView;
    MovieModel *model;
    MovieModel *detailedModel;
    QMovie *movie;
    QString temporaryID = "";
    void fuck(QString jsonData);
    void showWatchlist();
    QPixmap posterMap;
    QString imdbID;
    LocalDatabse *localDatabase;
    WatchlistDelegate *wd;
};
#endif // WATCHLIST_H
