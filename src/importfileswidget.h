/*
 *  File: importfileswidget.h
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */


#ifndef IMPORTFILESWIDGET_H
#define IMPORTFILESWIDGET_H

#include <QSplitter>
#include <QLayout>
#include <QListWidget>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

#include "sansdata.h"
#include "importfile.h"
#include "sansdataviewer.h"
#include "generealwidget.h"

class ImportFilesWidget : public GenerealWidget
{
    Q_OBJECT
public:
    explicit ImportFilesWidget(QWidget *parent = nullptr);
    ~ImportFilesWidget();

    QStringList getOpenFiles(void){
        return open_files;
    }
    QStringList getImportedFiles(void){
        return imported_files;
    }

private:
    SANSDataViewer *sans_data_viewer;
    QListWidget *list_widget;

    QPushButton *open_files_button;
    QPushButton *import_button;
    QPushButton *select_all_button;
    QPushButton *unselect_all_button;
    QPushButton *clean_button;

    QStringList open_files;
    QStringList imported_files;

    ImportFile *import_file;
    SANSData *sans_data;

signals:

public slots:
    void openFiles();
    void selectAll();
    void unselectAll();
    void updateOpenList();
    void changeCheckState(QModelIndex model_index);
    void selectedItem(int row);
    void cleanSelected();

    void importRelease();

};

#endif // IMPORTFILESWIDGET_H
