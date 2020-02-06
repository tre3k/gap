/*
 * File: mainwindow.h
 * License: GNU GLPv3 (c) 2020
 * Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>

#include "sansdata.h"
#include "importfile.h"
#include "plots.h"
#include "sansdataviewer.h"
#include "importfileswidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:

};

#endif // MAINWINDOW_H
