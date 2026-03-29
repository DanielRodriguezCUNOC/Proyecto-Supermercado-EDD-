#ifndef ARBOLB_H
#define ARBOLB_H

#include <vector>
#include <iostream>

template <typename T>
class NodoB
{
public:
    std::vector<T> claves;
    std::vector<NodoB<T> *> hijos;
    bool hoja;
    int t; // Grado mínimo

    NodoB(int _t, bool _hoja) : t(_t), hoja(_hoja) {}
};

template <typename T>
class ArbolB
{
public:
    NodoB<T> *raiz;
    int t;

    ArbolB(int _t);
    void insertar(const T &k);
    void imprimir();

    // Buscar productos por rango de caducidad (solo para T=Product)
    std::vector<T> buscarPorCaducidad(const std::string& desde, const std::string& hasta);

    // Eliminar producto por código de barra (solo para T=Product)
    void eliminarPorCodigo(const std::string& codigo);

private:
    void insertarNoLleno(NodoB<T> *nodo, const T &k);
    void dividirHijo(NodoB<T> *padre, int i, NodoB<T> *hijo);
    void imprimirRec(NodoB<T> *nodo, int nivel);
    void buscarPorCaducidadRec(NodoB<T>* nodo, const std::string& desde, const std::string& hasta, std::vector<T>& resultado);
    void eliminarRec(NodoB<T>* nodo, const std::string& codigo);
    int encontrarClave(NodoB<T>* nodo, const std::string& codigo);
};

#endif // ARBOLB_H
