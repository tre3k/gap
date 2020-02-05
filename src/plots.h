/*
 *  File: plots.h
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */

#ifndef PLOTS_H
#define PLOTS_H

#include <QObject>
#include <QWidget>
#include <qcustomplot.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>

#include "generealwidget.h"
#include "sansdata.h"
#include "toolwidgets.h"

/*  ============================================ InteractivePlot ============================================ */

namespace Gap {
    enum units{
        pixel_unit,
        angstrom_unit,
        nanometers_unit,
        theta_unit,
        rel_unit                                                    //[-1,1]
    };
}


class InteractivePlot : public QCustomPlot
{
    Q_OBJECT
public:
    explicit InteractivePlot(QWidget *parent = nullptr);
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

/*  ============================================ MapSANSPlot ============================================ */
class MapSANSPlot : public GenerealWidget
{
    Q_OBJECT
public:
    explicit MapSANSPlot(QWidget *parent = nullptr);
    ~MapSANSPlot();

public:
    void setSANSData(SANSData *sans_data);
    void buildSANSData(SANSData *sans_data);
    void buildSANSData();

private:
    SANSData *s_d = nullptr;

protected:
    InteractivePlot *plot;

    QVBoxLayout *central_layout;
    QHBoxLayout *tool_layout_one;
    QHBoxLayout *tool_layout_two;

    SciDoubleSpinBox *spinBoxMax;
    SciDoubleSpinBox *spinBoxMin;
    QCheckBox *check_hold;
    QCheckBox *check_log_scale;
    QComboBox *combo_select_units;
    QPushButton *buttonRescale;

    QCPColorMap *colorMap;
    QCPColorScale *colorScale;

protected slots:
    void logScale(bool state);
    void hold(bool state);
    void setRangeZAxis(void);
    void setUnitAxis(int unit);
    void rescaleAxis(void);
    void changeDataRange(QCPRange range);

};

#endif          // PLOTS_H
