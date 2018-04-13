#include "mainwindow.h"
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QAction>
#include "createtable.h"
#include <QCheckBox>
#include <QFileDialog>
#include "logdata.h"
#include <QDebug>
#include <QLineSeries>
#include "leftwidget.h"
#include <QMenu>
#include <QScatterSeries>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QToolBar *tool = new QToolBar(this);
    tool->setMovable(false);
    QAction *action = tool->addAction("charts");
    QAction *action2 = tool->addAction("load...");
    //setRubberBand(QChartView::RectangleRubberBand);

    QAction *action3 = tool->addAction("zoom");

    QMenu *zoomMenu = new QMenu;
    horizontallyZoomAction = zoomMenu->addAction("horizontally zoom");
    verticallyZoomAction = zoomMenu->addAction("vertically zoom");
    manuallyZoomAction = zoomMenu->addAction("manually zoom");
    restoreZoomAction = zoomMenu->addAction("restore zoom");

    action3->setMenu(zoomMenu);

    connect(horizontallyZoomAction, &QAction::triggered, [=](){
        if(currentChartView)
        {
            currentChartView->horizontallyZoom();
        }
    });
    connect(verticallyZoomAction, &QAction::triggered, [=](){
        if(currentChartView)
        {
            currentChartView->verticallyZoom();
        }
    });
    connect(manuallyZoomAction, &QAction::triggered, [=](){
        if(currentChartView)
        {
            currentChartView->manuallyZoom();
        }
    });
    connect(restoreZoomAction, &QAction::triggered, [=](){
        if(currentChartView)
        {
            currentChartView->restoreZoom();
        }
    });

    QWidget *widget = new QWidget(this); //zheng ti jie mian

    penColors.insert(0,0x0072BD);
    penColors.insert(1,0xD95319);
    penColors.insert(2,0xEDB120);
    penColors.insert(3,0x7E2F8E);
    penColors.insert(4,0x77AC30);
    penColors.insert(5,0x4DBEEE);
    penColors.insert(6,0xA2142F);
    penColors.insert(7,0x000000);

    left = new QStackedWidget(this);
    left->setStyleSheet("background-color: rgb(165, 165, 165);");
    left->setFixedWidth(200);

    currentChartView = nullptr;

    right = new QWidget(this);
    right->setStyleSheet("background-color: rgb(195, 195, 195);");

    gridLayout = new QGridLayout;
    right->setLayout(gridLayout);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(left);
    hLayout->addWidget(right);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(tool);
    vLayout->addLayout(hLayout);

    widget->setLayout(vLayout);
    setCentralWidget(widget);

    CreateTable *table = new CreateTable(this);
    table->hide();

    connect(action, &QAction::triggered, [=](){
        table->move(50,30);
        table->show();
    });

    //set grid view
    connect(table, &CreateTable::showTable, [=](int row, int column){
        QList<ChartView*> items = right->findChildren<ChartView*>(QString());
        for(ChartView*item : items)
        {
            delete item;
        }

        for (int i = 0; i <= row; ++i)
        {
            for (int j = 0; j <= column; ++j)
            {
                LeftWidget *leftWidget = new LeftWidget();
                left->addWidget(leftWidget);

                ChartView *chartview = new ChartView();
                chartview->setStyleSheet(("border:2px solid rgb(195, 195, 195)"));
                gridLayout->addWidget(chartview,i,j);

                connect(leftWidget, &LeftWidget::openCheck, [=](int openID)
                {
                    QChart *chart = chartview->chart();
                    QXYSeries *series;
                    if(openID<8)
                    {
                        series = new QLineSeries;
                    }
                    else
                    {
                        series = new QScatterSeries;
                    }

                    // Customize series
                    QPen pen(penColors.value(openID));
                    pen.setWidth(1);
                    series->setPen(pen);

                    series->append(LogData::instance()->allLines.at(openID));
                    chart->addSeries(series);
                    series->attachAxis(chartview->axisX);
                    series->attachAxis(chartview->axisY);
//                    series->attachAxis(chartview->axisX3);
//                    chartview->axisX3->setGridLinePen((series->pen()));
//                    chartview->axisX3->setGridLineColor(QColor(Qt::red));

                    connect(leftWidget, &LeftWidget::closeCheck, [=](int closeID)
                    {
                        if(closeID == openID)
                        {
                            chart->removeSeries(series);
                        }
                    });

                });

                connect(chartview, &ChartView::changeLeftWidget, [=]()
                {
                    left->setCurrentWidget(leftWidget);
                });

            }
        }

    });

    //load log file
    connect(action2, &QAction::triggered, [=](){
        LogData::instance()->fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/carjam_log", tr("log (*.log)"));
        LogData::instance()->setupSeries();

    });

    //zoom
    connect(action3, &QAction::triggered, [=](){
        zoomMenu->popup(cursor().pos());
        zoomMenu->show();
    });

    resize(800,600);
    setWindowTitle("Analyze");
}

MainWindow::~MainWindow()
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QList<ChartView*> items = right->findChildren<ChartView*>(QString());
        for(ChartView *item : items)
        {
            if(item->underMouse())
            {
                currentChartView = item;

                item->setStyleSheet("border:2px solid yellow");

                emit item->changeLeftWidget();
            }
            else
            {
                item->setStyleSheet("border:2px solid rgb(195, 195, 195)");
            }
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        if(currentChartView != nullptr)
        {
            currentChartView->setStyleSheet(("border:2px solid rgb(195, 195, 195)"));
        }
    }

    return QWidget::mousePressEvent(event);
}
