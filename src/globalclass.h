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

class SANSDataMath : public QObject{
    Q_OBJECT
public:
    explicit SANSDataMath(QObject *parent = nullptr);

    //void calculate();    // foreground - background
    //void multiply(SANSData *);

private:
    QVector<SANSData *> background;
    QVector<SANSData *> foreground;

    SANSData *result;

};


/* =============================== Folder CLASS =============================== */
class FolderClass : public QObject{
    Q_OBJECT
public:
    explicit FolderClass(QString name = "", QObject *parent = nullptr);
    QVector<SANSData *> imorted;
    // for somes temperature and magnet field
    //QVector<QVector <SANSDataMath *>> sans_data_math;
    typedef QVector<SANSDataMath *> fileds_points;


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


signals:

};

#endif // GLOBALCLASS_H
