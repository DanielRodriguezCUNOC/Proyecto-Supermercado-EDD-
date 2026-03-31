#include "listaenlazadaordenada.h"
#include <sstream>
void ListaEnlazadaOrdenada::eliminar(Product *product)
{
  if (isEmpty()) return;
  Nodo *actual = cabeza;
  
  while (actual != nullptr) {
    if (actual->getValue() == product) {
      if (actual == cabeza) {
        cabeza = actual->getNext();
        if (cabeza != nullptr) cabeza->setPrev(nullptr);
        else cola = nullptr;
      } else if (actual == cola) {
        cola = actual->getPrev();
        if (cola != nullptr) cola->setNext(nullptr);
        else cabeza = nullptr;
      } else {
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
        Nodo *actual = cabeza;
        // Ordenar por el nombre del producto (alfabéticamente)
        while (actual != nullptr && actual->getValue()->getName() < product->getName())
        {
            actual = actual->getNext();
        }

        if (actual == cabeza) // Insertar al inicio
        {
            nuevo->setNext(cabeza);
            cabeza->setPrev(nuevo);
            cabeza = nuevo;
        }
        else if (actual == nullptr) // Insertar al final
        {
            cola->setNext(nuevo);
            nuevo->setPrev(cola);
            cola = nuevo;
        }
        else // Insertar en medio
        {
            Nodo *anterior = actual->getPrev();
            anterior->setNext(nuevo);
            nuevo->setPrev(anterior);
            nuevo->setNext(actual);
            actual->setPrev(nuevo);
        }
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


std::string ListaEnlazadaOrdenada::generarDOT() const {
    std::stringstream ss;
    ss << "digraph G {\n";
    ss << "  rankdir=LR;\n";
    ss << "  node [shape=record, style=filled, fillcolor=\"#E8F5E9\", color=\"#2E7D32\"];\n";
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
