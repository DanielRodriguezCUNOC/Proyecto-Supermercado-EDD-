#ifndef LISTAENLAZADAORDENADA_H
#define LISTAENLAZADAORDENADA_H
#include "model/entidades/nodo.h"

class ListaEnlazadaOrdenada
{
private:
    Nodo *cabeza;
    Nodo *cola;
    int size;

public:
    ListaEnlazadaOrdenada();
    Nodo *getCabeza() const;
    Nodo *getCola() const;
    Nodo *getAt(int position) const;
    void insertar(Product *product);
    void eliminar(Product *product);
    int getSize() const;
    bool isEmpty() const;
};

#endif // LISTAENLAZADAORDENADA_H
