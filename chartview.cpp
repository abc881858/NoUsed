#include "chartview.h"
#include <QDebug>

ChartView::ChartView(QWidget *parent) : QChartView(parent)
{
    for(int i=1; i<=22; ++i)
    {
        checkStates << false;
    }

//    defaultSeries = new QLineSeries();

//    setRubberBand(QChartView::RectangleRubberBand);

    QChart *chart = new QChart();
//    chart->addSeries(defaultSeries);
    chart->legend()->setVisible(false);
    chart->setAnimationOptions(QChart::NoAnimation);

    axisX = new QValueAxis();
    axisX->setLabelFormat("%i");
    axisX->setTickCount(10);
    chart->addAxis(axisX, Qt::AlignBottom);
//    defaultSeries->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setLabelFormat("%.6f");
    axisY->setTickCount(3);
    chart->addAxis(axisY, Qt::AlignLeft);

    /*
    axisX3 = new QCategoryAxis;
    axisX3->append("one", 300);
    axisX3->append("two", 600);
    axisX3->append("three", 900);
    */

//    axisX3->setLinePenColor(series->pen().color());
//    axisX3->setGridLinePen((series->pen()));

/*    chart->addAxis(axisX3, Qt::AlignTop);*/

//    defaultSeries->attachAxis(axisY);
//    chart->createDefaultAxes();

    setRenderHint(QPainter::Antialiasing);
    setChart(chart);
}

void ChartView::horizontallyZoom()
{
    setRubberBand(QChartView::HorizontalRubberBand);
}

void ChartView::verticallyZoom()
{
    setRubberBand(QChartView::VerticalRubberBand);
}

void ChartView::manuallyZoom()
{
    setRubberBand(QChartView::RectangleRubberBand);
}

void ChartView::restoreZoom()
{
    chart()->zoomReset();
//    fitInView(0,0,width(),height());
    setRubberBand(QChartView::NoRubberBand);
    //todo: restore ChartView
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        return; //event doesn't go further
    }
    QChartView::mouseReleaseEvent(event);//any other event
}
