#include <QtWidgets/QApplication>
#include "purse.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Purse w;
    w.show();
    
    return a.exec();
}
