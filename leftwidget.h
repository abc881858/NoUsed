#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QWidget>
#include <QFormLayout>

class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = nullptr);

signals:
    void openCheck(int);
    void closeCheck(int);

public slots:
};

#endif // LEFTWIDGET_H
