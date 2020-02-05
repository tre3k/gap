/*
 *  File: importfile.h
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */


#ifndef IMPORTFILE_H
#define IMPORTFILE_H

#include <QObject>
#include <QFile>
#include <QTextStream>

#include <QDebug>

#include "sansdata.h"

class ImportFile : public QObject
{
    Q_OBJECT

public:
    enum file_type{
        UNKNOWN,
        MLZ_FRM2,
        MLZ_FRM2_001,
        MLZ_FRM2_300,
        MLZ_FRM2_301,
        MLZ_FRM2_302,
        MLZ_FRM2_303
    };

public:
    ImportFile(QString filename = nullptr, QObject *parent = nullptr);
    ~ImportFile();

    void open(QString filename);
    void close(void);
    SANSData *getSANSData(void);

    bool isOpen(void){
        return is_open;
    }



private:
    QFile f;
    QTextStream text_stream;

    bool is_open = false;
    file_type filetype = UNKNOWN;
    file_type sub_file_type = UNKNOWN;

private:
    void parserMLZ(SANSData *sans_data);
    QVector<double> MLZComaSeporator(QString raw_number_array);
    QVector<double> MLZ10Symbols(QString raw_number_array);
    QVector<double> MLZ10SymbolsAndComa(QString raw_number_array);

};

#endif // IMPORTFILE_H
