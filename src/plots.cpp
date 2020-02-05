/*
 *  File: plots.cpp
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */

#include "plots.h"

/*  ============================================ InteractivePlot - general plot for others plots ============================================ */
InteractivePlot::InteractivePlot(QWidget *parent) : QCustomPlot(parent){
    this->setInteractions(QCP::iRangeZoom |
                          QCP::iRangeDrag |
                          QCP::iMultiSelect |
                          QCP::iSelectLegend |
                          QCP::iSelectPlottables |
                          QCP::iSelectAxes);
    this->xAxis2->setVisible(true);
    this->yAxis2->setVisible(true);

    connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)),this->xAxis2, SLOT(setRange(QCPRange)));
    connect(this->yAxis, SIGNAL(rangeChanged(QCPRange)), this->yAxis2, SLOT(setRange(QCPRange)));

    connect(this,SIGNAL(axisClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)),this,SLOT(slot_sAxies_drag_zoom(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)));
    connect(this,SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(slot_full_drag_zoom(QMouseEvent*)));
    connect(this,SIGNAL(selectionChangedByUser()),this,SLOT(slot_selectionChanged()));

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slot_contextMenuReq(QPoint)));

    // for points
    QLocale locale("en_EN.UTF-8");
    this->setLocale(locale);
    // сделать стили оформления + шрифты (возможно загрузка из конф. файла)

}

void InteractivePlot::slot_sAxies_drag_zoom(QCPAxis* sAxis,QCPAxis::SelectablePart part,QMouseEvent* event){
    this->axisRect()->setRangeDrag(sAxis->orientation());
    this->axisRect()->setRangeZoom(sAxis->orientation());
    return;
}

void InteractivePlot::slot_full_drag_zoom(QMouseEvent *mouseEvent){
    this->axisRect()->setRangeDrag(this->xAxis->orientation()|
                                   this->yAxis->orientation());
    this->axisRect()->setRangeZoom(this->xAxis->orientation()|
                                   this->yAxis->orientation());
    return;
}

void InteractivePlot::slot_selectionChanged(){
    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || this->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
          this->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || this->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
      {
        this->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        this->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
      }

      // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
      if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || this->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
          this->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || this->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
      {
        this->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        this->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
      }

      // synchronize selection of graphs with selection of corresponding legend items:
      for (int i=0; i<this->graphCount(); ++i)
      {
        QCPGraph *graph = this->graph(i);
        QCPPlottableLegendItem *item = this->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
          item->setSelected(true);
          graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
        }
      }
    return;
}

void InteractivePlot::slot_contextMenuReq(QPoint p){
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    QMenu *menu_export = new QMenu("Export");
    menu_export->setAttribute(Qt::WA_DeleteOnClose);
    menu->addMenu(menu_export);

    menu_export->addAction("bmp",this,SLOT(exportToBMP()));
    menu_export->addAction("jpg",this,SLOT(exportToJPG()));
    menu_export->addAction("pdf",this,SLOT(exportToPDF()));
    menu_export->addAction("png",this,SLOT(exportToPNG()));

    if(!x_log){
        menu->addAction("x log scale",this,SLOT(setXLog()));
    }else{
        menu->addAction("x linear scale",this,SLOT(setXLog()));
    }

    if(!y_log){
        menu->addAction("y log scale",this,SLOT(setYLog()));
    }else{
        menu->addAction("y linear scale",this,SLOT(setYLog()));
    }

    menu->popup(this->mapToGlobal(p));
}

void InteractivePlot::exportToBMP(){
    auto filename = QFileDialog::getSaveFileName(nullptr,"Save",".bmp","(*.bmp *.BMP)");
    if(filename!=nullptr) this->saveBmp(filename);
}

void InteractivePlot::exportToJPG(){
    auto filename = QFileDialog::getSaveFileName(nullptr,"Save",".jpg","(*.jpg *.JPG)");
    if(filename!=nullptr) this->saveJpg(filename);
}

void InteractivePlot::exportToPDF(){
    auto filename = QFileDialog::getSaveFileName(nullptr,"Save",".pdf","(*.pdf *.PDF)");
    if(filename!=nullptr) this->savePdf(filename);
}

void InteractivePlot::exportToPNG(){
    auto filename = QFileDialog::getSaveFileName(nullptr,"Save",".png","(*.png *.PNG)");
    if(filename!=nullptr) this->savePng(filename);
}

void InteractivePlot::setYLog(){
    y_log = !y_log;
    if(y_log){
        this->yAxis->setScaleType(QCPAxis::stLogarithmic);
        this->yAxis2->setScaleType(QCPAxis::stLogarithmic);
    }else{
        this->yAxis->setScaleType(QCPAxis::stLinear);
        this->yAxis2->setScaleType(QCPAxis::stLinear);
    }
    this->replot();
}

void InteractivePlot::setXLog(){
    x_log = !x_log;
    if(x_log){
        this->xAxis->setScaleType(QCPAxis::stLogarithmic);
        this->xAxis2->setScaleType(QCPAxis::stLogarithmic);
    }else{
        this->xAxis->setScaleType(QCPAxis::stLinear);
        this->xAxis2->setScaleType(QCPAxis::stLinear);
    }
    this->replot();
}

InteractivePlot::~InteractivePlot(){

}


/*  ============================================ MapSANSPlot - 2D Map plots for SANSData ============================================ */
MapSANSPlot::MapSANSPlot(QWidget *parent) : GenerealWidget(parent)
{
    plot = new InteractivePlot();
    central_layout = new QVBoxLayout(this);                                                     // main layout in this widget
    tool_layout_one = new QHBoxLayout();
    tool_layout_two = new QHBoxLayout();

    central_layout->setMargin(0);
    central_layout->setSpacing(2);

    central_layout->addWidget(plot);
    central_layout->addLayout(tool_layout_one);
    central_layout->addLayout(tool_layout_two);

    /* init tools widgets */
    combo_select_units = new QComboBox();
    buttonRescale = new QPushButton("rescale");
    spinBoxMax = new SciDoubleSpinBox();
    spinBoxMin = new SciDoubleSpinBox();
    check_hold = new QCheckBox("hold");
    check_log_scale = new QCheckBox("log");

    spinBoxMax->setRange(-999999999.99999,999999999.99999);
    spinBoxMin->setRange(-999999999.99999,999999999.99999);
    spinBoxMax->setDecimals(999999);
    spinBoxMin->setDecimals(999999);

    spinBoxMax->setValue(100.0);
    spinBoxMin->setValue(-100.0);

    spinBoxMax->setMaximumWidth(80);
    spinBoxMin->setMaximumWidth(80);

    combo_select_units->addItem("pixels");
    combo_select_units->addItem("wave vector [1/Å]");
    combo_select_units->addItem("wave vector [1/nm]");
    combo_select_units->addItem("angle θ [mrad]");
    combo_select_units->addItem("reletiv [-1;1]");

    /* add tools to layout */
    tool_layout_one->addWidget(new QLabel("Unit"));
    tool_layout_one->addWidget(combo_select_units);
    tool_layout_one->addStretch();
    tool_layout_one->addWidget(new QLabel("max:"));
    tool_layout_one->addWidget(spinBoxMax,0,Qt::AlignRight);
    tool_layout_one->addWidget(new QLabel("min:"));
    tool_layout_one->addWidget(spinBoxMin,0,Qt::AlignRight);

    tool_layout_two->addWidget(buttonRescale);
    tool_layout_two->addStretch();
    tool_layout_two->addWidget(check_hold,0,Qt::AlignRight);
    tool_layout_two->addWidget(check_log_scale,0,Qt::AlignRight);

    /* set color map and other attributes for 2D Plot */
    colorMap = new QCPColorMap(plot->xAxis,plot->yAxis);
    colorScale = new QCPColorScale(plot);
    colorScale->setType(QCPAxis::atRight);
    plot->plotLayout()->addElement(0,1,colorScale);

    colorMap->setColorScale(colorScale);
    colorMap->setGradient(QCPColorGradient::gpJet);         // добавить возможность выбора разных карт из опций

    QCPMarginGroup *marginGroup = new QCPMarginGroup(plot);
    plot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    /* tools connections */
    connect(check_log_scale,SIGNAL(clicked(bool)), this,SLOT(logScale(bool)));
    connect(check_hold,SIGNAL(clicked(bool)), this,SLOT(hold(bool)));
    connect(combo_select_units,SIGNAL(activated(int)), this,SLOT(setUnitAxis(int)));
    connect(buttonRescale,SIGNAL(clicked()),this,SLOT(rescaleAxis()));
    connect(colorScale,SIGNAL(dataRangeChanged(QCPRange)),this,SLOT(changeDataRange(QCPRange)));
}

MapSANSPlot::~MapSANSPlot(){

}

void MapSANSPlot::logScale(bool state){
    if(state){
        colorMap->setDataScaleType(QCPAxis::stLogarithmic);
    }else{
        colorMap->setDataScaleType(QCPAxis::stLinear);
    }
    setRangeZAxis();
    return;
}

void MapSANSPlot::hold(bool state){
    if(state){
        connect(spinBoxMax,SIGNAL(valueChanged(double)),this,SLOT(setRangeZAxis()));
        connect(spinBoxMin,SIGNAL(valueChanged(double)),this,SLOT(setRangeZAxis()));
    }else{
        disconnect(spinBoxMax,SIGNAL(valueChanged(double)),this,SLOT(setRangeZAxis()));
        disconnect(spinBoxMin,SIGNAL(valueChanged(double)),this,SLOT(setRangeZAxis()));
    }
    setRangeZAxis();
}


void MapSANSPlot::setRangeZAxis(){
    if(check_hold->isChecked()){
        colorMap->setDataRange(QCPRange(spinBoxMin->value(),spinBoxMax->value()));
    }else{
        colorMap->rescaleDataRange(true);
    }
    plot->rescaleAxes();
    plot->replot();
}

void MapSANSPlot::rescaleAxis(){
    hold(check_hold->isChecked());
    plot->rescaleAxes();
    plot->replot();
}

void MapSANSPlot::changeDataRange(QCPRange range){
    if(!check_hold->isChecked()){
        spinBoxMax->setValue(range.upper);
        spinBoxMin->setValue(range.lower);
    }
}


/* build SANSData */
void MapSANSPlot::setSANSData(SANSData *sans_data){
    s_d = sans_data;
}

void MapSANSPlot::setUnitAxis(int unit){
    switch(unit){
    case Gap::pixel_unit:
        colorMap->data()->setRange(QCPRange(0,s_d->getRawMapSize().x),
                                   QCPRange(0,s_d->getRawMapSize().y));
        plot->xAxis->setLabel("pixels x");
        plot->yAxis->setLabel("pixels y");
        break;

    case Gap::theta_unit:
        colorMap->data()->setRange(QCPRange(-s_d->getQBorderMrad().x,s_d->getQBorderMrad().x),
                                    QCPRange(-s_d->getQBorderMrad().y,s_d->getQBorderMrad().y));
        plot->xAxis->setLabel(QString("θx, mrad").toHtmlEscaped());
        plot->yAxis->setLabel("θy, mrad");
        break;

    case Gap::angstrom_unit:
        colorMap->data()->setRange(QCPRange(-s_d->getQBorderAngstrom().x,s_d->getQBorderAngstrom().x),
                                    QCPRange(-s_d->getQBorderAngstrom().y,s_d->getQBorderAngstrom().y));
        plot->xAxis->setLabel("wave vector Qx, 1/Å");
        plot->yAxis->setLabel("wave vector Qy, 1/Å");
        break;

    case Gap::nanometers_unit:
        colorMap->data()->setRange(QCPRange(-s_d->getQBorderNanometers().x,s_d->getQBorderNanometers().x),
                                    QCPRange(-s_d->getQBorderNanometers().y,s_d->getQBorderNanometers().y));
        plot->xAxis->setLabel("wave vector Qx, 1/nm");
        plot->yAxis->setLabel("wave vector Qy, 1/nm");
        break;

    case Gap::rel_unit:
        colorMap->data()->setRange(QCPRange(-1,1), QCPRange(-1,1));
        plot->xAxis->setLabel("x, arb. units");
        plot->yAxis->setLabel("y, arb. units");
        break;
    }
    rescaleAxis();
}

void MapSANSPlot::buildSANSData(SANSData *sans_data){
    setSANSData(sans_data);
    buildSANSData();
}

void MapSANSPlot::buildSANSData(){
    if(s_d==nullptr) return;
    colorMap->data()->setSize(s_d->getRawMapSize().x,s_d->getRawMapSize().y);
    for(int i=0; i<s_d->getRawMapSize().x; i++){
        for(int j=0; j<s_d->getRawMapSize().y; j++){
            colorMap->data()->setCell(i,j,s_d->getMapAt(i,j));
        }
    }
    setUnitAxis(combo_select_units->currentIndex());
    setRangeZAxis();

}
