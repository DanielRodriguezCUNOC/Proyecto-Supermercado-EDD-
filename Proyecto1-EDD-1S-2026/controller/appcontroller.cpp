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
        estructurasController->getArbolAVL());

    // Instanciar la Vista Principal
    vistaSistema = new PantallaSistema();
    vistaSistema->setAppController(this);

    connect(vistaSistema, &PantallaSistema::archivoCSVSeleccionado,
            this, &AppController::cargarArchivoCSV);
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
    if (vistaSistema)
    {
        vistaSistema->show();
    }
}

void AppController::onAgregarProducto()
{
    qDebug() << "AppController: Señal de agregarProducto recibida de la vista.";
}

void AppController::agregarProducto(const QString &nombre, const QString &codigoBarra, const QString &categoria,
                                    const QDate &fechaCaducidad, const QString &marca, double precio, int stock)
{
}

void AppController::cargarArchivoCSV(const QString &ruta)
{
    const QList<Product> productos = fileController->cargarCSV(ruta);
    qDebug() << "CSV cargado:" << ruta << "Productos válidos:" << productos.size();

    for (const Product &p : productos) {
        estructurasController->agregarProducto(
            p.getName(),
            p.getBarcode(),
            p.getCategory(),
            p.getExpiryDate(),
            p.getBrand(),
            p.getPrice(),
            p.getStock());
    }
}
