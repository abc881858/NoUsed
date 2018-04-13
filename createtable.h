#ifndef CREATETABLE_H
#define CREATETABLE_H

#include <QFrame>
#include <QLabel>

class CreateTable : public QFrame
{
    Q_OBJECT
public:
    explicit CreateTable(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QLabel* allLabels[8][8];
    int labelRow;
    int labelColumn;
signals:
    void showTable(int,int);
public slots:
};

#endif // CREATETABLE_H
