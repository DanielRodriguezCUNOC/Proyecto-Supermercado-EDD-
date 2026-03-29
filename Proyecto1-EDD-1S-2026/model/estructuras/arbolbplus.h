#ifndef ARBOLBPLUS_H
#define ARBOLBPLUS_H

#include <string>
#include "model/entidades/product.h"
#include "model/entidades/nodo.h"

// Nodo para lista enlazada de categorías
struct CategoriaNodo
{
    std::string nombre;
    struct BPlusNode *raiz;
    CategoriaNodo *siguiente;
    CategoriaNodo(const std::string &n) : nombre(n), raiz(nullptr), siguiente(nullptr) {}
};

// Nodo del árbol B+
struct BPlusNode
{
    bool esHoja;
    // arreglo dinámico de claves
    std::string *claves;
    int numClaves;
    // arreglo dinámico de hijos
    BPlusNode **hijos;
    int numHijos;
    // solo en hojas: lista doblemente enlazada de productos
    Nodo *productos;
    // para recorrido por hojas
    BPlusNode *siguienteHoja;

    BPlusNode(int grado, bool hoja);
    ~BPlusNode();
};

class ArbolBPlus
{
public:
    ArbolBPlus(int grado = 4);
    ~ArbolBPlus();

    // Inserción atómica por categoría
    bool insertarProducto(const Product &producto, std::string &errorRollback);

    // Buscar productos por categoría
    void buscarPorCategoria(const std::string &categoria, Nodo *&resultado) const;

    // Eliminar producto (por código de barra)
    bool eliminarProducto(const std::string &codigoBarra, std::string &errorRollback);

    // Exportar a CSV
    std::string exportarCSV() const;

    // Importar desde CSV
    bool importarCSV(const std::string &csvData, std::string &errorMsg);

private:
    int grado;
    CategoriaNodo *categorias;

    // Métodos para lógica interna
    CategoriaNodo *buscarCategoria(const std::string &nombre) const;
    CategoriaNodo *crearOCapturarCategoria(const std::string &nombre);
    void liberarCategorias();
    void rollbackInsercion(CategoriaNodo *categoria, const std::string &codigoBarra);
    void rollbackEliminacion(CategoriaNodo *categoria, Product *producto);

    // Métodos para inserción y rebalanceo
    BPlusNode *buscarHojaDestino(BPlusNode *raiz, const std::string &clave);
    void insertarEnHoja(BPlusNode *hoja, const std::string &clave, Product *producto);
    void dividirHoja(CategoriaNodo *cat, BPlusNode *hoja);
};

#endif // ARBOLBPLUS_H
