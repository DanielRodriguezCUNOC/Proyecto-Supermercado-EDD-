void ListaEnlazadaOrdenada::eliminar(Product *product)
{
  if (isEmpty()) return;
  Nodo *actual = cabeza;
  Nodo *anterior = nullptr;
  while (actual != nullptr) {
    if (actual->getValue() == product) {
      if (actual == cabeza) {
        cabeza = actual->getNext();
        if (actual == cola) {
          cola = nullptr;
        }
      } else {
        anterior->setNext(actual->getNext());
        if (actual == cola) {
          cola = anterior;
        }
      }
      delete actual;
      size--;
      return;
    }
    anterior = actual;
    actual = actual->getNext();
  }
}
#include "listaenlazadaordenada.h"

ListaEnlazadaOrdenada::ListaEnlazadaOrdenada() : cabeza(nullptr), cola(nullptr), size(0) {}

void ListaEnlazadaOrdenada::insertar(Product *product)
{
    Nodo *nuevo = new Nodo(product);
    if (isEmpty())
    {
        cabeza = nuevo;
        cola = nuevo;
    }
    else
    {
        cola->setNext(nuevo);
        cola = nuevo;
    }
    size++;
}

Nodo *ListaEnlazadaOrdenada::getCabeza() const
{
  return cabeza;
}

Nodo *ListaEnlazadaOrdenada::getCola() const
{
  return cola;
}

Nodo *ListaEnlazadaOrdenada::getAt(int position) const
{
  if (isEmpty() || position < 0 || position >= size)
    return nullptr;
  Nodo *current = cabeza;
  int currentPosition = 0;
  while (currentPosition < position && current != nullptr)
  {
    current = current->getNext();
    currentPosition++;
  }
  return current;
}

int ListaEnlazadaOrdenada::getSize() const
{
  return size;
}

bool ListaEnlazadaOrdenada::isEmpty() const
{
  return cabeza == nullptr;
}
