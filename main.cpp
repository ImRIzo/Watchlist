/*
 *
as a movie freak I needed this very much
so it is what it is
if you like it, cool
or
fuck off
*
*/

#include "watchlist.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WatchList w;
    w.show();
    return a.exec();
}
