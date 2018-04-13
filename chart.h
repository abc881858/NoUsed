#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QChartView>

QT_CHARTS_USE_NAMESPACE

class Chart : public QChartView
{
    Q_OBJECT
public:
    explicit Chart(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // CHART_H
