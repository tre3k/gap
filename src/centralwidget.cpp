/*
 *  File: centralwidget.h
 *  License: GNU GLPv3 (c) 2020
 *  Autor: Kirill Pshenichnyi
 *
 *  This is part of software "gap"
 */

#include "centralwidget.h"

/* =============================== SideBarUnit Class =============================== */
SideBarUnit::SideBarUnit(QString text, QString image_path_normal, QString image_path_active,QWidget *parent) : QWidget(parent)
{
    /* initilization */
    label = new QLabel();
    label_image = new QLabel();
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignHCenter);
    this->setLayout(layout);

    label_image->setAlignment(Qt::AlignHCenter);
    label->setAlignment(Qt::AlignHCenter);

    layout->addWidget(label_image);
    layout->addWidget(label);

    pAnimation = new QPropertyAnimation(this,"color");
    pAnimation->setDuration(DURATION_ANIMATION);

    setText(text);
    setImage(image_path_normal);

    image_file_active = image_path_active;
    image_file_normal = image_path_normal;

    this->setMouseTracking(false);
    this->setAutoFillBackground(true);

    // set background color also as sidebar RGB #434343
    setPalleteNormal();
}


void SideBarUnit::setText(QString text){
    label->setText("\n<b>"+text+"</b>");

}

void SideBarUnit::setImage(QString filepath){
    QPixmap image(filepath);
    label_image->setPixmap(image.scaled(50,50,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    //label_image->setPixmap(image);
}

void SideBarUnit::mousePressEvent(QMouseEvent *event){
    setPalleteEnabled();
    emit clicked(n_index);
}

void SideBarUnit::mouseReleaseEvent(QMouseEvent *event){
    /* RESERVATION */
}

void SideBarUnit::mouseMoveEvent(QMouseEvent *event){
    /* RESERVATION */
}

void SideBarUnit::setColor(QColor color){
    QPalette pal(palette());
    pal.setColor(QPalette::Background, color);
    pal.setColor(QPalette::WindowText, QColor(Qt::white));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

QColor SideBarUnit::color(){
    return Qt::black;
}

void SideBarUnit::setIndex(int index){
    n_index = index;
}

int SideBarUnit::getIndex(){
    return n_index;
}

/* SLOTS */
void SideBarUnit::setPalleteNormal(){
    pAnimation->stop();
    setImage(image_file_normal);
    setColor(BACKGROUND_COLOR);
}

void SideBarUnit::setPalleteEnabled(){
    setImage(image_file_active);
    pAnimation->setStartValue(BACKGROUND_COLOR);
    pAnimation->setEndValue(BACKLIGHT_COLOR);
    pAnimation->start();
}

void SideBarUnit::setPalleteSelectedWithoutAnimation(){
    setImage(image_file_active);
    setColor(QColor(BACKLIGHT_COLOR));
}

void SideBarUnit::setPalleteSelected(){
    /* RESERVATION */

}

/* =============================== SideBar Class =============================== */
SideBar::SideBar(QWidget *parent) : QWidget(parent)
{
    /* list for units */
    unit_list = new QVector<SideBarUnit *>;

    /* set layout */
    layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->setSpacing(0);
    layout->setMargin(0);

    this->setMaximumWidth(MAX_WIDTH);
    /* Palette */
    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(BACKGROUND_COLOR));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void SideBar::addUnit(SideBarUnit *unit){
    unit_list->append(unit);
    layout->addWidget(unit);
    unit->setIndex(unit_list->size()-1);

    connect(unit,SIGNAL(clicked(int)),
            this,SLOT(unitClicked(int)));
    return;
}

void SideBar::addStretch(int size){
    layout->addStretch(size);
    QPixmap spliter(":/icons/split.svg");
    QLabel *label = new QLabel();
    label->setAlignment(Qt::AlignHCenter);
    label->setPixmap(spliter.scaled(70,50,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    layout->addWidget(label);
}

void SideBar::unselectUnit(int index){
    for(int i=0;i<unit_list->size();i++){
        if(i!=index) unit_list->at(i)->setPalleteNormal();
    }
}

void SideBar::selectUnit(int index){
    unit_list->at(index)->setPalleteSelectedWithoutAnimation();
}

void SideBar::unitClicked(int index){
    unselectUnit(index);
    emit clickedUnit(index);
}


/* =============================== CentralWidget Class =============================== */
CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    sb = new SideBar();
    layout = new QHBoxLayout();

    layout->setMargin(0);
    layout->setSpacing(0);

    this->setLayout(layout);
    layout->addWidget(sb);

    layout->itemAt(0)->setAlignment(Qt::AlignLeft);
    //layout->setAlignment(Qt::AlignLeft);

    connect(sb,SIGNAL(clickedUnit(int)),this,SLOT(slot_activate(int)));

}

CentralWidget::~CentralWidget(){
    delete sb;
    delete layout;
}

void CentralWidget::addTab(SideBarUnit *unit, QWidget *widget){
    sb->addUnit(unit);
    widgets.append(widget);
    layout->addWidget(widget);
    widget->hide();
}

/* set Tab and unselect buttons */
void CentralWidget::slot_activate(int index){
    for(int i=0;i<widgets.size();i++) widgets.at(i)->hide();
    widgets.at(index)->show();
    sb->unselectUnit(index);            // unselected all units (buttons on left tab) except index. Selection button inside SideBarUnit
    emit selected(index);
}

/* activate tab and select unit (not slot) */
void CentralWidget::activate(int index){
    slot_activate(index);
    sb->selectUnit(index);

}

void CentralWidget::addSplit(){
    sb->addStretch(0);
    /* my be need add painter line */
}
