#ifndef SERVERDATA_H
#define SERVERDATA_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QPixmap>
#include <QEventLoop>

class serverdata : public QObject
{
    Q_OBJECT
public:
    explicit serverdata(QObject *parent = nullptr);
    // json data downloading function
    void GetData(QString apikey,QString title);
    // image downloading function
    QPixmap downloadImage(QString url);

private:
    QNetworkAccessManager *manager;
private slots:
    void onReplyFinished(QNetworkReply *reply);

signals:
    void dataReceived(QString jsonData);
};

#endif // SERVERDATA_H
