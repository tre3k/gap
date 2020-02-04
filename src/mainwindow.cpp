/*
 * Under license GNU GLP (c) 2020
 * Autor: Kirill Pshenichnyi
 *
 */

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    SANSData *sans_data = nullptr;
    ImportFile *import_file = new ImportFile("test_files/D0429428.001");
    import_file->open("test_files/D0439792.300");

    //ImportFile *import_file = new ImportFile("test_files/D0439792.300");
    //ImportFile *import_file = new ImportFile("test_files/D0439732.303");
    sans_data = import_file->getSANSData();

    qDebug() << sans_data->getName() << " " << sans_data->getProposal();
    qDebug() << sans_data->getTitle();
    qDebug() << sans_data->getUser();
    qDebug() << sans_data->getSampleName();
    qDebug() << "wavelenght: " <<sans_data->getWaveLenghtInAngstorm() << " A";
    qDebug() << "SD: " <<sans_data->getDetectorSourceDistance() << " m";
    qDebug() << "Time: " << sans_data->getTimeMeasurement() << " sec";
    qDebug() << "Monitor: " << sans_data->getMonitroCounter();


    for(int i=0;i<sans_data->getRawMapSize().x;i++){
        for(int j=0;j<sans_data->getRawMapSize().y;j++){
            qDebug() << sans_data->getMapAt(i,j);
        }
    }


}
