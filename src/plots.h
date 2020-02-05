/*
 *  File: plots.h
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */


#include <QObject>
#include <QWidget>
#include <qcustomplot.h>

#include "generealwidget.h"


class InteractivePlot : public QCustomPlot
{
    Q_OBJECT
public:

public:
    InteractivePlot(QWidget *parent = nullptr);
    ~InteractivePlot();

protected:
    bool x_log = false;
    bool y_log = false;

private:


public slots:

protected slots:
    void slot_sAxies_drag_zoom(QCPAxis *,QCPAxis::SelectablePart,QMouseEvent *);
    void slot_full_drag_zoom(QMouseEvent *);
    void slot_selectionChanged();
    void slot_contextMenuReq(QPoint p);

    void exportToPDF();
    void exportToBMP();
    void exportToJPG();
    void exportToPNG();

    void setXLog();
    void setYLog();


signals:

};

/*
class MapSANSPlot : public InteractivePlot
{

};
*/
