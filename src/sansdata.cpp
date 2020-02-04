/*
 * Under license GNU GLP (c) 2020
 * Autor: Kirill Pshenichnyi
 *
 */

#include "sansdata.h"

SANSData::SANSData(int size_x, int size_y, QObject *parent) : QObject(parent)
{
    if(size_x == 0 || size_y == 0){
        raw_map = nullptr;
    }else{
        s_x = size_x;
        s_y = size_y;

        initEmptyRawMap();
    }
    return;
}

SANSData::~SANSData(){
    deleteRawMap();
    return;
}


void SANSData::initEmptyRawMap(){
    raw_map = new double * [s_x];
    for(int i=0;i<s_x;i++) raw_map[i] = new double [s_y];
    is_map_created = true;
    return;
}

void SANSData::newRawMap(int size_x, int size_y){
    if(size_x <= 0 || size_y <= 0) return;
    s_x = size_x;
    s_y = size_y;

    initEmptyRawMap();
}

void SANSData::deleteRawMap(){
    if(s_x == 0 || s_y == 0) return;
    for(int i=0;i<s_x;i++) delete raw_map[i];
    is_map_created = false;
    delete raw_map;
}

/* convert intencity unit from count to arb.units/time */
void SANSData::normalize(){
    if(raw_map == nullptr) return;

    double incident_intencity = monitor_counter/monitor_percent;

    for(int i=0;i<s_x;i++){
        for(int j=0;j<s_y;j++){
            raw_map[i][j] = raw_map[i][j]/time/incident_intencity;
        }
    }
    is_normalize = true;
}

/* set DataTimes */
void SANSData::setDateTimeFileISODate(QString datetime){
    dt_file = QDateTime().fromString(datetime,Qt::ISODate);
    return;
}
void SANSData::setDateTimeFileUnix(uint64_t datetime){
    dt_file = QDateTime().fromTime_t(datetime);
    return;
}

void SANSData::setDateTimeStartMeasurementISODate(QString datetime){
    dt_start = QDateTime().fromString(datetime,Qt::ISODate);
    return;
}
void SANSData::setDateTimeStartMeasurementUnix(uint64_t datetime){
    dt_start = QDateTime().fromTime_t(datetime);
    return;
}

void SANSData::setDateTimeEndMeasurementISODate(QString datetime){
    dt_end = QDateTime().fromString(datetime,Qt::ISODate);
    return;
}
void SANSData::setDateTimeEndMeasurementUnix(uint64_t datetime){
    dt_end = QDateTime().fromTime_t(datetime);
    return;
}

double SANSData::getMapAt(int i, int j){
    if(i >= 0 && i < s_x && j >= 0 && j < s_y){
        return raw_map[i][j];
    }else{
        return 0.0;
    }
}

void SANSData::setMapAt(int i, int j, double value){
    if(i >= 0 && i < s_x && j >= 0 && j < s_y) raw_map[i][j] = value;
}
