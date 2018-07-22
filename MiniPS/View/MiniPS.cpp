#include "MiniPS.h"
#include "Command/OpenFileCommand.h"
#include "Command/ContrastCommand.h"
#include "Notification//Notification.h"
#include "Command/Filter1Command.h"
#include "Command/GaussianFilterCommand.h"
#include "Command/SaveFileCommand.h"
#include "Command/UndoCommand.h"

MiniPS::MiniPS(QWidget *parent)
    : QWidget(parent)
{
    InitialWid();
    updateViewSink = std::static_pointer_cast<UpdateViewNotification> \
        (std::shared_ptr<UpdateViewNotification>(new UpdateViewNotification(std::shared_ptr<MiniPS>(this))));

}


MiniPS::~MiniPS()
{

}
void MiniPS::Option() {
    son = new OptionWindow();
    connect(son->sldcon, SIGNAL(sliderReleased()), this, SLOT(OptionContrast()));
    connect(son->butconsub, SIGNAL(clicked()), this, SLOT(OptionContrast()));
    connect(son->sldbri, SIGNAL(sliderReleased()), this, SLOT(OptionContrast()));
    connect(son->butbrisub, SIGNAL(clicked()), this, SLOT(OptionContrast()));
    connect(son->butguassfil, SIGNAL(clicked()), this, SLOT(OptionFilGuass()));
    connect(son->butfil1_past, SIGNAL(clicked()), this, SLOT(OptionFilPast()));
    connect(son->butfil2_black, SIGNAL(clicked()), this, SLOT(OptionFilBlack()));
    connect(son->undocon, SIGNAL(clicked(QClickLabel*)), this, SLOT(Undo()));
    connect(son->undofil, SIGNAL(clicked(QClickLabel*)), this, SLOT(Undo()));
    connect(son->butfacenoti, SIGNAL(clicked()), this, SLOT(FaceDetect()));
    connect(son->undonoti, SIGNAL(clicked(QClickLabel*)), this, SLOT(Undo()));
    son->show();
}
void MiniPS::InitialWid() {
    this->setFixedSize(960, 425);
    this->autoFillBackground();//背景自动填充

    piclabel = new QClickLabel;//显示图片
    load = new QClickLabel;//加载图片的按钮
    save = new QClickLabel;
    objpiclabel = new QLabel;//标签
    stacklay = new QGridLayout;
    butlay = new QGridLayout;
    toplay = new QGridLayout;

    //初始化背景
    QPixmap *bkg= new QPixmap("bkg.jpg");
    *bkg = bkg->scaled(960, 425, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    background.setColor(this->backgroundRole(), QColor(192, 253, 123));
    background.setBrush(this->backgroundRole(), QBrush(*bkg));
    this->setPalette(background);

    //加载图片的按键
    //load->setText("load new picture");
    load->setFixedSize(100, 100);
    //save->setText("save this picture");
    save->setFixedSize(100, 100);

    QPixmap *picload = new QPixmap("load.png");
    QPixmap *picsave = new QPixmap("save.png");
    *picload = picload->scaled(load->width(), load->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    load->setPixmap(*picload);
    *picsave = picsave->scaled(save->width(), save->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    save->setPixmap(*picsave);


    //半透明化的按钮
    QGraphicsOpacityEffect *opacityEffect1 = new QGraphicsOpacityEffect;
    load->setGraphicsEffect(opacityEffect1);
    opacityEffect1->setOpacity(0.3);

    QGraphicsOpacityEffect *opacityEffect2 = new QGraphicsOpacityEffect;
    save->setGraphicsEffect(opacityEffect2);
    opacityEffect2->setOpacity(0.3);


    //带框
    objpiclabel->setFixedSize(240, 240);
    objpiclabel->setFrameShape(QFrame::Box);
    objpiclabel->setStyleSheet("border-width: 3px;border-style: solid;border-color: rgb(117,207,219);");

    piclabel->setFixedSize(80, 80);
    piclabel->setFrameShape(QFrame::Box);
    piclabel->setStyleSheet("border-width: 3px;border-style: solid;border-color: rgb(255,44,14);");



    butlay->addWidget(load, 0, 0);
    butlay->addWidget(save, 1, 0);

    stacklay->addWidget(piclabel, 0, 0);
    stacklay->addWidget(objpiclabel, 1, 1);

    toplay->addLayout(butlay, 0, 0);
    toplay->addLayout(stacklay, 0, 1);

    this->setLayout(toplay);

    this->setWindowTitle(QWidget::tr("MiniPS"));
    //连接信号槽
    connect(load, SIGNAL(clicked(QClickLabel*)), this, SLOT(LoadPic()));
    connect(piclabel, SIGNAL(clicked(QClickLabel*)), this, SLOT(Option()));
    connect(save, SIGNAL(clicked(QClickLabel*)), this, SLOT(SavePic()));
}
void MiniPS::ResizeWid(QPixmap pic) {
    double ratio;
    double picw = pic.width();
    double pich = pic.height();
    double widw, widh, oriw, orih, objw, objh,stackh,stackw;
    if (1080 / picw<720 / pich)
        ratio = 1080 / picw;
    else
        ratio = 720 / pich;
    widw = picw*ratio;
    widh = pich*ratio;
    this->setFixedSize(widw, widh);
    if (picw>pich) {//横向布局
        stackw = widw - 110;
        stackh = widh;
        butlay->removeWidget(save);
        butlay->addWidget(save,1, 0);
        toplay->removeItem(stacklay);
        toplay->addLayout(stacklay, 0, 1);

    }
    else {//竖向布局
        stackw = widw;
        stackh = widh - 110;
        butlay->removeWidget(save);
        butlay->addWidget(save, 0, 1);
        toplay->removeItem(stacklay);
        toplay->addLayout(stacklay, 1, 0);
    }
    stackw = stackw*0.82*0.25;
    stackh = stackh*0.82*0.75;
    if (stackw / picw < stackh / pich)
        ratio = stackw / picw;
    else
        ratio = stackh / pich;
    oriw = picw*ratio;
    orih = pich*ratio;
    objw = oriw * 3;
    objh = orih * 3;
    piclabel->setFixedSize(oriw, orih);
    objpiclabel->setFixedSize(objw, objh);


}

//public
void MiniPS::SetOpenFileCommand(std::shared_ptr<ICommandBase> cmd) {
    openFileCommand = cmd;
}
void MiniPS::SetContrastCommand(std::shared_ptr<ICommandBase> cmd) {
    contrastCommand = cmd;
};
void MiniPS::SetGaussianFilterCommand(std::shared_ptr<ICommandBase> cmd) {
    guassianFilterCommand = cmd;
};
void MiniPS::SetFilter1Command(std::shared_ptr<ICommandBase> cmd) {
    filter1Command = cmd;
};
void MiniPS::SetFilter2Command(std::shared_ptr<ICommandBase> cmd) {
    filter2Command = cmd;
};
void MiniPS::SetSaveFileCommand(std::shared_ptr<ICommandBase> cmd) {
    saveFileCommand = cmd;
}
void MiniPS::SetUndoCommand(std::shared_ptr<ICommandBase>cmd) {
    undoCommand = cmd;
}
void MiniPS:: SetFaceDetectCommand(std::shared_ptr<ICommandBase>cmd) {
    faceDetectCommand = cmd;
}
std::shared_ptr<IPropertyNotification> MiniPS::GetUpdateViewSink() {
    return updateViewSink;
}


void MiniPS::SetQImage(std::shared_ptr<QImage> _qimg) {
    Img_ptr = _qimg;
}
void MiniPS::SetBackQImage(std::shared_ptr<QImage> _qimg) {
    BackImg_ptr = _qimg;
}
void MiniPS::SetObjQImage(std::shared_ptr<QImage> _qimg) {
    ObjImg_ptr = _qimg;
}

void MiniPS::SetBackGround() {
    QImage Img = *BackImg_ptr;
    QPixmap rst = QPixmap::fromImage(Img).scaled(this->width(), this->height());
    background.setColor(this->backgroundRole(), QColor(192, 253, 123));
    background.setBrush(this->backgroundRole(), QBrush(QPixmap(rst)));
    this->setPalette(background);
}
void MiniPS::ShowPicture() {
    QImage Img = *Img_ptr;
    QPixmap pic = QPixmap::fromImage(Img);
    ResizeWid(pic);
    QPixmap newpic = pic.scaled(piclabel->width(), piclabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    piclabel->setPixmap(newpic);
}
void MiniPS::ShowObjPicture() {
    QImage Img = *ObjImg_ptr;
    QPixmap pic = QPixmap::fromImage(Img);
    QPixmap newpic = pic.scaled(objpiclabel->width(), objpiclabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    objpiclabel->setPixmap(newpic);
}

void MiniPS::LoadPic() {
    QFileDialog *fileDialog = new QFileDialog(this);
    QString file_full = fileDialog->getOpenFileName(this, "select and open", "/", "Images(*.png *.jpg *.jpeg *.bmp)");
    QFileInfo fi = QFileInfo(file_full);
    std::string filename = fi.filePath().toStdString();
    if (filename!= "") {
        openFileCommand->SetParameter(std::static_pointer_cast<PathParameter>(std::shared_ptr<PathParameter>(new PathParameter(filename))));
        openFileCommand->Exec();
    }

}
void MiniPS::OptionContrast(){
    double con = son->sldcon->value();
    double bri = son->sldbri->value();
    contrastCommand->SetParameter(std::static_pointer_cast<ContrastParameter>(std::shared_ptr<ContrastParameter>(new ContrastParameter(con,bri))));
    contrastCommand->Exec();
}
void MiniPS::OptionFilGuass(){
    guassianFilterCommand->Exec();
}
void MiniPS::OptionFilPast(){
    filter1Command->Exec();

}
void MiniPS::OptionFilBlack(){
    filter2Command->Exec();
}
void MiniPS::SavePic() {
    QFileDialog *fileDialog = new QFileDialog(this);
    QString file_full = fileDialog->getSaveFileName(this, tr("save"), "", "Images(*.png *.jpg *.jpeg *.bmp)");
    QFileInfo fi = QFileInfo(file_full);
    std::string filename = fi.filePath().toStdString();
    if (filename!=""){
        saveFileCommand->SetParameter(std::static_pointer_cast<SPathParameter>(std::shared_ptr<SPathParameter>(new SPathParameter(filename))));
        saveFileCommand->Exec();
    }
}
void MiniPS::Undo(){
    undoCommand->Exec();
}
void MiniPS::FaceDetect() {
    faceDetectCommand->Exec();
}
/*
version 2018.7.19
#include "View/MiniPS.h"
#include "ui_MiniPS.h"
#include "Command/OpenFileCommand.h"
#include "Notification//Notification.h"
#include <string>
#include <QtWidgets/QFileDialog>  
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QLabel>

MiniPS::MiniPS(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);
    updateViewSink = std::static_pointer_cast<UpdateViewNotification> \
        (std::shared_ptr<UpdateViewNotification>(new UpdateViewNotification(std::shared_ptr<MiniPS>(this)))); 
}

void MiniPS::SetOpenFileCommand(std::shared_ptr<ICommandBase> cmd) {
    openFileCommand = cmd;
}

std::shared_ptr<IPropertyNotification> MiniPS::GetUpdateViewSink() {
    return updateViewSink;
}


void MiniPS::SetQImage(std::shared_ptr<QImage> _qimg) {
    qimg = _qimg;
}
void MiniPS::OnOpenButtonClicked() {
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
        tr("Choose an image"),
        "",
        tr("Image (*.png *.bmp *.jpg *.tif *.GIF)"));
    if (filename.isEmpty()) {
        QMessageBox::information(this, tr("Open file failed!"), tr("OK"));
        return;
    }
    else {
        openFileCommand->SetParameter(std::static_pointer_cast<PathParameter>(std::shared_ptr<PathParameter>(new PathParameter(filename.toStdString()))));
        openFileCommand->Exec();
    }
}

void MiniPS::ShowPicture(){
    QLabel *label = new QLabel();
    label->setPixmap(QPixmap::fromImage(*qimg));
    label->resize(QSize(qimg->width(), qimg->height()));
    ui.pic->setWidget(label);
}
*/