#include <QCoreApplication>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

//    QProcess process;
//    process.start("C:\Windows\System32\COMMAND.COM");

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("1.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream text_stream(&file);
    QByteArray byteArray = text_stream.readAll().toUtf8();
    file.close();

    QJsonDocument jsonDoucment = QJsonDocument::fromJson(byteArray);
    //(QByteArray)jsonDoucment.toJson(QJsonDocument::Compact);

    QJsonObject obj = jsonDoucment.object();

    QJsonArray container = obj["steamclient.dll"].toArray();

    foreach (QJsonObject var, container) {
        var["offset"].toInt();
        var["name"].toString();
        var["signature"].toString();
    }

    return a.exec();
}
