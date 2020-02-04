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


}
