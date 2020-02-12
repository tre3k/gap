/*
 *  File: globalclass.h
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */


#ifndef GLOBALCLASS_H
#define GLOBALCLASS_H

#include <QObject>
#include <QVector>

#include "sansdata.h"

class FolderClass : public QObject{
    Q_OBJECT
public:
    explicit FolderClass(QString name = "", QObject *parent = nullptr);

    void setFolderName(QString name){
        folder_name = name;
    }
    QString getFolderName(){
        return folder_name;
    }

private:
    QString folder_name;
};


/* =============================== GLOBAL CLASS =============================== */
class GlobalClass : public QObject
{
    Q_OBJECT
public:
    explicit GlobalClass(QObject *parent = nullptr);

    QVector<FolderClass *> folders;
    QVector<SANSData> imorted;

signals:

};

#endif // GLOBALCLASS_H
