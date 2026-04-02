#include "controller/estructurascontroller.h"
#include <QDebug>
#include <chrono>

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

  qDebug() << "--- Midiendo tiempos de inserción para:" << QString::fromStdString(name) << "---";

  long tUL = 0, tOL = 0, tAVL = 0, tB = 0, tBP = 0;

  // Lista No Ordenada
  if (unorderedList)
  {
    auto start = std::chrono::high_resolution_clock::now();
    Product *p = new Product(producto);
    unorderedList->insertar(p);
    auto end = std::chrono::high_resolution_clock::now();
    tUL = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    qDebug() << "[Lista No Ordenada]:" << tUL << "µs";
  }

  // Lista Ordenada
  if (listaOrdenada)
  {
    auto start = std::chrono::high_resolution_clock::now();
    Product *p = new Product(producto);
    listaOrdenada->insertar(p);
    auto end = std::chrono::high_resolution_clock::now();
    tOL = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    qDebug() << "[Lista Ordenada]:" << tOL << "µs";
  }

  // Arbol AVL
  if (arbolAVL)
  {
    auto start = std::chrono::high_resolution_clock::now();
    arbolAVL->insertar(producto);
    auto end = std::chrono::high_resolution_clock::now();
    tAVL = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    qDebug() << "[Arbol AVL]:" << tAVL << "µs";
  }

  // Arbol B
  if (arbolB)
  {
    auto start = std::chrono::high_resolution_clock::now();
    arbolB->insertar(producto);
    auto end = std::chrono::high_resolution_clock::now();
    tB = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    qDebug() << "[Arbol B]:" << tB << "µs";
  }

  // Arbol B+
  if (arbolBPlus)
  {
    auto start = std::chrono::high_resolution_clock::now();
    std::string errorRollback;
    bool insercionExitosa = arbolBPlus->insertarProducto(producto, errorRollback);
    auto end = std::chrono::high_resolution_clock::now();
    tBP = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    if (!insercionExitosa) {
      qDebug() << "[Arbol B+]: ERROR -" << QString::fromStdString(errorRollback);
    } else {
      qDebug() << "[Arbol B+]:" << tBP << "µs";
    }
  }

  qDebug() << "---------------------------------------------------------";

  if (emitirSenal) {
      emit tiemposCalculados(tUL, tOL, tB, tBP, tAVL);
      emit etructurasActualizadas();
  }
}

void EstructurasController::actualizarVistas()
{
    emit etructurasActualizadas();
}

void EstructurasController::eliminarProducto(std::string barcode)
{
  qDebug() << "--- Midiendo tiempos de eliminación para:" << QString::fromStdString(barcode) << "---";

  long tUL = 0, tOL = 0, tAVL = 0, tB = 0, tBP = 0;

  if (unorderedList)
  {
    auto start = std::chrono::high_resolution_clock::now();
    unorderedList->eliminar(barcode);
    auto end = std::chrono::high_resolution_clock::now();
    tUL = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    qDebug() << "[Lista No Ordenada]:" << tUL << "µs";
  }

  if (listaOrdenada)
  {
    auto start = std::chrono::high_resolution_clock::now();
    listaOrdenada->eliminar(barcode);
    auto end = std::chrono::high_resolution_clock::now();
    tOL = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    qDebug() << "[Lista Ordenada]:" << tOL << "µs";
  }

  if (arbolAVL)
  {
    auto start = std::chrono::high_resolution_clock::now();
    arbolAVL->eliminar(barcode);
    auto end = std::chrono::high_resolution_clock::now();
    tAVL = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    qDebug() << "[Arbol AVL]:" << tAVL << "µs";
  }

  if (arbolB)
  {
    auto start = std::chrono::high_resolution_clock::now();
    arbolB->eliminarPorCodigo(barcode);
    auto end = std::chrono::high_resolution_clock::now();
    tB = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    qDebug() << "[Arbol B]:" << tB << "µs";
  }

  if (arbolBPlus)
  {
    auto start = std::chrono::high_resolution_clock::now();
    std::string error;
    bool exito = arbolBPlus->eliminarProducto(barcode, error);
    auto end = std::chrono::high_resolution_clock::now();
    tBP = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    if (!exito) {
      qDebug() << "[Arbol B+]: ERROR -" << QString::fromStdString(error);
    } else {
      qDebug() << "[Arbol B+]:" << tBP << "µs";
    }
  }

  qDebug() << "---------------------------------------------------------";

  emit tiemposCalculados(tUL, tOL, tB, tBP, tAVL);
  emit etructurasActualizadas();
}
