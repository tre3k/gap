/*
 *  File: toolwidgets.h
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */

#include "toolwidgets.h"

SciDoubleSpinBox::SciDoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent){

}

SciDoubleSpinBox::~SciDoubleSpinBox(){

}

QValidator::State SciDoubleSpinBox::validate(QString &input, int &pos) const{
    /*
    bool ok;
    input.toDouble(&ok);
    if(ok){
        return QValidator::Acceptable;
    }else{
        return QValidator::Invalid;
    }
    */
    return QValidator::Acceptable;   // very simple, all free!
}

QString SciDoubleSpinBox::textFromValue(double val) const{
    return QString::number(val,'e',2);
}

double SciDoubleSpinBox::valueFromText(const QString &text) const{
    return text.toDouble();
}
