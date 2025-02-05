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
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon appIcon(":/images/resources/images/appicon.png");
    a.setWindowIcon(appIcon);
    WatchList w;
    w.show();
    return a.exec();
}
