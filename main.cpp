#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "module.h"

static QHash<QString, uint32_t> addresses_;

uint32_t ProcessAddress(QString module_name, Signature signature, int offset)
{
    Process process;
    process.Attach(QString("Dota 2"));

    Module module;
    module.Init(process, module_name);

    uint32_t address = (uint32_t)module.FindPattern(signature);
    address += offset;

    return (uint32_t)module.GetAddress(address);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("1.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream text_stream(&file);
    QByteArray byteArray = text_stream.readAll().toUtf8();
    file.close();

    QJsonDocument jsonDoucment = QJsonDocument::fromJson(byteArray);
    QJsonObject obj = jsonDoucment.object();
    QJsonArray container = obj["steamclient.dll"].toArray();

    foreach (const QJsonValue &var, container)
    {
        QJsonObject node = var.toObject();
        int offset = node["offset"].toInt();
        QString name = node["name"].toString();
        QString signature = node["signature"].toString();

        uint32_t address = ProcessAddress("steamclient.dll", Signature(signature), offset);

        addresses_[name] = address;
    }

    return a.exec();
}
