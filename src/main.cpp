#include <QtWidgets/QApplication>
//#include "purse.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Purse w;
    //w.show();

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
