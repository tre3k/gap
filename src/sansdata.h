/*
 * Under license GNU GLP (c) 2020
 * Autor: Kirill Pshenichnyi
 *
 */

#ifndef SANSDATA_H
#define SANSDATA_H

#include <QObject>
#include <QString>
#include <QDateTime>

class SANSData : public QObject
{
    Q_OBJECT
public:
    enum polarization_type{
        NON_POLARIZATE,
        POLARIZATE_UP,
        POLARIzATE_DOWN,
        ALREADY
    };

    enum data_type{
        UNKNOWN,
        TECHNICAL,
        BACKGROUND,
        MAGNET_STRUCTURE,
        MAGNET_DINAMYCS
    };

public:
    SANSData(int size_x = 0, int size_y = 0, QObject *parent = nullptr);
    ~SANSData();
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
    double getWaveLenghtInAngstorm(void){
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

    /* Set and Get "name" */
    void setName(QString value){
        name = value;
    }
    QString getName(void){
        return name;
    }

    /* Set and Get "proposal" */
    void setProposal(QString value){
        proposal = value;
    }
    QString getProposal(void){
        return proposal;
    }

    /* Set and Get "title" */
    void setTitle(QString value){
        title = value;
    }
    QString getTitle(void){
        return title;
    }

    /* Set and Get "sample_name" */
    void setSampleName(QString value){
        sample_name = value;
    }
    QString getSampleName(void){
        return sample_name;
    }

    /* Set and Get "User" */
    void setUser(QString value){
        user = value;
    }
    QString getUser(void){
        return user;
    }

    /* Set and Get datetimes */
    void setDateTimeFileISODate(QString datetime);
    void setDateTimeFileUnix(uint64_t datetime);
    void setDateTimeStartMeasurementISODate(QString datetime);
    void setDateTimeStartMeasurementUnix(uint64_t datetime);
    void setDateTimeEndMeasurementISODate(QString datetime);
    void setDateTimeEndMeasurementUnix(uint64_t datetime);

    QDateTime getDateTimeFile(void){
        return dt_file;
    }
    QDateTime getDateTimeStartMeasurement(void){
        return dt_start;
    }
    QDateTime getDateTimeEndMeasurement(void){
        return dt_end;
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
    bool isMapCreated(){
        return is_map_created;
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

    double getMapAt(int i, int j);
    void setMapAt(int i, int j, double value);

private:
    double wavelenght;                                      // Wavelenght in Agnstrom [A]
    double ds_distance;                                     // Distance of soruce to detector in meters [m]
    double monitor_counter;                                 // just monitor counter (before sample enviroment)
    //double amount_count;                                  // all counts [ - reservate - ]
    double time;                                            // time of measurement int sec [s]
    double field;                                           // magnetic field int Tesla [T]
    double temperature;                                     // temperature of sample in Kelvin [K]

    int s_x,s_y;                                            // sizee of intencity map
    double **raw_map;                                       // intencity 2D map
    //double *raw_data;                                     // 1D plolt           [ - reservate - ]

    QString name;                                           // name
    QString proposal;                                       // proposal name
    QString title;                                          // title
    QString sample_name;
    QString user;
    QDateTime dt_file;                                      // date & time file creation
    QDateTime dt_start;                                     // date & time start measurement
    QDateTime dt_end;                                       // date & time end measurmenet

    bool is_normalize = false;
    bool is_map_created = false;
    polarization_type pol_type;
    double monitor_percent = .2;                            // efficienty of monitor from 0 to 1, (default 0.2 - 20%)

private:
    void initEmptyRawMap();                                 // size_x and size_y must be initialized int s_x and s_y
    void deleteRawMap();

};

#endif // SANSDATA_H
