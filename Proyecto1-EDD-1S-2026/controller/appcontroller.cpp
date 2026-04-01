#include "appcontroller.h"
#include <QDebug>
#include <qdatetime.h>

AppController::AppController(QObject *parent) : QObject(parent)
{
    // Instanciar Controladores secundarios
    estructurasController = new EstructurasController();
    fileController = new FileController();

    // Instanciar la Vista Principal
    vistaSistema = new PantallaSistema();
    vistaSistema->setAppController(this);

    // Inyección de dependencias al ViewController con las estructuras y las QGraphicsViews
    viewController = new ViewController(
        estructurasController->getUnorderedList(),
        estructurasController->getListaOrdenada(),
        estructurasController->getArbolB(),
        estructurasController->getArbolBPlus(),
        estructurasController->getArbolAVL(),
        vistaSistema->getViewListaNoOrdenada(),
        vistaSistema->getViewListaOrdenada(),
        vistaSistema->getViewArbolB(),
        vistaSistema->getViewArbolBPlus(),
        vistaSistema->getViewArbolAVL());

    connect(vistaSistema, &PantallaSistema::archivoCSVSeleccionado,
            this, &AppController::cargarArchivoCSV);

    // Conectar actualización de estructuras con viewController para renderizar
    connect(estructurasController, &EstructurasController::etructurasActualizadas,
            viewController, &ViewController::actualizarVista);
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
    estructurasController->agregarProducto(
        nombre.toStdString(),
        codigoBarra.toStdString(),
        categoria.toStdString(),
        fechaCaducidad.toString("yyyy-MM-dd").toStdString(),
        marca.toStdString(),
        precio,
        stock);
}

void AppController::cargarArchivoCSV(const QString &ruta)
{
    const QList<Product> productos = fileController->cargarCSV(ruta);
    qDebug() << "CSV cargado:" << ruta << "Productos válidos:" << productos.size();

    for (const Product &p : productos)
    {
        estructurasController->agregarProducto(
            p.getName(),
            p.getBarcode(),
            p.getCategory(),
            p.getExpiryDate(),
            p.getBrand(),
            p.getPrice(),
            p.getStock(),
            false); // No emitir señal por cada producto
    }
    
    // Actualizar arboles de una sola vez XD
    estructurasController->actualizarVistas();
    
    // Pasar los datos cargados a la tabla qlera
    vistaSistema->mostrarDatosCSV(productos);
}
