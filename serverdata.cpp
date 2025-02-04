#include "serverdata.h"
#include <QDebug.h>

serverdata::serverdata(QObject *parent): QObject{parent}
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &serverdata::onReplyFinished);
}
void serverdata::GetData(QString apikey, QString title)
{

    QUrl url("http://www.omdbapi.com/");
    QUrlQuery query;
    query.addQueryItem("apikey", apikey);
    query.addQueryItem("s", title);
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
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8());
        qDebug()<<jsonDoc;
        // Emit the dataReceived signal with the JSON data
        emit dataReceived(jsonData);
    } else {
        qDebug() << "Error:" << reply->errorString();
        emit dataReceived(nullptr); // Emit nullptr in case of error
    }
    reply->deleteLater();
}
