#include "optionwindow.h"
OptionWindow::OptionWindow(QWidget *parent):QWidget(parent)
{
    
    setwid();
    setlist();



    toplay=new QHBoxLayout;
    toplay->addWidget(stack);
    toplay->addWidget(list);
    setLayout(toplay);

}
void OptionWindow::setwid(){

    stack = new QStackedWidget;
    //³õÊ¼»¯
    setconwid();
    setfilwid();
    setnotiwid();
    stack->addWidget(contrast);
    stack->addWidget(filter);
    stack->addWidget(notify);
}
void OptionWindow::setlist(){
    list=new QListWidget;
    list->setFixedSize(150, 240);
    list->insertItem(0,tr("contrast&brightness"));
    list->insertItem(1,tr("filter"));
    list->insertItem(2, tr("notify"));
    connect(list,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)));

}
void OptionWindow::setconwid() {
    contrast = new QWidget;
    QGridLayout *laycon = new QGridLayout;
    QLabel *labcon = new QLabel;
    QLabel *labbri = new QLabel;
    butconsub = new QPushButton;
    butconsub->setText("try");
    butconsub->setFixedSize(80, 40);

    sldcon = new QSlider(Qt::Horizontal);
    sldcon->setMinimum(0);
    sldcon->setMaximum(150);
    sldcon->setFixedSize(200, 20);
    sldcon->setValue(50);
    sldcon->setTickPosition(QSlider::TicksAbove);
    sldcon->setTickInterval(10);

    spncon = new QSpinBox;
    spncon->setMaximum(150);
    spncon->setMinimum(0);
    spncon->setFixedSize(50, 30);
    spncon->setValue(50);
    spncon->setSingleStep(5);


    undocon = new QClickLabel;
    undocon->setFixedSize(80, 80);
    QPixmap *picundo = new QPixmap("undo.png");
    *picundo = picundo->scaled(undocon->width(), undocon->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    undocon->setPixmap(*picundo);

    labcon->setFixedSize(30, 30);
    QPixmap *piccon = new QPixmap("contrast.jpg");
    *piccon = piccon->scaled(labcon->width(), labcon->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    labcon->setPixmap(*piccon);


    connect(sldcon, SIGNAL(valueChanged(int)),spncon , SLOT(setValue(int)));
    connect(spncon, SIGNAL(valueChanged(int)), sldcon, SLOT(setValue(int)));
    laycon->addWidget(labcon, 0, 0);
    laycon->addWidget(sldcon, 0, 1);
    laycon->addWidget(spncon, 0, 2);
    laycon->addWidget(butconsub, 0, 3);


    butbrisub = new QPushButton;
    butbrisub->setText("try");
    butbrisub->setFixedSize(80, 40);

    sldbri = new QSlider(Qt::Horizontal);
    sldbri->setMinimum(0);
    sldbri->setMaximum(150);
    sldbri->setFixedSize(200, 20);
    sldbri->setValue(50);
    sldbri->setTickPosition(QSlider::TicksAbove);
    sldbri->setTickInterval(10);

    spnbri = new QSpinBox;
    spnbri->setMaximum(150);
    spnbri->setMinimum(0);
    spnbri->setFixedSize(50, 30);
    spnbri->setValue(50);
    spnbri->setSingleStep(5);


    labbri->setFixedSize(30, 30);
    QPixmap *picbri = new QPixmap("bright.jpg");
    *picbri = picbri->scaled(labbri->width(), labbri->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    labbri->setPixmap(*picbri);

    connect(sldbri, SIGNAL(valueChanged(int)), spnbri, SLOT(setValue(int)));
    connect(spnbri, SIGNAL(valueChanged(int)), sldbri, SLOT(setValue(int)));
    laycon->addWidget(labbri, 2, 0);
    laycon->addWidget(sldbri, 2, 1);
    laycon->addWidget(spnbri, 2, 2);
    laycon->addWidget(butbrisub, 2, 3);

    laycon->addWidget(undocon, 3, 3);
    contrast->setLayout(laycon);
    contrast->setFixedSize(480, 240);
}
void OptionWindow::setfilwid() {
    filter = new QWidget;
    QGridLayout *layfil = new QGridLayout;

    butguassfil = new QPushButton;
    butfil1_past = new QPushButton;
    butfil2_black= new QPushButton;
    
    butguassfil->setText("GuassFilter");
    butfil1_past->setText("PastFilter");
    butfil2_black->setText("BlackFilter");
    
    butguassfil->setFixedSize(80, 40);
    butfil1_past->setFixedSize(80, 40);
    butfil2_black->setFixedSize(80, 40);


    undofil = new QClickLabel;
    undofil->setFixedSize(80, 80);
    QPixmap *picundo = new QPixmap("undo.png");
    *picundo = picundo->scaled(undofil->width(), undofil->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    undofil->setPixmap(*picundo);

    layfil->addWidget(butguassfil, 0, 0);
    layfil->addWidget(butfil1_past, 0, 1);
    layfil->addWidget(butfil2_black, 0, 2);
    layfil->addWidget(undofil,1, 2);
    filter->setLayout(layfil);
    filter->setFixedSize(320, 240);
}

void OptionWindow::setnotiwid() {
    notify = new QWidget;
    butfacenoti = new QPushButton;
    butfacenoti->setFixedSize(100, 50);
    butfacenoti->setText("Face Detect");
    
    undonoti = new QClickLabel;
    undonoti->setFixedSize(80, 80);
    QPixmap *picundo = new QPixmap("undo.png");
    *picundo = picundo->scaled(undonoti->width(), undonoti->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    undonoti->setPixmap(*picundo);

    QGridLayout *laynoti = new QGridLayout;
    laynoti->addWidget(butfacenoti, 0, 0);
    laynoti->addWidget(undonoti, 1, 1);

    notify->setLayout(laynoti);
    notify->setFixedSize(240, 160);
}
