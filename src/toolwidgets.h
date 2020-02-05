/*
 *  File: toolwidgets.h
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */


#ifndef TOOLWIDGETS_H
#define TOOLWIDGETS_H

#include <QDoubleSpinBox>
#include <QString>
#include <QValidator>
#include <QDebug>

class SciDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit SciDoubleSpinBox(QWidget *parent = nullptr);
    ~SciDoubleSpinBox();

    QString textFromValue(double val) const;
    double valueFromText(const QString &text) const;
    QValidator::State validate(QString &input, int &pos) const;

};


#endif // TOOLWIDGETS_H
