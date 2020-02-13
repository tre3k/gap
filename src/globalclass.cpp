/*
 *  File: globalclass.cpp
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */


#include "globalclass.h"

SANSDataMath::SANSDataMath(QObject *parent) : QObject(parent){

}

FolderClass::FolderClass(QString name, QObject *parent) : QObject(parent)
{
    setFolderName(name);


}


GlobalClass::GlobalClass(QObject *parent) : QObject(parent)
{

}
