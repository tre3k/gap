/*
 * File: mainwindow.cpp
 * License: GNU GLPv3 (c) 2020
 * Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    SANSData *sans_data = nullptr;
    ImportFile *import_file = new ImportFile();

    auto i_plot = new MapSANSPlot();
    this->setCentralWidget(i_plot);

    QStringList filename;
    filename.append("test_files/D0429428.001");
    filename.append("test_files/D0429923.001");
    filename.append("test_files/D0439944.300");

    import_file->open(filename.at(1));

    sans_data = new SANSData();
    qDebug() << sans_data;

    //sans_data = import_file->getSANSData();
    import_file->getSANSData(sans_data);
    //sans_data->normalize();

    qDebug() << sans_data;

    qDebug() << sans_data->getName() << " " << sans_data->getProposal();
    qDebug() << sans_data->getTitle();
    qDebug() << sans_data->getUser();
    qDebug() << sans_data->getSampleName();
    qDebug() << "wavelenght: " <<sans_data->getWaveLenghtInAngstorm() << " A";
    qDebug() << "SD: " <<sans_data->getDetectorSourceDistance() << " m";
    qDebug() << "Time: " << sans_data->getTimeMeasurement() << " sec";
    qDebug() << "Monitor: " << sans_data->getMonitroCounter();

    i_plot->buildSANSData(sans_data);

    delete sans_data;
}
