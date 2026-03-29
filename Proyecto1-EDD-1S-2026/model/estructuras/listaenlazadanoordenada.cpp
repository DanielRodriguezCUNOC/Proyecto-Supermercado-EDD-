#include "listaenlazadanoordenada.h"

ListaEnlazadaNoOrdenada::ListaEnlazadaNoOrdenada() {}

void ListaEnlazadaNoOrdenada::insertar(Product *product)
{
  Nodo *nuevoProducto = new Nodo(product);
  if (this->isEmpty())
  {
    this->cabeza = nuevoProducto;
    this->cola = nuevoProducto;
  }
  else
  {
    nuevoProducto->setNext(this->cabeza);
    this->cabeza = nuevoProducto;
  }
  size++;
}

void ListaEnlazadaNoOrdenada::eliminar(Product *product)
{
  if (this->isEmpty())
    return;

  Nodo *actual = this->cabeza;
  Nodo *anterior = nullptr;

  while (actual != nullptr)
  {
    if (actual->getValue() == product)
    {
      if (actual == this->cabeza)
      {
        this->cabeza = actual->getNext();
        if (actual == this->cola)
        {
          this->cola = nullptr;
        }
      }
      else
      {
        anterior->setNext(actual->getNext());
        if (actual == this->cola)
        {
          this->cola = anterior;
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

Nodo *ListaEnlazadaNoOrdenada::getCabeza() const
{
  return this->cabeza;
}

Nodo *ListaEnlazadaNoOrdenada::getCola() const
{
  return this->cola;
}

Nodo *ListaEnlazadaNoOrdenada::getAt(int position) const
{
  if (this->isEmpty())
    return nullptr;

  if (this->getSize() <= position)
    return nullptr;

  Nodo *current = this->cabeza;
  int currentPosition = 1;

  while (currentPosition < position && current != nullptr)
  {
    current = current->getNext();
    currentPosition++;
  }

  return current;
}

int ListaEnlazadaNoOrdenada::getSize() const
{
  if (this->isEmpty())
    return 0;

  return size;
}

bool ListaEnlazadaNoOrdenada::isEmpty() const
{
  return this->cabeza == nullptr;
}
