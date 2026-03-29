#ifndef ARBOLBPLUS_H
#define ARBOLBPLUS_H

#include <string>
#include "../entidades/product.h"
#include "../entidades/nodo.h"

// Nodo del Árbol B+
class BPlusNode
{
public:
    bool esHoja;
    int grado;
    int numClaves;
    std::string *claves;       // Categorías
    BPlusNode **hijos;         // Hijos (solo internos)
    Nodo **productos;          // Cabezas de lista de productos por categoría (solo hojas)
    BPlusNode *siguienteHoja;  // Puntero para recorrido secuencial

    BPlusNode(int _grado, bool _hoja);
    ~BPlusNode();
};

class ArbolBPlus
{
public:
    BPlusNode *raiz;
    int grado;

    ArbolBPlus(int _grado = 4);
    ~ArbolBPlus();

    bool insertarProducto(const Product &producto, std::string &errorRollback);
    void buscarPorCategoria(const std::string &categoria, Nodo *&resultado) const;
    bool eliminarProducto(const std::string &codigoBarra, std::string &errorRollback);
    std::string exportarCSV() const;

private:
    void destruirRec(BPlusNode *nodo);
    void insertarEnNodo(BPlusNode *nodo, const std::string &clave, Nodo *nuevoProducto);
    void dividirNodo(BPlusNode *padre, int index, BPlusNode *hijo);
    void insertarInternal(const std::string &clave, Nodo *nuevoProducto);
    BPlusNode* encontrarHoja(const std::string &clave) const;
};

#endif // ARBOLBPLUS_H
