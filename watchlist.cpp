#include "watchlist.h"
#include "serverdata.h"
#include "./ui_watchlist.h"


WatchList::WatchList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WatchList)
{
    ui->setupUi(this);
    GetAPIkey();
    localDatabase = new LocalDatabse(this);
    // show the watchlist from local database
    showWatchlist();
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
    delete movie;
    delete ui;    
}

// this function executes once the return button is pressed.....
void WatchList::on_searchBox_returnPressed()
{
    on_searchBtn_clicked();
}
// once the search button is clicked this function .............
void WatchList::on_searchBtn_clicked()
{
    // make sure we are on the first page..
    if(ui->stackedWidget->currentIndex()!=0)ui->stackedWidget->setCurrentWidget(ui->searchlist_page);

    QString title = ui->searchBox->text();

    // show dialog if text is empty...
    if(title==""){
        Dialog dialog(this);
        dialog.showDialog("Your speak English madafaka ?");
    }

    serverdata *sd = new serverdata(this);
    // Connect the dataReceived signal to the onDataReceived slot
    connect(sd, &serverdata::dataReceived, this, &WatchList::onDataReceived);
    sd->GetData(apiKey, title, true); // true means i'm sending title from here false means imdb id
}
// this slot triggers when we get data
void WatchList::onDataReceived(QString jsonData) {
    if (jsonData.isNull()) {
        Dialog dialog(this);
        dialog.showDialog("Failed to fetch data.");
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

    model->ShowSearchResult(jsonData, MovieModel::DataType::SearchData);
}
// This function is triggered when a movie item is clicked
void WatchList::onMovieItemClicked(const QModelIndex &index)
{   //show loading gif...
    ui->stackedWidget->setCurrentWidget(ui->loading_page);

    imdbID = index.model()->data(index, MovieModel::imdbIDRole).toString();
    posterMap = index.model()->data(index, MovieModel::PosterRole).value<QPixmap>();
    qDebug() << "Clicked movie:" << imdbID;

    // if we alreadt checked the movie details then we will skil fetching data
    // rather just go to the details page
    if(temporaryID==imdbID){
        ui->stackedWidget->setCurrentWidget(ui->details_page);
        return;
    }
    temporaryID = imdbID;

    // play loading animation .............
    QLabel *label = ui->loading_gif;
    movie = new QMovie(":/images/resources/images/loading.gif");
    label->setMovie(movie);
    movie->start();

    serverdata *sd = new serverdata(this);
    // Connect the dataReceived signal to the onDataReceived slot
    connect(sd, &serverdata::dataReceived, this, &WatchList::showMovieDetails);
    sd->GetData(apiKey, imdbID, false); // true means i'm sending title from here false means imdb id

}

void WatchList :: showMovieDetails(QString jsonData)
{
    detailedModel = new MovieModel(this);
    MovieDetails details = detailedModel->movieDetailedShow(jsonData);

// showing data begin
    ui->_title->setText(details.Title);
    ui->_year->setText(details.Year);
    ui->_genre->setText(details.Genre);
    ui->_director->setText(details.Director);
    ui->_country->setText(details.Language);
    ui->_runtime->setText(details.Runtime);
    ui->_country->setText(details.Country);
    ui->_actors->setText(details.Actors);
    ui->_plot->setText(details.Plot);
    ui->_awards->setText(details.Awards);

    for (const auto &rating : details.Ratings) {
        //qDebug() << rating.first << ": " << rating.second;
        if(rating.first == "Internet Movie Database"){
            ui->_imdbrating->setText(rating.second);
        }else if(rating.first == "Rotten Tomatoes"){
            ui->_rottenrating->setText(rating.second);
        }
    }

    ui->_poster->setPixmap(posterMap);


    ui->stackedWidget->setCurrentWidget(ui->details_page);
}

void WatchList::on_back_button_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->searchlist_page);
}


void WatchList::on_youtube_button_clicked()
{
    QString title = ui->_title->text();
    QString year = ui->_year->text();
    QString url = "https://www.youtube.com/results?search_query=";
    url = url + title + "+" +year;
    url = url.replace(" ", "+");
    QDesktopServices::openUrl(QUrl(url));
}


void WatchList::on_google_button_clicked()
{
    QString title = ui->_title->text();
    QString year = ui->_year->text();
    QString url = "https://www.google.com/search?q=";
    url = url + title + "+"+year;
    url = url.replace(" ", "+");
    QDesktopServices::openUrl(QUrl(url));
}


void WatchList::on_download_button_clicked()
{
    QString title = ui->_title->text();
    QString year = ui->_year->text();
    QString url = "https://1337x.to/search/";
    url = url + title +"+"+year + "/1/";
    url = url.replace(" ", "+");
    QDesktopServices::openUrl(QUrl(url));
}

 // from here we will work on local database

void WatchList :: showWatchlist(){
    // this will be modified later..

    QList<Movie> movieList = localDatabase->fetchWatchlist();
    MovieModel *model = new MovieModel(this);
    model->ShowWatchListResult(movieList);
    QListView *listView = ui->listview_saved;
    listView->setModel(model);

    //set a custom delegate
    WatchlistDelegate *delegate = new WatchlistDelegate(this);
    listView->setItemDelegate(delegate);
    listView->show();

}

void WatchList::on_addwatchlist_button_clicked()
{
 // first we will look for if the movie data is already exist in our sqlite local database...
    // if exists then will promt that the movie is already exist on your lis, else
 // we will save the movie data in out database.. and data:
 // Title, Yearm indbID, Poster, Rating, Watched/NotWatched

 // let's check if the movie exist,

 if (localDatabase->checkIfMovieExists(imdbID)) {
     //qDebug() << "Movie found: ";
     Dialog dialog(this);
     dialog.showDialog("This movie is already in your list nigga.");
 }
 else {
     qDebug() << "Movie does not exist in the database. Inserting new details...";

     connect(localDatabase,&LocalDatabse::dataInsertedLocally, this, &WatchList::on_localdata_insert);

     QString title = ui->_title->text();
     QString year = ui->_year->text();
     QString director = ui->_director->text();
     QPixmap poster = ui->_poster->pixmap();
     localDatabase->insertMovieDetails(imdbID, title, year, director, poster);
 }

}
void WatchList :: on_localdata_insert(){
    qDebug()<<"data inserted";
    Dialog dialog(this);
    dialog.showDialog("The movie has been added to your watchlist!");

    showWatchlist();

}
