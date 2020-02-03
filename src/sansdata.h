/*
 * Under license GNU GLP (c) 2020
 * Autor: Kirill Pshenichnyi
 *
 */

#ifndef SANSDATA_H
#define SANSDATA_H

#include <QObject>
#include <QString>

class SANSData : public QObject
{
    Q_OBJECT
public:
    enum polarization_type{
        NON_POLARIZATE,
        POLARIZATE_UP,
        POLARIzATE_DOWN
    };

public:
    SANSData(int size_x = 0, int size_y = 0, QObject *parent = nullptr);
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
    double getWaveLenghtInNanoMeters(void){
        return wavelenght * .1;
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

    /* Set and Get "field" */
    void setMagneticField(double value){
        field = value;
    }
    double getMagneticField(void){
        return field;
    }

    /* Set and Get "temperature" */
    void setTemperature(double value){
        temperature = value;
    }
    double getTemperature(void){
        return temperature;
    }

    /* get size of intencity map*/
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

    void normalize(void);
    bool isNormalize(void){
        return is_normalize;
    }

    void setPolarizationType(polarization_type type){
        pol_type = type;
    }
    polarization_type getPolarizationType(void){
        return pol_type;
    }

    const QString getUnitIntencity(void){
        if(is_normalize){
            return (const QString) "count/time";
        }else{
            return (const QString) "count";
        }
    }

private:
    double wavelenght;                                      // Wavelenght in Agnstrom [A]
    double ds_distance;                                     // Distance of soruce to detector in meters [m]
    double monitor_counter;                                 // just monitor counter (before sample enviroment)
    double time;                                            // time of measurement int sec [s]
    double field;                                           // magnetic field int Tesla [T]
    double temperature;                                     // temperature of sample in Kelvin [K]

    int s_x,s_y;                                            // sizee of intencity map
    double **raw_map;                                       // intencity map

    bool is_normalize = false;
    polarization_type pol_type;
    double monitor_percent = .2;                            // efficienty of monitor from 0 to 1, (default 0.2 - 20%)

private:
    void initEmptyRawMap();                                 // size_x and size_y must be initialized int s_x and s_y

};

#endif // SANSDATA_H
