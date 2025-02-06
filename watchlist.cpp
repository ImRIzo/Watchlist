#include "watchlist.h"
#include "serverdata.h"
#include "./ui_watchlist.h"
#include <qfile.h>
#include <QLineEdit>
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

// once the search button is clicked this function .............
void WatchList::on_searchBtn_clicked()
{
    QString title = ui->searchBox->text();
    serverdata *sd = new serverdata(this);
    // Connect the dataReceived signal to the onDataReceived slot
    connect(sd, &serverdata::dataReceived, this, &WatchList::onDataReceived);
    sd->GetData(apiKey, title);
}
// this slot triggers when we get data
void WatchList::onDataReceived(QString jsonData) {
    if (jsonData.isNull()) {
        qDebug() << "Failed to fetch data.";
    } else {
        //qDebug() << "Received JSON data:" << jsonData;

        fuck(jsonData);
    }
}
void WatchList::fuck(QString jsonData){

    listView = ui->listview_search;
    model = new MovieModel(this);
    MovieDelegate *delegate = new MovieDelegate(this);

    listView->setModel(model);
    listView->setItemDelegate(delegate);
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Connect the delegate signal to a slot that handles clicks
    connect(delegate, &MovieDelegate::itemClicked, this, &WatchList::onMovieItemClicked);

    model->ShowSearchResult(jsonData);
}
// This function is triggered when a movie item is clicked
void WatchList::onMovieItemClicked(const QModelIndex &index)
{
    QString imdbID = index.model()->data(index, MovieModel::imdbIDRole).toString();
    qDebug() << "Clicked movie:" << imdbID;
}

