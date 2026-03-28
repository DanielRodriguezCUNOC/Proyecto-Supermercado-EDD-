#include "pantallas/mainwindow.h"
#include "pantallas/pantallasistema.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
    //w.show();
    PantallaSistema pS;
    pS.show();
    return a.exec();
}
