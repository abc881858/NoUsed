#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>
#include <QScrollArea>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QCategoryAxis>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ChartView(QWidget *parent = nullptr);

    QValueAxis *axisX;
    QValueAxis *axisY;
//    QLineSeries *defaultSeries;
/*    QCategoryAxis *axisX3;*/

    QList<bool> checkStates;

protected:
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void changeLeftWidget();

public slots:
    void horizontallyZoom();
    void verticallyZoom();
    void manuallyZoom();
    void restoreZoom();
};

#endif // CHARTVIEW_H
