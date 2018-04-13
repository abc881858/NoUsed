#include "leftwidget.h"
#include <QCheckBox>

LeftWidget::LeftWidget(QWidget *parent) : QWidget(parent)
{
    QFormLayout *formLayout = new QFormLayout;

    formLayout->addWidget(new QCheckBox("vehicle vxy", this));
    formLayout->addWidget(new QCheckBox("vehicle ax", this));
    formLayout->addWidget(new QCheckBox("vehicle yawrate", this));
    formLayout->addWidget(new QCheckBox("record vxy", this));
    formLayout->addWidget(new QCheckBox("record ax", this));
    formLayout->addWidget(new QCheckBox("record yawrate", this));
    formLayout->addWidget(new QCheckBox("front wheel angle", this));
    formLayout->addWidget(new QCheckBox("record wheel angle", this));

    formLayout->addWidget(new QCheckBox("back collision ibeo", this));
    formLayout->addWidget(new QCheckBox("front collision ibeo", this));
    formLayout->addWidget(new QCheckBox("back collision fusion", this));
    formLayout->addWidget(new QCheckBox("front collision fusion", this));
    formLayout->addWidget(new QCheckBox("cutin collision risk", this));
    formLayout->addWidget(new QCheckBox("rear end collision risk", this));
    formLayout->addWidget(new QCheckBox("gap", this));
    formLayout->addWidget(new QCheckBox("start timestamp", this));
    formLayout->addWidget(new QCheckBox("footfault hdmap", this));
    formLayout->addWidget(new QCheckBox("footfault dectect", this));
    formLayout->addWidget(new QCheckBox("acc difference", this));
    formLayout->addWidget(new QCheckBox("angle difference", this));
    formLayout->addWidget(new QCheckBox("take over request", this));
    formLayout->addWidget(new QCheckBox("quit take over", this));

    setLayout(formLayout);

    QList<QCheckBox*> items = findChildren<QCheckBox*>(QString());
    for (int i = 0; i < items.size(); ++i)
    {
        QCheckBox *checkBox = items.at(i);
        connect(checkBox, &QCheckBox::toggled, [=](bool checked)
        {
            if(checked)
            {
                emit openCheck(i);
            }
            else
            {
                emit closeCheck(i);
            }
        });
    }
}
