/********************************************************************************
** Form generated from reading UI file 'MiniPS.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINIPS_H
#define UI_MINIPS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiniPSClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_open;
    QPushButton *pushButton_2;
    QScrollArea *pic;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MiniPSClass)
    {
        if (MiniPSClass->objectName().isEmpty())
            MiniPSClass->setObjectName(QStringLiteral("MiniPSClass"));
        MiniPSClass->resize(600, 400);
        centralWidget = new QWidget(MiniPSClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_open = new QPushButton(centralWidget);
        pushButton_open->setObjectName(QStringLiteral("pushButton_open"));
        pushButton_open->setGeometry(QRect(90, 60, 141, 81));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(90, 180, 141, 71));
        pic = new QScrollArea(centralWidget);
        pic->setObjectName(QStringLiteral("pic"));
        pic->setGeometry(QRect(330, 90, 261, 171));
        pic->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 259, 169));
        pic->setWidget(scrollAreaWidgetContents);
        MiniPSClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MiniPSClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        MiniPSClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MiniPSClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MiniPSClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MiniPSClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MiniPSClass->setStatusBar(statusBar);

        retranslateUi(MiniPSClass);
        QObject::connect(pushButton_open, SIGNAL(clicked()), MiniPSClass, SLOT(OnOpenButtonClicked()));

        QMetaObject::connectSlotsByName(MiniPSClass);
    } // setupUi

    void retranslateUi(QMainWindow *MiniPSClass)
    {
        MiniPSClass->setWindowTitle(QApplication::translate("MiniPSClass", "MiniPS", Q_NULLPTR));
        pushButton_open->setText(QApplication::translate("MiniPSClass", "Open", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MiniPSClass", "End", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MiniPSClass: public Ui_MiniPSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIPS_H
