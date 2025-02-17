#include "serverdata.h"
#include <QDebug.h>

serverdata::serverdata(QObject *parent): QObject{parent}
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &serverdata::onReplyFinished);
}
void serverdata::GetData(QString apikey, QString titleORid, bool isTitle)
{

    QUrl url("http://www.omdbapi.com/");
    QUrlQuery query;
    query.addQueryItem("apikey", apikey);

    if(isTitle==true){
        query.addQueryItem("s", titleORid);
    }else{
        query.addQueryItem("i", titleORid);
    }

    url.setQuery(query);

    // Send the GET request
    QNetworkRequest request(url);
    manager->get(request);
}
void serverdata::onReplyFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        // Read the response data
        QByteArray responseData = reply->readAll();
        QString jsonData(responseData);
        //QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8());
        //qDebug()<<jsonDoc;
        // Emit the dataReceived signal with the JSON data
        emit dataReceived(jsonData);
    } else {
        qDebug() << "Error:" << reply->errorString();
        emit dataReceived(nullptr); // Emit nullptr in case of error
    }
    reply->deleteLater();
}

// image downloading function; it returns the QPixmap
QPixmap serverdata::downloadImage(QString url) {
    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

    // Create an event loop to wait until the request is finished
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Blocks until the image is downloaded

    QPixmap pixmap;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray imageData = reply->readAll();
        pixmap.loadFromData(imageData);
    }

    reply->deleteLater();
    return pixmap;
}
