/*
 *  File: importfileswidget.cpp
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */

/*
 *   | splitter                                    |
 *   | - left_widget         | - sans_data_viewer  |
 *   | -- top_left_layout    |                     |
 *   | -- list_widget        |                     |
 *   | -- bottom_left_layout |                     |
 *
 */


#include "importfileswidget.h"


ImportFilesWidget::ImportFilesWidget(QWidget *parent) : GenerealWidget(parent)
{

    auto splitter = new QSplitter(Qt::Horizontal);
    auto left_widget = new QWidget();                                           // left part of splitter
    auto left_layout = new QVBoxLayout(left_widget);                            // with list_widget and buttons
    auto top_left_layout = new QHBoxLayout();
    auto bottom_left_layout = new QHBoxLayout();
    left_layout->setMargin(0);

    open_files_button = new QPushButton("add files");
    import_button = new QPushButton("import");
    select_all_button = new QPushButton("select all files");
    unselect_all_button = new QPushButton("unselect all files");
    clean_button = new QPushButton("clean");

    list_widget = new QListWidget();
    sans_data_viewer = new SANSDataViewer();

    /* empty import_file mecanism */
    import_file = new ImportFile();
    sans_data = new SANSData();

    top_left_layout->addWidget(new QLabel("open files: "));
    top_left_layout->addStretch(0);
    top_left_layout->addWidget(open_files_button);
    bottom_left_layout->addWidget(select_all_button);
    bottom_left_layout->addWidget(unselect_all_button);
    bottom_left_layout->addWidget(clean_button);
    bottom_left_layout->addStretch(0);
    bottom_left_layout->addWidget(import_button);
    left_layout->addLayout(top_left_layout);
    left_layout->addWidget(list_widget);
    left_layout->addLayout(bottom_left_layout);

    splitter->addWidget(left_widget);
    splitter->addWidget(sans_data_viewer);
    central_layout->addWidget(splitter);

    /* Create connections */
    connect(open_files_button,SIGNAL(clicked()),this,SLOT(openFiles()));
    connect(list_widget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(changeCheckState(QModelIndex)));
    connect(list_widget,SIGNAL(currentRowChanged(int)),this,SLOT(selectedItem(int)));
    connect(select_all_button,SIGNAL(clicked()),this,SLOT(selectAll()));
    connect(unselect_all_button,SIGNAL(clicked()),this,SLOT(unselectAll()));
    connect(clean_button,SIGNAL(clicked()),this, SLOT(cleanSelected()));


}

void ImportFilesWidget::openFiles(){
    QStringList files = QFileDialog::getOpenFileNames(nullptr,"open files","","*");
    if(files.count() == 0) return;

    QFileInfo file_info;
    int start = open_files.count();
    for(int i=start;i<files.count()+start;i++){
        open_files.append(files.at(i-start));
        file_info = QFileInfo(open_files.at(i));
        list_widget->addItem(QString(file_info.fileName()));

        list_widget->item(i)->setFlags(list_widget->item(i)->flags() | Qt::ItemIsUserCheckable);
        list_widget->item(i)->setCheckState(Qt::Unchecked);
    }

    //updateOpenList();
}

void ImportFilesWidget::selectAll(){
    for(int i=0;i<list_widget->count();i++) list_widget->item(i)->setCheckState(Qt::Checked);
}

void ImportFilesWidget::unselectAll(){
    for(int i=0;i<list_widget->count();i++) list_widget->item(i)->setCheckState(Qt::Unchecked);
}

void ImportFilesWidget::updateOpenList(){
    list_widget->clear();

    QFileInfo file_info;
    for(int i=0;i<open_files.count();i++){
        file_info = QFileInfo(open_files.at(i));
        list_widget->addItem(QString(file_info.fileName()));

        list_widget->item(i)->setFlags(list_widget->item(i)->flags() | Qt::ItemIsUserCheckable);
        list_widget->item(i)->setCheckState(Qt::Unchecked);

    }
}

void ImportFilesWidget::changeCheckState(QModelIndex model_index){
    int row = model_index.row();
    switch(list_widget->item(row)->checkState()){
    case Qt::Unchecked:
        list_widget->item(row)->setCheckState(Qt::Checked);
        break;

    case Qt::Checked:
        list_widget->item(row)->setCheckState(Qt::Unchecked);
        break;

    case Qt::PartiallyChecked:
        break;
    }
}

void ImportFilesWidget::selectedItem(int row){
    if(row >= open_files.count()) return;
    QString filename = open_files.at(row);

    import_file->open(filename);
    import_file->getSANSData(sans_data);
    sans_data_viewer->viewSANSData(sans_data);
}

void ImportFilesWidget::cleanSelected(){
    bool trigger = true;
    disconnect(list_widget,SIGNAL(currentRowChanged(int)),this,SLOT(selectedItem(int)));
    while(trigger){
        trigger = false;
        if(open_files.count() == 1 && list_widget->item(0)->checkState() == Qt::Checked){
            qDebug () << "last!";
            //open_files.clear();
            //list_widget->clear();   what the bug????? Qt?  segmentation fault
            break;
        }
        for(int i=0;i<open_files.count();i++){
            if(list_widget->item(i)->checkState()==Qt::Checked){
                delete list_widget->takeItem(i);
                open_files.removeAt(i);
                trigger = true;
                break;
            }
        }
    }
    connect(list_widget,SIGNAL(currentRowChanged(int)),this,SLOT(selectedItem(int)));
}
