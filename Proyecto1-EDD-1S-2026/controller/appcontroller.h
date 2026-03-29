#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include "estructurascontroller.h"
#include "filecontroller.h"
#include "viewcontroller.h"
#include "../view/pantallas/pantallasistema.h"

class AppController : public QObject
{
    Q_OBJECT

private:
    PantallaSistema* vistaSistema;
    EstructurasController* estructurasController;
    FileController* fileController;
    ViewController* viewController;

private slots:
    // Slot intermedio para manejar la interacción de la vista
    void onAgregarProducto();

public:
    AppController(QObject *parent = nullptr);
    ~AppController();

    // Método para arrancar la aplicación
    void iniciar();
};

#endif // APPCONTROLLER_H
