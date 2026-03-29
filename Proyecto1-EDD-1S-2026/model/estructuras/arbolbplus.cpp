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

// --- MÉTODOS AUXILIARES PARA INSERCIÓN Y REBALANCEO ---
BPlusNode *ArbolBPlus::buscarHojaDestino(BPlusNode *raiz, const std::string &clave)
{
  BPlusNode *actual = raiz;
  while (actual && !actual->esHoja)
  {
    int i = 0;
    while (i < actual->numClaves && clave >= actual->claves[i])
      i++;
    actual = actual->hijos[i];
  }
  return actual;
}

void ArbolBPlus::insertarEnHoja(BPlusNode *hoja, const std::string &clave, Product *producto)
{
  int i = hoja->numClaves - 1;
  while (i >= 0 && clave < hoja->claves[i])
  {
    hoja->claves[i + 1] = hoja->claves[i];
    i--;
  }
  hoja->claves[i + 1] = clave;
  hoja->numClaves++;
  // Insertar producto en la lista enlazada en orden
  Nodo *nuevo = new Nodo(producto);
  Nodo *actual = hoja->productos;
  Nodo *prev = nullptr;
  while (actual && actual->getValue()->getBarcode() < clave)
  {
    prev = actual;
    actual = actual->getNext();
  }
  nuevo->setNext(actual);
  if (actual)
    actual->setPrev(nuevo);
  nuevo->setPrev(prev);
  if (prev)
    prev->setNext(nuevo);
  else
    hoja->productos = nuevo;
}

void ArbolBPlus::dividirHoja(CategoriaNodo *cat, BPlusNode *hoja)
{
  int mitad = grado / 2;
  BPlusNode *nuevaHoja = new BPlusNode(grado, true);
  // Copiar la mitad superior de claves a la nueva hoja
  for (int i = mitad, j = 0; i < grado; ++i, ++j)
  {
    nuevaHoja->claves[j] = hoja->claves[i];
    nuevaHoja->numClaves++;
  }
  hoja->numClaves = mitad;
  // Copiar productos correspondientes
  Nodo *actual = hoja->productos;
  Nodo *prev = nullptr;
  int idx = 0;
  while (actual)
  {
    Nodo *sig = actual->getNext();
    if (idx >= mitad)
    {
      // Mover a nueva hoja
      if (!nuevaHoja->productos)
      {
        nuevaHoja->productos = actual;
        actual->setPrev(nullptr);
      }
      else
      {
        Nodo *ult = nuevaHoja->productos;
        while (ult->getNext())
          ult = ult->getNext();
        ult->setNext(actual);
        actual->setPrev(ult);
      }
      actual->setNext(nullptr);
    }
    else
    {
      prev = actual;
    }
    actual = sig;
    idx++;
  }
  if (prev)
    prev->setNext(nullptr);
  // Enlazar hojas
  nuevaHoja->siguienteHoja = hoja->siguienteHoja;
  hoja->siguienteHoja = nuevaHoja;
  // Promocionar clave mínima de la nueva hoja al padre
  std::string clavePromocionada = nuevaHoja->claves[0];
  // Si la hoja es raíz
  if (cat->raiz == hoja)
  {
    BPlusNode *nuevaRaiz = new BPlusNode(grado, false);
    nuevaRaiz->claves[0] = clavePromocionada;
    nuevaRaiz->numClaves = 1;
    nuevaRaiz->hijos[0] = hoja;
    nuevaRaiz->hijos[1] = nuevaHoja;
    nuevaRaiz->numHijos = 2;
    cat->raiz = nuevaRaiz;
  }
  else
  {
    // Propagar hacia arriba (implementación pendiente para nodos internos)
    // ...
  }
}

// Inserción atómica por categoría (con división de hoja)
bool ArbolBPlus::insertarProducto(const Product &producto, std::string &errorRollback)
{
  CategoriaNodo *cat = crearOCapturarCategoria(producto.getCategory());
  if (!cat->raiz)
    cat->raiz = new BPlusNode(grado, true);
  // Buscar hoja destino
  BPlusNode *hoja = buscarHojaDestino(cat->raiz, producto.getBarcode());
  // Validar unicidad
  for (int i = 0; i < hoja->numClaves; ++i)
  {
    if (hoja->claves[i] == producto.getBarcode())
    {
      errorRollback = "Clave duplicada";
      return false;
    }
  }

  // Insertar en hoja
  insertarEnHoja(hoja, producto.getBarcode(), new Product(producto));

  // Si la hoja se desborda, dividir
  if (hoja->numClaves == grado)
  {
    dividirHoja(cat, hoja);
  }
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