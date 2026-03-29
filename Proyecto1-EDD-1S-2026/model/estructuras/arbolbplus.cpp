// Implementación propia sin STL (salvo string)
#include "arbolbplus.h"
#include <sstream>

BPlusNode::BPlusNode(int grado, bool hoja) : esHoja(hoja), numClaves(0), numHijos(0), productos(nullptr), siguienteHoja(nullptr)
{
  claves = new std::string[grado];
  hijos = new BPlusNode *[grado + 1];
  for (int i = 0; i < grado + 1; ++i)
    hijos[i] = nullptr;
}

BPlusNode::~BPlusNode()
{
  delete[] claves;
  for (int i = 0; i < numHijos; ++i)
    delete hijos[i];
  delete[] hijos;

  // Liberar lista de productos
  Nodo *actual = productos;
  while (actual)
  {
    Nodo *sig = actual->getNext();
    delete actual;
    actual = sig;
  }
}

ArbolBPlus::ArbolBPlus(int grado) : grado(grado), categorias(nullptr) {}

ArbolBPlus::~ArbolBPlus()
{
  liberarCategorias();
}

CategoriaNodo *ArbolBPlus::buscarCategoria(const std::string &nombre) const
{
  CategoriaNodo *actual = categorias;
  while (actual)
  {
    if (actual->nombre == nombre)
      return actual;
    actual = actual->siguiente;
  }
  return nullptr;
}

CategoriaNodo *ArbolBPlus::crearOCapturarCategoria(const std::string &nombre)
{
  CategoriaNodo *cat = buscarCategoria(nombre);
  if (cat)
    return cat;
  cat = new CategoriaNodo(nombre);
  cat->siguiente = categorias;
  categorias = cat;
  return cat;
}

void ArbolBPlus::liberarCategorias()
{
  CategoriaNodo *actual = categorias;
  while (actual)
  {
    CategoriaNodo *sig = actual->siguiente;
    if (actual->raiz)
      delete actual->raiz;
    delete actual;
    actual = sig;
  }
  categorias = nullptr;
}

// Inserción atómica por categoría
bool ArbolBPlus::insertarProducto(const Product &producto, std::string &errorRollback)
{
  CategoriaNodo *cat = crearOCapturarCategoria(producto.getCategory());
  if (!cat->raiz)
    cat->raiz = new BPlusNode(grado, true);

  // Inserción en hoja (simulación, sin rebalanceo)
  Nodo *nuevo = new Nodo(new Product(producto));
  nuevo->setNext(cat->raiz->productos);
  if (cat->raiz->productos)
    cat->raiz->productos->setPrev(nuevo);
  cat->raiz->productos = nuevo;
  cat->raiz->numClaves++;

  // Aquí iría la lógica real de inserción y rebalanceo
  return true;
}

// Buscar productos por categoría
void ArbolBPlus::buscarPorCategoria(const std::string &categoria, Nodo *&resultado) const
{
  resultado = nullptr;
  CategoriaNodo *cat = buscarCategoria(categoria);
  if (!cat || !cat->raiz)
    return;

  // Copiar la lista de productos de la hoja
  Nodo *actual = cat->raiz->productos;
  Nodo *prev = nullptr;
  while (actual)
  {
    Nodo *copia = new Nodo(new Product(*actual->getValue()));
    if (!resultado)
      resultado = copia;
    if (prev)
      prev->setNext(copia);
    copia->setPrev(prev);
    prev = copia;
    actual = actual->getNext();
  }
}

// Eliminar producto (por código de barra)
bool ArbolBPlus::eliminarProducto(const std::string &codigoBarra, std::string &errorRollback)
{
  bool eliminado = false;
  CategoriaNodo *cat = categorias;
  while (cat)
  {
    if (cat->raiz)
    {
      Nodo *actual = cat->raiz->productos;
      Nodo *prev = nullptr;
      while (actual)
      {
        if (actual->getValue()->getBarcode() == codigoBarra)
        {
          if (prev)
            prev->setNext(actual->getNext());
          else
            cat->raiz->productos = actual->getNext();

          if (actual->getNext())
            actual->getNext()->setPrev(prev);

          delete actual;
          cat->raiz->numClaves--;
          eliminado = true;
          break;
        }
        prev = actual;
        actual = actual->getNext();
      }
    }
    cat = cat->siguiente;
  }

  if (!eliminado)
  {
    errorRollback = "Producto no encontrado para eliminar.";
    return false;
  }
  return true;
}

// Exportar a CSV
std::string ArbolBPlus::exportarCSV() const
{
  std::ostringstream oss;
  oss << "Nombre,CodigoBarra,Categoria,FechaCaducidad,Marca,Precio,Stock\n";
  CategoriaNodo *cat = categorias;
  while (cat)
  {
    if (cat->raiz)
    {
      Nodo *actual = cat->raiz->productos;
      while (actual)
      {
        Product *p = actual->getValue();
        oss << p->getName() << ","
            << p->getBarcode() << ","
            << p->getCategory() << ","
            << p->getExpiryDate() << ","
            << p->getBrand() << ","
            << p->getPrice() << ","
            << p->getStock() << "\n";
        actual = actual->getNext();
      }
    }
    cat = cat->siguiente;
  }
  return oss.str();
}

// Importar desde CSV (implementación básica, no robusta)
bool ArbolBPlus::importarCSV(const std::string &csvData, std::string &errorMsg)
{
  // Implementación pendiente
  errorMsg = "No implementado";
  return false;
}

void ArbolBPlus::rollbackInsercion(CategoriaNodo *categoria, const std::string &codigoBarra)
{
  if (!categoria || !categoria->raiz)
    return;

  Nodo *actual = categoria->raiz->productos;
  Nodo *prev = nullptr;
  while (actual)
  {
    if (actual->getValue()->getBarcode() == codigoBarra)
    {
      if (prev)
        prev->setNext(actual->getNext());
      else
        categoria->raiz->productos = actual->getNext();

      if (actual->getNext())
        actual->getNext()->setPrev(prev);

      delete actual;
      categoria->raiz->numClaves--;
      break;
    }
    prev = actual;
    actual = actual->getNext();
  }
}

void ArbolBPlus::rollbackEliminacion(CategoriaNodo *categoria, Product *producto)
{
  if (!categoria || !categoria->raiz)
    return;

  Nodo *nuevo = new Nodo(producto);
  nuevo->setNext(categoria->raiz->productos);
  if (categoria->raiz->productos)
    categoria->raiz->productos->setPrev(nuevo);
  categoria->raiz->productos = nuevo;
  categoria->raiz->numClaves++;
}