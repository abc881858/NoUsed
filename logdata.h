#ifndef LOGDATA_H
#define LOGDATA_H

#include <QList>
#include <QPointF>

typedef QList<QPointF> Data;

class LogData
{
public:
    static LogData* instance();
    QString fileName;
    void setupSeries();

    Data data_vehicle_vxy;
    Data data_vehicle_ax;
    Data data_vehicle_yawrate;
    Data data_record_vxy;
    Data data_record_ax;
    Data data_record_yawrate;
    Data data_front_wheel_angle;
    Data data_record_wheel_angle;

    Data back_collision_ibeo;
    Data front_collision_ibeo;
    Data back_collision_fusion;
    Data front_collision_fusion;
    Data cutin_collision_risk;
    Data rear_end_collision_risk;
    Data gap;
    Data start_timestamp;
    Data footfault_hdmap;
    Data footfault_dectect;
    Data acc_difference;
    Data angle_difference;
    Data take_over_request;
    Data quit_take_over;

    QList<Data> allLines;

    int beginTime;

};

#endif // LOGDATA_H
