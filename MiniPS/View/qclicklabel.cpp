#include "qclicklabel.h"


void QClickLabel::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked(this); // �ڵ���¼��з����ź�
}