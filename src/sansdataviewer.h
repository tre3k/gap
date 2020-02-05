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

#include "generealwidget.h"

class SANSDataViewer : public GenerealWidget
{
    Q_OBJECT
public:
    explicit SANSDataViewer(QWidget *parent = nullptr);

signals:

};

#endif // SANSDATAVIEWER_H
