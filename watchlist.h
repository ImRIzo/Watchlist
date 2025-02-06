#ifndef WATCHLIST_H
#define WATCHLIST_H

#include <QMainWindow>
#include <QListView>
#include "MovieModel.h"
#include "MovieDelegate.h"

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


private:
    Ui::WatchList *ui;
    QListView *listView;
    MovieModel *model;

    void fuck(QString jsonData);
};
#endif // WATCHLIST_H
