#include "watchlist.h"
#include "./ui_watchlist.h"
#include <qfile.h>
#include <QDebug>

WatchList::WatchList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WatchList)
{
    ui->setupUi(this);
    GetAPIkey();
}

// Get the API key from config.txt file...
void WatchList::GetAPIkey()
{
    QString keyPath = QCoreApplication::applicationDirPath() + "/config.txt";

    QFile configFile(keyPath);
    if (configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&configFile);
        QString _apiKey = in.readLine().split("=")[1].trimmed();
        configFile.close();
        apiKey = _apiKey;
        qDebug()<<"API key: "<<_apiKey;
    }else{
        qDebug()<<"key not found";
    }
}




WatchList::~WatchList()
{
    delete ui;
}
