#include "createtable.h"
#include <QPainter>
#include <QLabel>
#include <QGridLayout>
#include <QHoverEvent>
#include <QMouseEvent>

CreateTable::CreateTable(QWidget *parent) : QFrame(parent)
{
    resize(300,300);
    labelRow = 0;
    labelColumn = 0;

    setMouseTracking(true);

    QGridLayout *layout = new QGridLayout(this);
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            QLabel *label = new QLabel();
            label->setMouseTracking(true);
            allLabels[i][j] = label;
            label->setStyleSheet("background-color: rgb(211, 215, 207);");
            layout->addWidget(label,i,j);
        }
    }

    setLayout(layout);
}

void CreateTable::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(127, 127, 127), 2));
    painter.setBrush(QColor(255, 255, 255));
    painter.drawRect(0, 0, 300, 300);
}


void CreateTable::mouseMoveEvent(QMouseEvent *event)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if(allLabels[i][j]->underMouse())
            {
                labelRow = i;
                labelColumn = j;
            }
        }
    }

    for(int k = 0; k < 8; ++k)
    {
        for(int l = 0; l < 8; ++l)
        {
            if(k <= labelRow && l <= labelColumn)
            {
                allLabels[k][l]->setStyleSheet("background-color: rgb(136, 138, 133);");
            }
            else
            {
                allLabels[k][l]->setStyleSheet("background-color: rgb(211, 215, 207);");
            }
        }
    }
    return QWidget::mouseMoveEvent(event);
}

void CreateTable::mousePressEvent(QMouseEvent *event)
{
    this->hide();
    emit showTable(labelRow, labelColumn);
    return QWidget::mousePressEvent(event);
}
