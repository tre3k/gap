/*
 *  File: generalwidget.h
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */


#ifndef GENEREALWIDGET_H
#define GENEREALWIDGET_H

#include <QWidget>

class GenerealWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GenerealWidget(QWidget *parent = nullptr);
    ~GenerealWidget();

signals:

};

#endif // GENEREALWIDGET_H
