#include "App/app.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App* app = new App;
    app->show();
    return a.exec();
}
