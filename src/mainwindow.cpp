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
    // More tests....

    /*
    SANSData *sans_data = nullptr;
    ImportFile *import_file = new ImportFile();

    QStringList filename;
    filename.append("test_files/D0429428.001");
    filename.append("test_files/D0429923.001");
    filename.append("test_files/D0439944.300");

    import_file->open(filename.at(0));

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


    SANSDataViewer *viewer = new SANSDataViewer();
    viewer->viewSANSData(sans_data);
    */

    ImportFilesWidget *import_files_widget = new ImportFilesWidget();

    //auto gc = new GlobalClass();
    auto cw = new CentralWidget();

    auto import_tab = new SideBarUnit("Import",":/icons/open_n.svg",":/icons/open_a.svg");
    cw->addTab(import_tab,import_files_widget);
    cw->addSplit();
    auto help_tab = new SideBarUnit("About", ":/icons/help_n.svg", ":/icons/help_a.svg");
    auto about_widget = new GenerealWidget();
    about_widget->layout()->addWidget(new QLabel("about?"));
    cw->addTab(help_tab, about_widget);

    cw->activate(0);

    this->setCentralWidget(cw);


}
