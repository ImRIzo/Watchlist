#include "watchlist.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WatchList w;
    w.show();
    return a.exec();
}
