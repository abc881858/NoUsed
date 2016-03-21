# QDota2Cheat

#include <QCoreApplication>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
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

    qDebug() << obj;

    return a.exec();
}

///////////////////////////////////////////////
{
	"client.dll": [
		{
			"offset": 1, 
			"name": "DotaInput", 
			"signature": "A1 ? ? ? ? B9 ? ? ? ? FF 90 98 00 00 00"
		}, 
		{
			"offset": 4, 
			"name": "PlayerResource", 
			"signature": "74 4D 8B 35 ? ? ? ? 85 F6 74 67"
		},
		{
			"offset": 4, 
			"name": "GameRules", 
			"signature": "74 4B 8B 0D ? ? ? ? 85 C9 74 06"
		},
		{
			"offset": 3, 
			"name": "Hud", 
			"signature": "7C E9 B9 ? ? ? ? E8 ? ? ? ?"
		},
		{
			"offset": 3, 
			"name": "ClientMode", 
			"signature": "74 11 68 ? ? ? ? FF 15 ? ? ? ? 83 C4 04 5E 5D C3 8B 0D ? ? ? ? 8B B6 0C 04 00 00"
		},
		{
			"offset": 1, 
			"name": "ModifierDefaultParams", 
			"signature": "68 ? ? ? ? 6A 17 8B C8"
		},
		{
			"offset": 2, 
			"name": "GameSystemsRetriever", 
			"signature": "8B 15 ? ? ? ? 85 C0 7E 0E"
		}
	],
	"engine.dll": [
		{
			"offset": 4, 
			"name": "CommandBuffer", 
			"signature": "EB 5E FF 05 ? ? ? ?"
		}
	]
}
