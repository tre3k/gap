/*
 *  File: sansdataviewer.cpp
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */

/*     |   central_layout   |
 *     | - splitter         |
 *     | -- map_plot        |
 *     |____________________|
 *     | -- buttom_widget   |
 *     | --- form_layout    |
 */


#include "sansdataviewer.h"

SANSDataViewer::SANSDataViewer(QWidget *parent) : GenerealWidget(parent)
{

    central_layout->setMargin(0);

    bottom_widget = new GenerealWidget();
    auto form_layout = new QFormLayout();
    bottom_widget->addLayout(form_layout);
    auto splitter = new QSplitter(Qt::Vertical);
    map_plot = new MapSANSPlot();

    proposal = new QLabel();
    ds_distance = new QLabel();
    temperature = new QLabel();
    field = new QLabel();
    sample = new QLabel();
    time = new QLabel();
    title = new QLabel();
    title->setWordWrap(true);
    title->setTextInteractionFlags(Qt::TextSelectableByMouse);
    users = new QLabel();
    users->setWordWrap(true);
    users->setTextInteractionFlags(Qt::TextSelectableByMouse);

    splitter->addWidget(map_plot);
    splitter->addWidget(bottom_widget);
    central_layout->addWidget(splitter);

    form_layout->addRow("Proposal: ",proposal);
    form_layout->addRow("Sample: ", sample);
    form_layout->addRow("Temperature <i>T</i>: ", temperature);
    form_layout->addRow("Magnetic field <i>H</i>:", field);
    form_layout->addRow("Time of measurement: ", time);
    form_layout->addRow("Title: ", title);
    form_layout->addRow("User: ", users);


}

SANSDataViewer::~SANSDataViewer(){

}

void SANSDataViewer::viewSANSData(SANSData *sans_data){
    /* build plot */
    map_plot->buildSANSData(sans_data);
    /* show text on labels */
    proposal->setText(sans_data->getProposal());
    sample->setText(sans_data->getSampleName());
    temperature->setText("<b>"+QString::number(sans_data->getTemperature())+QString(" K</b>"));
    field->setText("<b>"+QString::number(1000*sans_data->getMagneticField())+QString(" mT</b>"));
    time->setText(QString::number(sans_data->getTimeMeasurement())+" sec");
    title->setText(sans_data->getTitle());
    users->setText(sans_data->getUser());
}
