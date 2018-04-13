#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "chartview.h"
#include <QStackedWidget>
#include <QHash>

QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGridLayout *gridLayout;
    QWidget *right;
    QStackedWidget *left;

private:
    ChartView *currentChartView;
    QAction *horizontallyZoomAction;
    QAction *verticallyZoomAction;
    QAction *manuallyZoomAction;
    QAction *restoreZoomAction;
    QHash<int, QRgb> penColors;

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
