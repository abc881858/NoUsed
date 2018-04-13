#include "logdata.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Q_GLOBAL_STATIC(LogData, logData)

LogData *LogData::instance()
{
    return logData();
}

void LogData::setupSeries()
{
    allLines.clear();
    data_vehicle_vxy.clear();
    data_vehicle_ax.clear();
    data_vehicle_yawrate.clear();
    data_record_vxy.clear();
    data_record_ax.clear();
    data_record_yawrate.clear();
    data_front_wheel_angle.clear();
    data_record_wheel_angle.clear();

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream text_stream(&file);

    bool begin = true;

    while (!text_stream.atEnd())
    {
        QString text_line = text_stream.readLine();
        QStringList log_list = text_line.split("] ");
        QString first_string = log_list.first();
        if(!first_string.isEmpty() && first_string.startsWith("WARNING:"))
        {
            QString last_string = log_list.last();
            QStringList msg_list = last_string.split(",");
            if(!msg_list.isEmpty() && msg_list.size()>=2)
            {
                if(begin)
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    QString left_string = right_string.left(4); //to do:
                    beginTime = left_string.toInt();
                    qDebug() << "beginTime= " << beginTime;
                    begin = false;
                }

//                qDebug() << msg_list;
                if(msg_list.at(1) == "vehicle motion state")
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - beginTime;

                    QString y1_string = msg_list.at(2); // che su
                    qreal y1 = y1_string.toDouble();
                    QString y2_string = msg_list.at(3); // heng xiang jia su du
                    qreal y2 = y2_string.toDouble();
                    QString y3_string = msg_list.at(4); // heng bai jiao su du
                    qreal y3 = y3_string.toDouble();
                    QString y4_string = msg_list.at(5);
                    qreal y4 = y4_string.toDouble();
                    QString y5_string = msg_list.at(6);
                    qreal y5 = y5_string.toDouble();
                    QString y6_string = msg_list.at(7);
                    qreal y6 = y6_string.toDouble();

                    data_vehicle_vxy << QPointF(x, y1);
//                    qDebug() << "data_vehicle_vxy= " << data_vehicle_vxy;
                    data_vehicle_ax << QPointF(x, y2);
                    data_vehicle_yawrate << QPointF(x, y3);
                    data_record_vxy << QPointF(x, y4);
                    data_record_ax << QPointF(x, y5);
                    data_record_yawrate << QPointF(x, y6);

                }
                else if(msg_list.at(1) == "front wheel angle")
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y1_string = msg_list.at(2); //visual
                    qreal y1 = y1_string.toDouble();
                    QString y2_string = msg_list.at(3); //real
                    qreal y2 = y2_string.toDouble();

                    data_front_wheel_angle << QPointF(x, y1);
                    data_record_wheel_angle << QPointF(x, y2);
                }

                else if(msg_list.at(1) == "back collision ibeo") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    back_collision_ibeo << QPointF(x, y);
                }
                else if(msg_list.at(1) == "front collision ibeo") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    front_collision_ibeo << QPointF(x, y);
                }
                else if(msg_list.at(1) == "back collision fusion") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    back_collision_fusion << QPointF(x, y);
                }
                else if(msg_list.at(1) == "front collision fusion") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    front_collision_fusion << QPointF(x, y);
                }
                else if(msg_list.at(1) == "cutin collision risk") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    cutin_collision_risk << QPointF(x, y);
                }
                else if(msg_list.at(1) == "rear end collision risk") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    rear_end_collision_risk << QPointF(x, y);
                }
                else if(msg_list.at(1) == "gap")
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(3);
                    qreal y = y_string.toDouble();
                    gap << QPointF(x, y);
                }
                else if(msg_list.at(1) == "start timestamp") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    start_timestamp << QPointF(x, y);
                }
                else if(msg_list.at(1) == "footfault hdmap") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    footfault_hdmap << QPointF(x, y);
                }
                else if(msg_list.at(1) == "footfault")
                {
                    if(msg_list.at(2) == "detect")
                    {
                        QString x_string = msg_list.at(0);
                        QString right_string = x_string.right(10);
                        double x = right_string.toLongLong()/1000000.0 - begin;
                        QString y_string = msg_list.at(4);
                        qreal y = y_string.toDouble();
                        footfault_dectect << QPointF(x, y);
                    }
                }
                else if(msg_list.at(1) == "acc difference found") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    acc_difference << QPointF(x, y);
                }
                else if(msg_list.at(1) == "angle difference found") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    angle_difference << QPointF(x, y);
                }
                else if(msg_list.at(1) == "take over request") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    take_over_request << QPointF(x, y);
                }
                else if(msg_list.at(1) == "quit take over") //null
                {
                    QString x_string = msg_list.at(0);
                    QString right_string = x_string.right(10);
                    double x = right_string.toLongLong()/1000000.0 - begin;
                    QString y_string = msg_list.at(2);
                    qreal y = y_string.toDouble();
                    quit_take_over << QPointF(x, y);
                }
            }
        }
    }

    allLines << data_vehicle_vxy
             << data_vehicle_ax
             << data_vehicle_yawrate
             << data_record_vxy
             << data_record_ax
             << data_record_yawrate
             << data_front_wheel_angle
             << data_record_wheel_angle

             << back_collision_ibeo
             << front_collision_ibeo
             << back_collision_fusion
             << front_collision_fusion
             << cutin_collision_risk
             << rear_end_collision_risk
             << gap
             << start_timestamp
             << footfault_hdmap
             << footfault_dectect
             << acc_difference
             << angle_difference
             << take_over_request
             << quit_take_over;
}
