/*
 *  File: importfile.cpp
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */


#include "importfile.h"

ImportFile::ImportFile(QString filename, QObject *parent) : QObject(parent)
{
    if(filename != nullptr) open(filename);
}

ImportFile::~ImportFile(){
    this->close();
}

void ImportFile::open(QString filename){
    QString type = filename.split('.').last();
    filetype = UNKNOWN;
    /* MLZ File types */
    if( type=="001" || type=="300" || type=="301" || type=="303"){
        filetype = MLZ_FRM2;
        if(type=="001") sub_file_type = MLZ_FRM2_001;
        if(type=="300") sub_file_type = MLZ_FRM2_300;
        if(type=="301") sub_file_type = MLZ_FRM2_301;
        if(type=="302") sub_file_type = MLZ_FRM2_302;                   // [ - reservate - ]
        if(type=="303") sub_file_type = MLZ_FRM2_303;
    }

    if(f.isOpen()) f.close();
    f.setFileName(filename);
    if(!f.open(QIODevice::ReadOnly)){
        is_open = false;
        return;
    }

    text_stream.setDevice(&f);
    is_open = true;
}

void ImportFile::close(){
    f.close();
    is_open = false;
}

SANSData *ImportFile::getSANSData(){
    SANSData *sans_data = new SANSData();
    getSANSData(sans_data);
    return sans_data;
}

void ImportFile::getSANSData(SANSData *sans_data){
    if(!is_open || filetype == UNKNOWN) return;
    sans_data->clean();
    switch(filetype){
    default:
        return;
        break;                          // =)

    case MLZ_FRM2:
        sans_data->setDetectorResolution(8,8);  // DEBUG for SANS-1 machine 8x8 mm resolution
        parserMLZ(sans_data);
        break;

        /* other types */
    }

    this->close();
}

void ImportFile::parserMLZ(SANSData *sans_data){
    enum segment{
        File, Sample, Setup, Counter,
        History, Comment, Counts, Errors
    };

    enum seporator{
        comma,
        ten_symbols
    };

    QString line;
    segment seg;

    int size_map_x = -1;
    int size_map_y = -1;
    bool new_raw_map = false;

    QString raw_number_array;
    //QString raw_errors_array;
    QVector<double> number_array;

    sans_data->setName("test name");

    /* read text loop */
    while(!text_stream.atEnd()){
        line = text_stream.readLine();
        if(line == "%File")     seg = File;
        if(line == "%Sample")   seg = Sample;
        if(line == "%Setup")    seg = Setup;
        if(line == "%Counter")  seg = Counter;
        if(line == "%History")  seg = History;
        if(line == "%Comment")  seg = Comment;
        if(line == "%Counts")   seg = Counts;
        if(line == "%Errors")   seg = Errors;


        switch(seg){
        case File:
            if(line.split('=').first()=="FileName") sans_data->setName(line.split('=').last());
            if(line.split('=').first()=="Proposal") sans_data->setProposal(line.split('=').last());
            if(line.split('=').first()=="Title") sans_data->setTitle(line.split('=').last());
            if(line.split('=').first()=="User") sans_data->setUser(line.split('=').last());
            if(line.split('=').first()=="DataSizeX") size_map_x = QString(line.split('=').last()).toInt();
            if(line.split('=').first()=="DataSizeY") size_map_y = QString(line.split('=').last()).toInt();
            break;

        case Sample:
            if(line.split('=').first()=="SampleName") sans_data->setSampleName(line.split('=').last());
            if(line.split('=').first()=="Magnet") sans_data->setMagneticField(QString(line.split('=').last()).toDouble());
            if(line.split('=').first()=="Temperature") sans_data->setTemperature(QString(line.split('=').last()).toDouble());
            if(line.split('=').first()=="Flipper"){
                if(QString(line.split('=').last())!=""){
                    if(QString(line.split('=').last()).toDouble() > 1.0){
                        sans_data->setPolarizationType(SANSData::POLARIZATE_DOWN);
                    }else{
                        sans_data->setPolarizationType(SANSData::POLARIZATE_UP);
                    }
                }
            }
            break;

        case Setup:
            if(line.split('=').first()=="Lambda") sans_data->setWaveLenght(QString(line.split('=').last()).toDouble());
            if(line.split('=').first()=="SD") sans_data->setDetectorSourceDistance(QString(line.split('=').last()).toDouble());
            if(line.split('=').first()=="Polarization"){
                sans_data->setPolarization(line.split('=').last());
                if(sans_data->getPolarization()=="ng"){
                    sans_data->setPolarizationType(SANSData::NON_POLARIZATE);
                }else{
                    sans_data->Polarizated();
                }
            }
            break;

        case Counter:
            if(line.split('=').first()=="Time") sans_data->setTimeMeasurement(QString(line.split('=').last()).toDouble());
            if(line.split('=').first()=="Moni1") sans_data->setMonitroCounter(QString(line.split('=').last()).toDouble());
            if(line.split('=').first()=="Sum") sans_data->setAmountCount(QString(line.split('=').last()).toDouble());
            break;

        case History:

            break;

        case Comment:
            if(sans_data->getProposal()=="" && line.split('=').first()=="Exp_proposal") sans_data->setProposal(line.split('=').last());
            // in sometimes uses power supply
            if(line.split('=').first()=="ea_psi_curr_status" && sans_data->getPolarizationType()==SANSData::NON_POLARIZATE){
                if(line.split('=').last() == "ok"){
                    sans_data->setPolarizationType(SANSData::POLARIZATE_UP);
                }else{
                    sans_data->setPolarizationType(SANSData::POLARIZATE_DOWN);
                }
            }
            break;

        case Counts:
            if(!new_raw_map){
                sans_data->newRawMap(size_map_x, size_map_y);
                new_raw_map = true;
            }
            if(sans_data->isMapCreated()){
                if(line=="%Counts") continue;
                raw_number_array += line + '\n';
            }
            break;

        case Errors:

            break;
        }
    }

    switch(sub_file_type){
    case MLZ_FRM2_001:
        number_array = MLZComaSeporator(raw_number_array);
        break;
    case MLZ_FRM2_300:
        number_array = MLZ10Symbols(raw_number_array);
        break;
    case MLZ_FRM2_301:
        number_array = MLZ10SymbolsAndComa(raw_number_array);
        break;
    case MLZ_FRM2_303:
        number_array = MLZ10SymbolsAndComa(raw_number_array);
        break;
    }

    int count = 0;
    for(int j=0; j<sans_data->getRawMapSize().y; j++){
        for(int i=0; i<sans_data->getRawMapSize().x; i++){
            sans_data->setMapAt(i,j,number_array.at(count));
            count++;
        }
    }

    if(sans_data->isPolarizated() && sans_data->getPolarizationType()==SANSData::NON_POLARIZATE){
        sans_data->setPolarizationType(SANSData::POLARIZATED);
    }
}

QVector<double> ImportFile::MLZComaSeporator(QString raw_number_array){
    raw_number_array.replace('\n',',');
    QStringList str_list = raw_number_array.split(',');
    QVector<double> retval;

    for(int i=0;i<str_list.size();i++) retval.append(QString(str_list.at(i)).toDouble());

    return retval;
}

/* NEED TEST */
QVector<double> ImportFile::MLZ10Symbols(QString raw_number_array){
    QVector<double> retval;
    QString tmp;
    int ten_count = 0;

    raw_number_array.remove('\n');

    for(int i=0;i<raw_number_array.size();i++){
        tmp.append(raw_number_array.at(i));
        if(ten_count == 9){
            ten_count = -1;
            retval.append(QString(tmp).toDouble());
            tmp = "";
        }
        ten_count++;
    }
    return retval;
}

QVector<double> ImportFile::MLZ10SymbolsAndComa(QString raw_number_array){
    return MLZComaSeporator(raw_number_array);
}
