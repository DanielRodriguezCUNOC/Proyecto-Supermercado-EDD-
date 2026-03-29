#include "nodo.h"

Nodo::Nodo() {}
Nodo::Nodo(Product *product) : product(product), next(nullptr), prev(nullptr) {}

Product *Nodo::getValue() const
{
  return product;
}

Nodo *Nodo::getNext() const
{
  return next;
}

Nodo *Nodo::getPrev() const
{
  return prev;
}

void Nodo::setValue(Product *product)
{
  this->product = product;
}

void Nodo::setNext(Nodo *next)
{
  this->next = next;
}

void Nodo::setPrev(Nodo *prev)
{
  this->prev = prev;
}
