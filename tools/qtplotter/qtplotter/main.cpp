#include "plotterwindow.h"
#include <QApplication>
#include <QLocale>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //  QLocale::setDefault(QLocale::c());
    PlotterWindow w;
    w.show();

    return a.exec();
}
