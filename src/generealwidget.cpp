/*
 *  File: generalwidget.cpp
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */


#include "generealwidget.h"

GenerealWidget::GenerealWidget(QWidget *parent) : QWidget(parent)
{
    central_layout = new QVBoxLayout(this);
}

GenerealWidget::~GenerealWidget(){

}

void GenerealWidget::addWidget(QWidget *widget){
    central_layout->addWidget(widget);
}

void GenerealWidget::addLayout(QLayout *layout){
    central_layout->addLayout(layout);
}
