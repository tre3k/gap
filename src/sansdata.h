/*
 * Under license GNU GLP (c) 2020
 * Autor: Kirill Pshenichnyi
 *
 */

#ifndef SANSDATA_H
#define SANSDATA_H

#include <math.h>

class SANSData
{
public:
    SANSData(int size_x = 0, int size_y = 0);
    void newRawMap(int size_x = 0, int size_y = 0);

    /* Set and Get ds_distance */
    void setDetectorSourceDistance(double value){
        ds_distance = value;
    }
    double getDetectorSourceDistance(void){
        return ds_distance;
    }

    /* Set and  Get "wavelenght" */
    void setWaveLenght(double value){
        wavelenght = value;
    }
    double getWaveLenght(void){
        return wavelenght;
    }
    double getWaveLenghtInMeters(void){
        return wavelenght * 1e-10;
    }

    /* Set and  Get "monitor_counter" */
    void setMonitroCounter(double value){
        monitor_counter = value;
    }
    double getMonitroCounter(void){
        return monitor_counter;
    }

    /* Set and Get "time" */
    void setTimeMeasurement(double value){
        time = value;
    }
    double getTimeMeasurement(void){
        return time;
    }

    struct s_size{
        int x;
        int y;
    };
    s_size getRawMapSize(void){
        s_size retval;
        retval.x = s_x;
        retval.y = s_y;
        return retval;
    }

private:
    double wavelenght;                                      // Wavelenght in Agnstrom [A]
    double ds_distance;                                     // Distance of soruce to detector in meters [m]
    double monitor_counter;                                 // just monitor counter (before sample enviroment)
    double time;                                            // time of measurement int sec [s]

    int s_x,s_y;
    double **raw_map;

private:
    void initEmptyRawMap();                                 // size_x and size_y must be initialized int s_x and s_y

};

#endif // SANSDATA_H
