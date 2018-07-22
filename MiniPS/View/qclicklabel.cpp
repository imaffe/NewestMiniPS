#include "qclicklabel.h"


void QClickLabel::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked(this); // 在点击事件中发送信号
}