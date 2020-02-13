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
    ImportFilesWidget *import_files_widget = new ImportFilesWidget();

    auto gc = new GlobalClass();
    auto cw = new CentralWidget();

    auto import_tab = new SideBarUnit("Import",":/icons/open_n.svg",":/icons/open_a.svg");
    cw->addTab(import_tab,import_files_widget);

    cw->addSplit();


    auto about_tab = new SideBarUnit("About", ":/icons/help_n.svg", ":/icons/help_a.svg");
    auto about_widget = new GenerealWidget();
    about_widget->layout()->addWidget(new QLabel("about?"));
    cw->addTab(about_tab, about_widget);

    cw->activate(0);

    this->setCentralWidget(cw);


}
