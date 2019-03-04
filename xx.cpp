#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QUrl>
#include <QSslConfiguration>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName("proxyhk.huawei.com");
    proxy.setPort(8080);
    proxy.setUser("wwx556609");
    proxy.setPassword("a#yMn4!4");
    QNetworkProxy::setApplicationProxy(proxy);

    manager = new QNetworkAccessManager(this);
    manager->setProxy(proxy);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_0);

    ///players/{account_id}/matches

    QNetworkRequest request(QUrl(QString("https://api.opendota.com/api/players/189901415/matches/?hero_id=59&api_key=B7028D52AA181C100C76520ADADFA736")));
    request.setSslConfiguration(config);

    QNetworkReply *reply = manager->get(QNetworkRequest(request));
    connect(reply, &QNetworkReply::finished, this, [=](){
        if(reply->error() != QNetworkReply::NoError)
        {
            qDebug() << "get data error!" << int(reply->error());
        }
        else
        {
            QByteArray ba = reply->readAll();
            qDebug() << ba;
            QJsonDocument jsonDoucment = QJsonDocument::fromJson(ba);
            resultJsonObject = jsonDoucment.object();

//            jsonObject["Datasets"].toArray());
        }

        reply->deleteLater();
    });
}
