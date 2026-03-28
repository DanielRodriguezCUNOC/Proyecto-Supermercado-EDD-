#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H
#include <QObject>
#include "estructurascontroller.h"
#include "filecontroller.h"
#include "pantallas/pantallasistema.h"
#include "viewcontroller.h"

class AppController : public QObject
{
    Q_OBJECT

private:
    PantallaSistema* vistaSistema;
    EstructurasController* sistemaController;
    FileController* fileController;
    ViewController* viewController;

private slots:
    void agregarProducto();

public:
    AppController();
};

#endif // APPCONTROLLER_H
