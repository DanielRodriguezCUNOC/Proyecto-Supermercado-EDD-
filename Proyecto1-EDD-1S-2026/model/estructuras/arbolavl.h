#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "../entidades/product.h"
#include <string>

class NodoAVL {
public:
    Product producto;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;

    NodoAVL(Product p);
};

class ArbolAVL {
private:
    NodoAVL* raiz;

    int obtenerAltura(NodoAVL* N);
    int max(int a, int b);
    NodoAVL* rotacionDerecha(NodoAVL* y);
    NodoAVL* rotacionIzquierda(NodoAVL* x);
    int obtenerBalance(NodoAVL* N);
    
    NodoAVL* insertarRec(NodoAVL* nodo, const Product& producto);
    NodoAVL* nodoValorMinimo(NodoAVL* nodo);
    NodoAVL* eliminarRec(NodoAVL* root, const std::string& barcode);
    
    NodoAVL* buscarRec(NodoAVL* root, const std::string& nombre) const;
    void inOrderRec(NodoAVL* root) const;
    void destruirRec(NodoAVL* nodo);

public:
    ArbolAVL();
    ~ArbolAVL();

    void insertar(const Product& producto);
    void eliminar(const std::string& barcode);
    
    // Búsqueda binaria por nombre
    Product* buscarPorNombre(const std::string& nombre) const;
    
    // Imprimir ordenado por nombre
    void listarPorNombre() const;

    std::string generarDOT() const;
};

#endif // ARBOLAVL_H
