/*
 * Under license GNU GLP (c) 2020
 * Autor: Kirill Pshenichnyi
 *
 */

#include "sansdata.h"

SANSData::SANSData(int size_x, int size_y)
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

void SANSData::initEmptyRawMap(){
    raw_map = new double * [s_x];
    for(int i=0;i<s_x;i++) raw_map[i] = new double [s_y];
    return;
}

void SANSData::newRawMap(int size_x, int size_y){
    s_x = size_x;
    s_y = size_y;

    initEmptyRawMap();
}


