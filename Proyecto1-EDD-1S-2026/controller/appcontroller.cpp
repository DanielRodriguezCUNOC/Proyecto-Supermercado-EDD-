#include "appcontroller.h"
#include <QDebug>

AppController::AppController(QObject *parent) : QObject(parent)
{
    // Instanciar Controladores secundarios
    estructurasController = new EstructurasController();
    fileController = new FileController();
    
    // Inyección de dependencias al ViewController para que pueda acceder a los modelos y graficarlos
    viewController = new ViewController(
        estructurasController->getUnorderedList(),
        estructurasController->getListaOrdenada(),
        estructurasController->getArbolB(),
        estructurasController->getArbolBPlus(),
        estructurasController->getArbolAVL()
    );

    // Instanciar la Vista Principal
    vistaSistema = new PantallaSistema();

    // Conectar Signals y Slots (Coordinación)
    
    // Conectar el botón de agregar de la vista con nuestro slot orquestador
    connect(vistaSistema, &PantallaSistema::agregarProducto, this, &AppController::onAgregarProducto);

}

AppController::~AppController()
{
    delete vistaSistema;
    delete estructurasController;
    delete fileController;
    delete viewController;
}

void AppController::iniciar()
{
    // Mostrar la pantalla principal
    if (vistaSistema) {
        vistaSistema->show();
    }
}

void AppController::onAgregarProducto()
{
    qDebug() << "AppController: Señal de agregarProducto recibida de la vista.";
}
