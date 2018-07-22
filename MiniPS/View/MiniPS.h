#pragma once

#include <QtWidgets/QWidget>
#include <memory>

#include "View/qclicklabel.h"
#include "View/optionwindow.h"
#include <QtWidgets/QLayout>
#include <QtGui/QImage>
#include <QtGui/QPalette>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtCore/QFile>
#include <QtWidgets/QGraphicsOpacityEffect>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>

#include "Comman/Comman.h"


class MiniPS : public QWidget
{
    Q_OBJECT
private:
    //界面元素
    QGridLayout *butlay;
    QGridLayout *stacklay;//界面
    QGridLayout *toplay;
    QClickLabel *piclabel;//显示图片
    QLabel *objpiclabel;
    QClickLabel *load;//加载图片
    QClickLabel *save;//存储图片
    QPalette background;//背景
    OptionWindow *son;
    
    void ResizeWid(QPixmap);
    void InitialWid();


    //私有图片指针
    std::shared_ptr<QImage> Img_ptr;
    std::shared_ptr<QImage> BackImg_ptr;
    std::shared_ptr<QImage> ObjImg_ptr;


private slots:
    void LoadPic();
    void SavePic();
    void Option();
    void OptionContrast();
    void OptionFilGuass();
    void OptionFilPast();
    void OptionFilBlack();
    void Undo();
    void FaceDetect();
public:
    MiniPS(QWidget *parent = 0);
    ~MiniPS();

    //公共指针
    std::shared_ptr<ICommandBase> openFileCommand;
    std::shared_ptr<ICommandBase> contrastCommand;
    std::shared_ptr<ICommandBase> guassianFilterCommand;
    std::shared_ptr<ICommandBase> filter1Command;
    std::shared_ptr<ICommandBase> filter2Command;
    std::shared_ptr<ICommandBase> saveFileCommand;
    std::shared_ptr<ICommandBase>undoCommand;
    std::shared_ptr <ICommandBase> faceDetectCommand;
    std::shared_ptr<IPropertyNotification> updateViewSink;

    //操作函数
    void ShowPicture();//显示原图
    void SetBackGround();//设置背景
    void ShowObjPicture();//显示目标图片
    
    //外界暴露函数
    void SetOpenFileCommand(std::shared_ptr<ICommandBase>);
    void SetContrastCommand(std::shared_ptr<ICommandBase>);
    void SetGaussianFilterCommand(std::shared_ptr<ICommandBase>);
    void SetFilter1Command(std::shared_ptr<ICommandBase>);
    void SetFilter2Command(std::shared_ptr<ICommandBase>);
    std::shared_ptr<IPropertyNotification> GetUpdateViewSink();
    void SetQImage(std::shared_ptr<QImage>);
    void SetBackQImage(std::shared_ptr<QImage>);
    void SetObjQImage(std::shared_ptr<QImage>);
    void SetSaveFileCommand(std::shared_ptr<ICommandBase>);
    void SetUndoCommand(std::shared_ptr<ICommandBase>);
    void SetFaceDetectCommand(std::shared_ptr<ICommandBase>);
   




};
/*
version2018.7.19
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MiniPS.h"
#include "Comman/Comman.h"


class MiniPS : public QMainWindow
{
    Q_OBJECT

public:
    MiniPS(QWidget *parent = Q_NULLPTR);
    void SetOpenFileCommand(std::shared_ptr<ICommandBase>);
    std::shared_ptr<IPropertyNotification> GetUpdateViewSink();
    void SetQImage(std::shared_ptr<QImage>);
    void ShowPicture();
    
private slots:
    void OnOpenButtonClicked();
private:
    Ui::MiniPSClass ui;
    std::shared_ptr<QImage> qimg;
public:
    std::shared_ptr<ICommandBase> openFileCommand;
    std::shared_ptr<IPropertyNotification> updateViewSink;
    
};
*/