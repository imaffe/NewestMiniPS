#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QSlider> 
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtGui/QPixmap>
#include <View/qclicklabel.h>
class OptionWindow: public QWidget
{
    Q_OBJECT
public:
    OptionWindow(QWidget *parent = 0);
    QPushButton *butconsub;
    QSlider *sldcon;
    QSpinBox *spncon;
    QPushButton *butbrisub;
    QSlider *sldbri;    
    QSpinBox *spnbri;

    QPushButton *butguassfil;
    QPushButton *butfil1_past;
    QPushButton *butfil2_black;

    QPushButton *butfacenoti;

    QClickLabel *undocon;
    QClickLabel *undofil;
    QClickLabel *undonoti;


 

private:
    void setlist();
    void setwid();
    QWidget *contrast;
    QWidget *filter;
    QWidget *notify;
    QHBoxLayout *toplay;
    QStackedWidget *stack;
    QListWidget *list;
    void setconwid();
    void setfilwid();
    void setnotiwid();

private slots:


};

#endif // OPTIONWINDOW_H
