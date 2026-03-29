#include "arbolavl.h"
#include <iostream>

using namespace std;

NodoAVL::NodoAVL(Product p) : producto(p), izq(nullptr), der(nullptr), altura(1) {}

ArbolAVL::ArbolAVL() : raiz(nullptr) {}

ArbolAVL::~ArbolAVL() {
    destruirRec(raiz);
}

void ArbolAVL::destruirRec(NodoAVL* nodo) {
    if (nodo != nullptr) {
        destruirRec(nodo->izq);
        destruirRec(nodo->der);
        delete nodo;
    }
}

int ArbolAVL::obtenerAltura(NodoAVL* N) {
    if (N == nullptr) return 0;
    return N->altura;
}

int ArbolAVL::max(int a, int b) {
    return (a > b) ? a : b;
}

NodoAVL* ArbolAVL::rotacionDerecha(NodoAVL* y) {
    NodoAVL* x = y->izq;
    NodoAVL* T2 = x->der;

    // Realizar rotación
    x->der = y;
    y->izq = T2;

    // Actualizar alturas
    y->altura = max(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
    x->altura = max(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;

    return x;
}

NodoAVL* ArbolAVL::rotacionIzquierda(NodoAVL* x) {
    NodoAVL* y = x->der;
    NodoAVL* T2 = y->izq;

    // Realizar rotación
    y->izq = x;
    x->der = T2;

    // Actualizar alturas
    x->altura = max(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
    y->altura = max(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;

    return y; // Nueva raíz
}

int ArbolAVL::obtenerBalance(NodoAVL* N) {
    if (N == nullptr) return 0;
    return obtenerAltura(N->izq) - obtenerAltura(N->der);
}

void ArbolAVL::insertar(const Product& producto) {
    raiz = insertarRec(raiz, producto);
}

NodoAVL* ArbolAVL::insertarRec(NodoAVL* nodo, const Product& producto) {
    // 1. Inserción normal de BST guiada por el NOMBRE del producto
    if (nodo == nullptr)
        return new NodoAVL(producto);

    if (producto.getName() < nodo->producto.getName())
        nodo->izq = insertarRec(nodo->izq, producto);
    else if (producto.getName() > nodo->producto.getName())
        nodo->der = insertarRec(nodo->der, producto);
    else // Si tienen el mismo nombre, comparamos por código de barras para no perder productos con igual nombre
    {
        if (producto.getBarcode() < nodo->producto.getBarcode())
            nodo->izq = insertarRec(nodo->izq, producto);
        else if (producto.getBarcode() > nodo->producto.getBarcode())
            nodo->der = insertarRec(nodo->der, producto);
        else 
            return nodo; // Duplicado exacto (no se permite inserción)
    }

    // 2. Actualizar la altura del ancestro
    nodo->altura = 1 + max(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

    // 3. Obtener el factor de balance
    int balance = obtenerBalance(nodo);

    // Si el nodo se desbalancea, hay 4 casos:

    // Izquierda Izquierda
    if (balance > 1 && producto.getName() <= nodo->izq->producto.getName())
        return rotacionDerecha(nodo);

    // Derecha Derecha
    if (balance < -1 && producto.getName() >= nodo->der->producto.getName())
        return rotacionIzquierda(nodo);

    // Izquierda Derecha
    if (balance > 1 && producto.getName() > nodo->izq->producto.getName()) {
        nodo->izq = rotacionIzquierda(nodo->izq);
        return rotacionDerecha(nodo);
    }

    // Derecha Izquierda
    if (balance < -1 && producto.getName() < nodo->der->producto.getName()) {
        nodo->der = rotacionDerecha(nodo->der);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

NodoAVL* ArbolAVL::nodoValorMinimo(NodoAVL* nodo) {
    NodoAVL* actual = nodo;
    while (actual->izq != nullptr)
        actual = actual->izq;
    return actual;
}

void ArbolAVL::eliminar(const std::string& barcode) {
    // Nota: Como la clave principal es nombre pero necesitamos borrar por código de barra,
    // podríamos necesitar un borrado adaptado si se desea código $O(\log n)$, 
    // pero en este caso el barcode requiere buscar. Como no sabemos el nombre, 
    // asumiremos una búsqueda general si se envía un código (aunque idealmente la app lo mande con el producto completo)
    // Para adaptarlo a lo básico:
    raiz = eliminarRec(raiz, barcode); // Borrado simple por código, necesita recorrido adaptado si es árbol ordenado por nombre
    // OJO: Este borrado por "código de barras" que propongo busca el código en todo el árbol 
    // ya que el árbol AVL está balanceado por NOMBRE.
}

NodoAVL* ArbolAVL::eliminarRec(NodoAVL* root, const std::string& barcode) {
    if (root == nullptr)
        return root;

    // Dado que el AVL está ordenado por NOMBRE, buscar y borrar por código de barra es complejo.
    // Buscamos en ambos lados como pre-order:
    if (root->producto.getBarcode() != barcode) {
        NodoAVL* res = nullptr;
        // Tratamos de buscar de un lado
        if ((res = eliminarRec(root->izq, barcode)) != root->izq) {
            root->izq = res;
        } else if ((res = eliminarRec(root->der, barcode)) != root->der) {
            root->der = res;
        } else {
            return root; // No encontrado aquí
        }
    } else {
        // Encontramos el nodo
        if ((root->izq == nullptr) || (root->der == nullptr)) {
            NodoAVL* temp = root->izq ? root->izq : root->der;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp; // copio contenido 
            }
            delete temp;
        } else {
            // Nodo con dos hijos, tomar min del derecho
            NodoAVL* temp = nodoValorMinimo(root->der);
            root->producto = temp->producto;
            root->der = eliminarRec(root->der, temp->producto.getBarcode());
        }
    }

    // Si el árbol tenía solo un nodo
    if (root == nullptr)
        return root;

    // Actualizar altura
    root->altura = 1 + max(obtenerAltura(root->izq), obtenerAltura(root->der));

    // Obtener balance
    int balance = obtenerBalance(root);

    // Casos de desbalanceo
    if (balance > 1 && obtenerBalance(root->izq) >= 0)
        return rotacionDerecha(root);

    if (balance > 1 && obtenerBalance(root->izq) < 0) {
        root->izq = rotacionIzquierda(root->izq);
        return rotacionDerecha(root);
    }

    if (balance < -1 && obtenerBalance(root->der) <= 0)
        return rotacionIzquierda(root);

    if (balance < -1 && obtenerBalance(root->der) > 0) {
        root->der = rotacionDerecha(root->der);
        return rotacionIzquierda(root);
    }

    return root;
}

Product* ArbolAVL::buscarPorNombre(const std::string& nombre) const {
    NodoAVL* resultado = buscarRec(raiz, nombre);
    if (resultado) return &(resultado->producto);
    return nullptr;
}

NodoAVL* ArbolAVL::buscarRec(NodoAVL* root, const std::string& nombre) const {
    if (root == nullptr || root->producto.getName() == nombre)
        return root;

    // Búsqueda binaria
    if (root->producto.getName() < nombre)
        return buscarRec(root->der, nombre);

    return buscarRec(root->izq, nombre);
}

void ArbolAVL::listarPorNombre() const {
    inOrderRec(raiz);
    cout << endl;
}

void ArbolAVL::inOrderRec(NodoAVL* root) const {
    if (root != nullptr) {
        inOrderRec(root->izq);
        cout << root->producto.getName() << " (" << root->producto.getBarcode() << ") - ";
        inOrderRec(root->der);
    }
}
