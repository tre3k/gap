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
    s_x = 0;
    s_y = 0;
}

/* convert intencity unit from count to arb.units/time */
void SANSData::normalize(){
    if(raw_map == nullptr || is_normalize) return;

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

/* convert Q units */
SANSData::border SANSData::getQBorderRad(){
    border retval;

    double Lx = detector_resolution.x*s_x/1000;                 //size of detector in meters
    double Ly = detector_resolution.y*s_y/1000;

    retval.x = atan(Lx/2/ds_distance);
    retval.y = atan(Ly/2/ds_distance);

    return retval;
}

SANSData::border SANSData::getQBorderMrad(){
    border retval;
    retval = getQBorderRad();
    retval.x *= 1000;
    retval.y *= 1000;
    return retval;
}

SANSData::border SANSData::getQBorderAngstrom(){
    border retval;
    double k_i = 2*M_PI/wavelenght;                              // in 1/Angstrom
    retval = getQBorderRad();
    retval.x *= k_i;
    retval.y *= k_i;
    return retval;
}

SANSData::border SANSData::getQBorderNanometers(){
    border retval;
    retval = getQBorderAngstrom();
    retval.x *= 10;
    retval.y *= 10;
    return retval;
}

void SANSData::clean(){
    deleteRawMap();

    wavelenght = 0.0;
    ds_distance = 0.0;
    monitor_counter = 1.0;
    time = 1.0;
    field = 0.0;
    temperature = -1;

    name.clear();
    proposal.clear();
    title.clear();
    sample_name.clear();
    user.clear();
    dt_file = QDateTime::fromTime_t(0);
    dt_start = QDateTime::fromTime_t(0);
    dt_end = QDateTime::fromTime_t(0);
    detector_resolution.x = 0;
    detector_resolution.y = 0;

    is_normalize = false;
    is_map_created = false;
    pol_type = NON_POLARIZATE;
    monitor_percent = .2;

}
