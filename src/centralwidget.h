/*
 *  File: centralwidget.cpp
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */

#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QMouseEvent>
#include <QPropertyAnimation>

#include "generealwidget.h"

/* =============================== SideBarUnit Class =============================== */
#define BACKGROUND_COLOR "#0b262c"
#define HIGHLIGHTED_COLOR "#575757"   // RESERVATION
#define BACKLIGHT_COLOR "#091d22"

#define DURATION_ANIMATION 300          // in ms

class SideBarUnit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit SideBarUnit(QString text="", QString image_path_normal="",QString image_path_active="", QWidget *parent = nullptr);
    void setText(QString text);
    void setImage(QString filepath);
    void setIndex(int index);
    int getIndex(void);

    void setColor(QColor color);
    QColor color();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QLabel *label;
    QVBoxLayout *layout;
    QLabel *label_image;
    QPropertyAnimation *pAnimation;

    QString image_file_normal, image_file_active;

    int n_index = 0;

signals:
    void clicked(int);

public slots:
    void setPalleteNormal();
    void setPalleteSelected();
    void setPalleteSelectedWithoutAnimation();
    void setPalleteEnabled();

};


/* =============================== SideBar Class =============================== */
#define MAX_WIDTH 100

class SideBar : public QWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = nullptr);
    void unselectUnit(int index);
    void selectUnit(int index);

private:
    QVBoxLayout *layout;
    QVector<SideBarUnit *> *unit_list;

signals:
    void clickedUnit(int);

public slots:
    void addUnit(SideBarUnit *unit);
    void addStretch(int size);
    void unitClicked(int index);
};


/* =============================== Central Widget Class =============================== */
class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget();
    void activate(int index);

private:
    SideBar *sb;
    QHBoxLayout *layout;
    QVector<QWidget *> widgets;

signals:
    void selected(int);

public slots:
    void addTab(SideBarUnit *sbUnit, QWidget *widget);
    void slot_activate(int index);
    void addSplit();
};

#endif // CENTRALWIDGET_H
