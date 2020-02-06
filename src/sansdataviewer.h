/*
 *  File: sansdataviewer.h
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 *
 *  Widget with Map Plot and other information about SANS data
 */


#ifndef SANSDATAVIEWER_H
#define SANSDATAVIEWER_H

#include <QSplitter>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QGroupBox>

#include "sansdata.h"
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
    //QVBoxLayout *central_layout;
    GenerealWidget *bottom_widget;

    MapSANSPlot *map_plot;

    QLabel *ds_distance;
    QLabel *sample;
    QLabel *temperature;
    QLabel *field;
    QLabel *time;
    QLabel *proposal;
    QLabel *title;
    QLabel *users;

signals:

};

#endif // SANSDATAVIEWER_H
