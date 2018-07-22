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
    void clicked(QClickLabel* click); // ����ź�
protected:
    void mouseReleaseEvent(QMouseEvent*); // ����������ͷ��¼�
};