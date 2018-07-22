#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

class QClickLabel :public QLabel
{
    Q_OBJECT
public:
    QClickLabel(QWidget *parent = 0) :QLabel(parent) {}
    ~QClickLabel() {}
signals:
    void clicked(QClickLabel* click); // 点击信号
protected:
    void mouseReleaseEvent(QMouseEvent*); // 重载了鼠标释放事件
};