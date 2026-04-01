#include "controller/estructurascontroller.h"
#include <QDebug>

EstructurasController::EstructurasController()
{
  // Inicializar todas las estructuras de datos
  unorderedList = new ListaEnlazadaNoOrdenada();
  listaOrdenada = new ListaEnlazadaOrdenada();
  arbolB = new ArbolB(5);         // t = 5 (Grado 10)
  arbolBPlus = new ArbolBPlus(4); // Grado = 4 
  arbolAVL = new ArbolAVL();
}

EstructurasController::EstructurasController(
    ListaEnlazadaNoOrdenada *unorderedList,
    ListaEnlazadaOrdenada *listaOrdenada,
    ArbolB *arbolB,
    ArbolBPlus *arbolBPlus,
    ArbolAVL *arbolAVL)
    : unorderedList(unorderedList),
      listaOrdenada(listaOrdenada),
      arbolB(arbolB),
      arbolBPlus(arbolBPlus),
      arbolAVL(arbolAVL)
{
}

void EstructurasController::agregarProducto(std::string name,
                                            std::string barcode,
                                            std::string category,
                                            std::string expiry_date,
                                            std::string brand,
                                            double price,
                                            int stock,
                                            bool emitirSenal)
{
  Product producto(name, barcode, category, expiry_date, brand, price, stock);

  // Cada lista recibe su propia copia dinámica para evitar aliasing y fugas en rutas nulas.
  if (unorderedList)
  {
    Product *productoNoOrdenado = new Product(producto);
    unorderedList->insertar(productoNoOrdenado);
  }

  if (listaOrdenada)
  {
    Product *productoOrdenado = new Product(producto);
    listaOrdenada->insertar(productoOrdenado);
  }

  if (arbolAVL)
  {
    arbolAVL->insertar(producto);
  }

  if (arbolB)
  {
    arbolB->insertar(producto);
  }

  if (arbolBPlus)
  {
    std::string errorRollback;
    bool insercionExitosa = arbolBPlus->insertarProducto(producto, errorRollback);
    if (!insercionExitosa)
    {
      qDebug() << "Error al insertar en ArbolBPlus:" << QString::fromStdString(errorRollback);
    }
  }

  // Emitir señal para notificar que las estructuras fueron actualizadas si emitirSenal es true
  if (emitirSenal) {
      emit etructurasActualizadas();
  }
}

void EstructurasController::actualizarVistas()
{
    emit etructurasActualizadas();
}

void EstructurasController::eliminarProducto(std::string barcode)
{
}
