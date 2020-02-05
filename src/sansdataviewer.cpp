/*
 *  File: sansdataviewer.cpp
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */


#include "sansdataviewer.h"

SANSDataViewer::SANSDataViewer(QWidget *parent) : GenerealWidget(parent)
{
    central_layout = new QVBoxLayout(this);
    bottom_widget = new GenerealWidget();
    auto form_layout = new QFormLayout(bottom_widget);
    auto splitter = new QSplitter(Qt::Vertical);
    map_plot = new MapSANSPlot();

    proposal = new QLabel();
    ds_distance = new QLabel();
    temperature = new QLabel();
    field = new QLabel();
    sample = new QLabel();

    splitter->addWidget(map_plot);
    splitter->addWidget(bottom_widget);
    central_layout->addWidget(splitter);

    form_layout->addRow("proposal: ",proposal);
    form_layout->addRow("sample: ", sample);
    form_layout->addRow("temperature <i>T</i>: ", temperature);
    form_layout->addRow("magnetic field <i>H</i>:", field);


}

SANSDataViewer::~SANSDataViewer(){

}

void SANSDataViewer::viewSANSData(SANSData *sans_data){
    map_plot->buildSANSData(sans_data);

    proposal->setText(sans_data->getProposal());
    sample->setText(sans_data->getSampleName());
    temperature->setText("<b>"+QString::number(sans_data->getTemperature())+QString(" K</b>"));
    field->setText("<b>"+QString::number(1000*sans_data->getMagneticField())+QString(" mT</b>"));

}
