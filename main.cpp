#include "showPointCloud.h"
#include <QtWidgets/QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    showPointCloud w;
    w.show();
   // w.showImagePointCloud();
    return a.exec();
}
