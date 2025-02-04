#ifndef WATCHLIST_H
#define WATCHLIST_H

#include <QMainWindow>

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

private:
    Ui::WatchList *ui;
};
#endif // WATCHLIST_H
