#ifndef SERVERDATA_H
#define SERVERDATA_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>

class serverdata : public QObject
{
    Q_OBJECT
public:
    explicit serverdata(QObject *parent = nullptr);
    void GetData(QString apikey,QString title);

private:
    QNetworkAccessManager *manager;
private slots:
    void onReplyFinished(QNetworkReply *reply);

signals:
    void dataReceived(QString jsonData);
};

#endif // SERVERDATA_H
