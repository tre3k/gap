/*
 *  File: sansdataviewer.h
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */


#ifndef SANSDATAVIEWER_H
#define SANSDATAVIEWER_H

#include <QSplitter>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>

#include "generealwidget.h"
#include "sansdata.h"
#include "plots.h"

class SANSDataViewer : public GenerealWidget
{
    Q_OBJECT
public:
    explicit SANSDataViewer(QWidget *parent = nullptr);
    ~SANSDataViewer();

    void viewSANSData(SANSData *sans_data);

private:
    QVBoxLayout *central_layout;
    GenerealWidget *bottom_widget;

    MapSANSPlot *map_plot;

    QLabel *ds_distance;
    QLabel *sample;
    QLabel *temperature;
    QLabel *field;
    QLabel *proposal;


signals:

};

#endif // SANSDATAVIEWER_H
