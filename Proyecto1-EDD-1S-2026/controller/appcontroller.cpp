#include "appcontroller.h"
#include <QDebug>

AppController::AppController(QObject *parent) : QObject(parent)
{
    // 1. Instanciar Controladores secundarios
    estructurasController = new EstructurasController();
    fileController = new FileController();
    viewController = new ViewController();

    // 2. Instanciar la Vista Principal
    vistaSistema = new PantallaSistema();

    // 3. Conectar Signals y Slots (Coordinación)
    
    // Conectar el botón de agregar de la vista con nuestro slot orquestador
    connect(vistaSistema, &PantallaSistema::agregarProducto, this, &AppController::onAgregarProducto);

    // Aquí irían más conexiones, por ejemplo: conectando reportes de datos a viewController 
    // connect(estructurasController, &EstructurasController::etructurasActualizadas, 
    //         viewController, &ViewController::actualizarVista);

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
    // Mostrar la pantalla principal una vez que todo está ensamblado
    if (vistaSistema) {
        vistaSistema->show();
    }
}

void AppController::onAgregarProducto()
{
    qDebug() << "AppController: Señal de agregarProducto recibida de la vista.";
    // TODO: Obtener datos reales de los QLineEdits de PantallaSistema.
    // Como PantallaSistema::agregarProducto no envía los datos aún, enviamos un log.
    // Cuando la vista envíe los datos, llamaremos a estructurasController->agregarProducto(...)
    // estructurasController->agregarProducto("Manzana", "123", "Fruta", "2026-12-01", "Marca", 5.0, 100);
}
