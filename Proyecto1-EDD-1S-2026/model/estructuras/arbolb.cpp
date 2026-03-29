#include "arbolb.h"
#include <iostream>
using namespace std;

// Constructor
template <typename T>
ArbolB<T>::ArbolB(int _t)
{
  raiz = nullptr;
  t = _t;
}

// Insertar clave
template <typename T>
void ArbolB<T>::insertar(const T &k)
{
  if (!raiz)
  {
    raiz = new NodoB<T>(t, true);
    raiz->claves.push_back(k);
  }
  else
  {
    if ((int)raiz->claves.size() == 2 * t - 1)
    {
      NodoB<T> *s = new NodoB<T>(t, false);
      s->hijos.push_back(raiz);
      dividirHijo(s, 0, raiz);
      int i = 0;
      if (s->claves[0] < k)
        i++;
      insertarNoLleno(s->hijos[i], k);
      raiz = s;
    }
    else
    {
      insertarNoLleno(raiz, k);
    }
  }
}

// Insertar en nodo no lleno
template <typename T>
void ArbolB<T>::insertarNoLleno(NodoB<T> *nodo, const T &k)
{
  int i = nodo->claves.size() - 1;
  if (nodo->hoja)
  {
    nodo->claves.push_back(k);
    int j = nodo->claves.size() - 1;
    while (j > 0 && nodo->claves[j] < nodo->claves[j - 1])
    {
      std::swap(nodo->claves[j], nodo->claves[j - 1]);
      j--;
    }
  }
  else
  {
    while (i >= 0 && k < nodo->claves[i])
      i--;
    i++;
    if ((int)nodo->hijos[i]->claves.size() == 2 * t - 1)
    {
      dividirHijo(nodo, i, nodo->hijos[i]);
      if (k > nodo->claves[i])
        i++;
    }
    insertarNoLleno(nodo->hijos[i], k);
  }
}

// Dividir hijo
template <typename T>
void ArbolB<T>::dividirHijo(NodoB<T> *padre, int i, NodoB<T> *hijo)
{
  NodoB<T> *z = new NodoB<T>(t, hijo->hoja);
  for (int j = 0; j < t - 1; j++)

    // Buscar productos por rango de caducidad (solo para T=Product)
    template <typename T>
    std::vector<T> ArbolB<T>::buscarPorCaducidad(const std::string &desde, const std::string &hasta)
    {
      std::vector<T> resultado;
      buscarPorCaducidadRec(raiz, desde, hasta, resultado);
      return resultado;
    }

  template <typename T>
  void ArbolB<T>::buscarPorCaducidadRec(NodoB<T> * nodo, const std::string &desde, const std::string &hasta, std::vector<T> &resultado)
  {
    if (!nodo)
      return;
    for (size_t i = 0; i < nodo->claves.size(); ++i)
    {

      // Usar método miembro del producto
      if (nodo->claves[i].estaEnRangoCaducidad(desde, hasta))
      {
        resultado.push_back(nodo->claves[i]);
      }
      if (!nodo->hoja && i < nodo->hijos.size())
      {
        buscarPorCaducidadRec(nodo->hijos[i], desde, hasta, resultado);
      }
    }
    if (!nodo->hoja && nodo->hijos.size() > nodo->claves.size())
    {
      buscarPorCaducidadRec(nodo->hijos.back(), desde, hasta, resultado);
    }
  }

  // Eliminar producto por código de barra (solo para T=Product)
  template <typename T>
  void ArbolB<T>::eliminarPorCodigo(const std::string &codigo)
  {
    eliminarRec(raiz, codigo);
    // TODO: rebalanceo y manejo de nodos vacíos
  }

  template <typename T>
  void ArbolB<T>::eliminarRec(NodoB<T> * nodo, const std::string &codigo)
  {
    if (!nodo)
      return;
    int idx = encontrarClave(nodo, codigo);

    // Si la clave está en este nodo
    if (idx < (int)nodo->claves.size() && nodo->claves[idx].getBarcode() == codigo)
    {
      // Si es hoja, eliminar directamente
      if (nodo->hoja)
      {
        nodo->claves.erase(nodo->claves.begin() + idx);
      }
      else
      {
        // TODO: manejar eliminación en nodos internos (rebalanceo, merges, etc.)
      }
    }
    else
    {
      // Si no es hoja, buscar en el hijo adecuado
      if (nodo->hoja)
        return; // No encontrado
      eliminarRec(nodo->hijos[idx], codigo);
    }
  }

  template <typename T>
  int ArbolB<T>::encontrarClave(NodoB<T> * nodo, const std::string &codigo)
  {
    int idx = 0;
    while (idx < (int)nodo->claves.size() && nodo->claves[idx].getBarcode() < codigo)
    {
      idx++;
    }
    return idx;
  }
  z->claves.push_back(hijo->claves[j + t]);
  if (!hijo->hoja)
  {
    for (int j = 0; j < t; j++)
      z->hijos.push_back(hijo->hijos[j + t]);
  }
  hijo->claves.resize(t - 1);
  hijo->hijos.resize(hijo->hoja ? 0 : t);
  padre->hijos.insert(padre->hijos.begin() + i + 1, z);
  padre->claves.insert(padre->claves.begin() + i, hijo->claves[t - 1]);
}

// Imprimir árbol
template <typename T>
void ArbolB<T>::imprimir()
{
  imprimirRec(raiz, 0);
}

template <typename T>
void ArbolB<T>::imprimirRec(NodoB<T> *nodo, int nivel)
{
  if (!nodo)
    return;
  cout << string(nivel * 2, ' ');
  for (const auto &clave : nodo->claves)
    cout << clave << " ";
  cout << endl;
  for (auto hijo : nodo->hijos)
    imprimirRec(hijo, nivel + 1);
}
