#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(QString("zh_cn.qm"));
    a.installTranslator(&translator);

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
