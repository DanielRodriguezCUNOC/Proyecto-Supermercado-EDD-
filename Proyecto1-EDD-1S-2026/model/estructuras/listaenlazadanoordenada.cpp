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
    this->cabeza->setPrev(nuevoProducto);
    this->cabeza = nuevoProducto;
  }
  size++;
}

void ListaEnlazadaNoOrdenada::eliminar(Product *product)
{
  if (this->isEmpty())
    return;

  Nodo *actual = this->cabeza;

  while (actual != nullptr)
  {
    if (actual->getValue() == product)
    {
      if (actual == this->cabeza)
      {
        this->cabeza = actual->getNext();
        if (this->cabeza != nullptr) this->cabeza->setPrev(nullptr);
        else this->cola = nullptr;
      }
      else if (actual == this->cola)
      {
        this->cola = actual->getPrev();
        if (this->cola != nullptr) this->cola->setNext(nullptr);
        else this->cabeza = nullptr;
      }
      else
      {
        actual->getPrev()->setNext(actual->getNext());
        actual->getNext()->setPrev(actual->getPrev());
      }
      delete actual;
      size--;
      return;
    }
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

#include <sstream>

std::string ListaEnlazadaNoOrdenada::generarDOT() const {
    std::stringstream ss;
    ss << "digraph G {\n";
    ss << "  rankdir=LR;\n";
    ss << "  node [shape=record, style=filled, fillcolor=\"#E3F2FD\", color=\"#1565C0\"];\n";
    Nodo* act = cabeza;
    int i = 0;
    while(act) {
        ss << "  node" << i << " [label=\"{ " << act->getValue()->getName() << " | " << act->getValue()->getBarcode() << " }\"];\n";
        if(i > 0) ss << "  node" << (i-1) << " -> node" << i << ";\n";
        act = act->getNext();
        i++;
    }
    ss << "}\n";
    return ss.str();
}
