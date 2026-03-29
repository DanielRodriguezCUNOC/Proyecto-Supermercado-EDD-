#ifndef LISTAENLAZADANOORDENADA_H
#define LISTAENLAZADANOORDENADA_H
#include "model/entidades/nodo.h"

class ListaEnlazadaNoOrdenada
{
private:
    Nodo *cabeza;
    Nodo *cola;
    int size;

public:
    ListaEnlazadaNoOrdenada();
    Nodo *getCabeza() const;
    Nodo *getCola() const;
    Nodo *getAt(int position) const;
    void insertar(Product *product);
    void eliminar(Product *product);
    int getSize() const;
    bool isEmpty() const;
};

#endif // LISTAENLAZADANOORDENADA_H
