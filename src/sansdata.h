/*
 * Under license GNU GLP (c) 2020
 * Autor: Kirill Pshenichnyi
 *
 */

#ifndef SANSDATA_H
#define SANSDATA_H


class SANSData
{
public:
    SANSData();

    void setDetectorSourceDistance(double value){
        ds_distance = value;
    }
    double getDetectorSourceDistance(void){
        return ds_distance;
    }

    void setWaveLenght(double value){
        wavelenght = value;
    }
    double getWaveLenght(void){
        return wavelenght;
    }

    void setMonitroCounter(double value){
        monitor_counter = value;
    }
    double getMonitroCounter(void){
        return monitor_counter;
    }

private:
    double wavelenght;                                      // Wavelenght in Agnstrom [A]
    double ds_distance;                                     // Distance of soruce to detector in meters [m]
    double monitor_counter;                                 // just monitor counter (before sample enviroment)



};

#endif // SANSDATA_H
