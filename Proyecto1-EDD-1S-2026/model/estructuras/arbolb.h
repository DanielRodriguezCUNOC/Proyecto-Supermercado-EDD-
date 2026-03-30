#ifndef ARBOLB_H
#define ARBOLB_H

#include <string>

class Product;

// Nodo del Árbol B específico para Product
class NodoB
{
public:
    Product* claves; // Arreglo dinámico de claves (productos)
    NodoB** hijos;   // Arreglo dinámico de punteros a hijos
    int n;           // Número actual de claves
    bool hoja;       // Verdadero si es hoja
    int t;           // Grado mínimo

    NodoB(int _t, bool _hoja);
    ~NodoB();

    void insertarNoLleno(const Product &k);
    void dividirHijo(int i, NodoB *y);
    void recorrer();

    // Métodos para eliminación
    int buscarClave(const std::string &codigo);
    void eliminar(const std::string &codigo);
    void removerDeHoja(int idx);
    void removerDeNoHoja(int idx);
    Product obtenerPredecesor(int idx);
    Product obtenerSucesor(int idx);
    void llenar(int idx);
    void pedirPrestadoAnterior(int idx);
    void pedirPrestadoSiguiente(int idx);
    void fusionar(int idx);

    // Para la búsqueda recursiva
    void buscarPorCaducidadRec(const std::string &desde, const std::string &hasta, class ListaResultados* resultados);
};

// Estructura simple para almacenar resultados de búsqueda sin usar vector
class NodoResultadoList {
public:
    Product producto;
    NodoResultadoList* next;
    NodoResultadoList(const Product& p) : producto(p), next(nullptr) {}
};

class ListaResultados {
public:
    NodoResultadoList* cabeza;
    NodoResultadoList* cola;
    int size;

    ListaResultados() : cabeza(nullptr), cola(nullptr), size(0) {}
    ~ListaResultados() {
        NodoResultadoList* actual = cabeza;
        while(actual) {
            NodoResultadoList* aux = actual->next;
            delete actual;
            actual = aux;
        }
    }
    void agregar(const Product& p) {
        NodoResultadoList* n = new NodoResultadoList(p);
        if(!cabeza) cabeza = cola = n;
        else {
            cola->next = n;
            cola = n;
        }
        size++;
    }
};

class ArbolB
{
public:
    NodoB *raiz;
    int t;

    ArbolB(int _t);
    ~ArbolB();

    void insertar(const Product &k);
    void imprimir();
    std::string generarDOT() const;
    
    // Retorna una lista con los productos que cumplen el rango de caducidad
    ListaResultados* buscarPorCaducidad(const std::string &desde, const std::string &hasta);

    void eliminarPorCodigo(const std::string &codigo);

private:
    void destruirRec(NodoB* nodo);
};

#endif // ARBOLB_H
