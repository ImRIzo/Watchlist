#ifndef WATCHLIST_H
#define WATCHLIST_H

#include <QMainWindow>
#include <QListView>
#include "MovieModel.h"
#include "MovieDelegate.h"
#include <QDesktopServices>
#include <QLineEdit>
#include <QDebug>
#include <QLabel>
#include <QMovie>
#include <qfile.h>

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
    void GetAPIkey();
    ~WatchList();

private slots:
    void on_searchBtn_clicked();
    void onDataReceived(QString jsonData);
    void onMovieItemClicked(const QModelIndex &index);
    void showMovieDetails(QString imdbID);

    void on_back_button_clicked();

    void on_youtube_button_clicked();

    void on_google_button_clicked();

    void on_download_button_clicked();

private:
    Ui::WatchList *ui;
    QListView *listView;
    MovieModel *model;
    MovieModel *detailedModel;
    QMovie *movie;
    QString temporaryID = "";
    void fuck(QString jsonData);
    QPixmap posterMap;
};
#endif // WATCHLIST_H
