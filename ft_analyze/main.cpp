#include <QApplication>
#include "app/mainwindow.h"
#include "app/controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Controller ctrl(0, &w);

    w.show();

    return a.exec();
}
