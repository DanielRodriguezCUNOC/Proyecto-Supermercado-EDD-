#include "arbolbplus.h"
#include <sstream>

BPlusNode::BPlusNode(int _grado, bool _hoja) : esHoja(_hoja), grado(_grado), numClaves(0), siguienteHoja(nullptr)
{
    claves = new std::string[grado];
    hijos = new BPlusNode *[grado + 1];
    productos = new Nodo *[grado];

    for (int i = 0; i < grado + 1; ++i) hijos[i] = nullptr;
    for (int i = 0; i < grado; ++i) productos[i] = nullptr;
}

BPlusNode::~BPlusNode()
{
    if (esHoja) {
        for (int i = 0; i < numClaves; ++i) {
            Nodo *actual = productos[i];
            while (actual) {
                Nodo *sig = actual->getNext();
                delete actual;
                actual = sig;
            }
        }
    }
    delete[] claves;
    delete[] hijos;
    delete[] productos;
}

ArbolBPlus::ArbolBPlus(int _grado) : raiz(nullptr), grado(_grado) {}

ArbolBPlus::~ArbolBPlus()
{
    destruirRec(raiz);
}

void ArbolBPlus::destruirRec(BPlusNode *nodo)
{
    if (!nodo) return;
    if (!nodo->esHoja) {
        for (int i = 0; i <= nodo->numClaves; ++i) {
            destruirRec(nodo->hijos[i]);
        }
    }
    delete nodo;
}

BPlusNode* ArbolBPlus::encontrarHoja(const std::string &clave) const
{
    if (!raiz) return nullptr;
    BPlusNode *actual = raiz;
    while (!actual->esHoja) {
        int i = 0;
        while (i < actual->numClaves && clave >= actual->claves[i]) {
            i++;
        }
        actual = actual->hijos[i];
    }
    return actual;
}

bool ArbolBPlus::insertarProducto(const Product &producto, std::string &errorRollback)
{
    std::string cat = producto.getCategory();
    Nodo *nuevo = new Nodo(new Product(producto));

    if (!raiz) {
        raiz = new BPlusNode(grado, true);
        raiz->claves[0] = cat;
        raiz->productos[0] = nuevo;
        raiz->numClaves = 1;
        return true;
    }

    BPlusNode *hoja = encontrarHoja(cat);

    // Buscar si la categoría ya existe en la hoja
    for (int i = 0; i < hoja->numClaves; ++i) {
        if (hoja->claves[i] == cat) {
            // Unicidad de codigo de barras
            Nodo *actual = hoja->productos[i];
            while (actual) {
                if (actual->getValue()->getBarcode() == producto.getBarcode()) {
                    delete nuevo->getValue();
                    delete nuevo;
                    errorRollback = "Código de barras duplicado";
                    return false;
                }
                actual = actual->getNext();
            }
            // Agregamos al inicio de la lista
            nuevo->setNext(hoja->productos[i]);
            if (hoja->productos[i]) hoja->productos[i]->setPrev(nuevo);
            hoja->productos[i] = nuevo;
            return true;
        }
    }

    insertarInternal(cat, nuevo);
    return true;
}

void ArbolBPlus::insertarInternal(const std::string &clave, Nodo *nuevoProducto)
{
    if (raiz->numClaves == grado - 1) {
        BPlusNode *s = new BPlusNode(grado, false);
        s->hijos[0] = raiz;
        dividirNodo(s, 0, raiz);
        raiz = s;
    }
    
    BPlusNode *actual = raiz;
    while (!actual->esHoja) {
        int i = actual->numClaves - 1;
        while (i >= 0 && clave < actual->claves[i]) i--;
        i++;
        if (actual->hijos[i]->numClaves == grado - 1) {
            dividirNodo(actual, i, actual->hijos[i]);
            if (clave >= actual->claves[i]) i++;
        }
        actual = actual->hijos[i];
    }
    
    insertarEnNodo(actual, clave, nuevoProducto);
}

void ArbolBPlus::insertarEnNodo(BPlusNode *nodo, const std::string &clave, Nodo *nuevoProducto)
{
    int i = nodo->numClaves - 1;
    while (i >= 0 && clave < nodo->claves[i]) {
        nodo->claves[i + 1] = nodo->claves[i];
        if (nodo->esHoja) nodo->productos[i + 1] = nodo->productos[i];
        i--;
    }
    nodo->claves[i + 1] = clave;
    if (nodo->esHoja) nodo->productos[i + 1] = nuevoProducto;
    nodo->numClaves++;
}

void ArbolBPlus::dividirNodo(BPlusNode *padre, int index, BPlusNode *hijo)
{
    BPlusNode *z = new BPlusNode(hijo->grado, hijo->esHoja);
    int t = hijo->grado / 2;
    z->numClaves = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->claves[j] = hijo->claves[j + t];
        if (z->esHoja) z->productos[j] = hijo->productos[j + t];
    }
    if (!hijo->esHoja) {
        for (int j = 0; j < t; j++) z->hijos[j] = hijo->hijos[j + t];
    }

    hijo->numClaves = t - 1;

    for (int j = padre->numClaves; j >= index + 1; j--) padre->hijos[j + 1] = padre->hijos[j];
    padre->hijos[index + 1] = z;

    for (int j = padre->numClaves - 1; j >= index; j--) padre->claves[j + 1] = padre->claves[j];
    
    if (hijo->esHoja) {
        padre->claves[index] = z->claves[0];
        // Enlazar hojas
        z->siguienteHoja = hijo->siguienteHoja;
        hijo->siguienteHoja = z;
        // Restaurar la clave en la hoja z ya que B+ la conserva abajo
        z->numClaves++;
        for(int j = z->numClaves - 1; j > 0; j--) {
            z->claves[j] = z->claves[j-1];
            z->productos[j] = z->productos[j-1];
        }
        z->claves[0] = hijo->claves[t - 1];
        z->productos[0] = hijo->productos[t - 1];
    } else {
        padre->claves[index] = hijo->claves[t - 1];
    }
    padre->numClaves++;
}

void ArbolBPlus::buscarPorCategoria(const std::string &categoria, Nodo *&resultado) const
{
    resultado = nullptr;
    BPlusNode *hoja = encontrarHoja(categoria);
    if (!hoja) return;

    for (int i = 0; i < hoja->numClaves; ++i) {
        if (hoja->claves[i] == categoria) {
            // Copiar la lista para no romper referencias
            Nodo *actual = hoja->productos[i];
            Nodo *prev_copia = nullptr;
            while (actual) {
                Nodo *copia = new Nodo(new Product(*actual->getValue()));
                if (!resultado) resultado = copia;
                if (prev_copia) prev_copia->setNext(copia);
                copia->setPrev(prev_copia);
                prev_copia = copia;
                actual = actual->getNext();
            }
            return;
        }
    }
}

bool ArbolBPlus::eliminarProducto(const std::string &codigoBarra, std::string &errorRollback)
{
    if (!raiz) {
        errorRollback = "Árbol vacío";
        return false;
    }

    // Como no sabemos la categoría por el código de barras, tenemos que buscar por hojas secuencialmente
    BPlusNode *hoja = raiz;
    while (!hoja->esHoja) hoja = hoja->hijos[0];

    bool encontrado = false;
    while (hoja && !encontrado) {
        for (int i = 0; i < hoja->numClaves; ++i) {
            Nodo *actual = hoja->productos[i];
            while (actual) {
                if (actual->getValue()->getBarcode() == codigoBarra) {
                    // Eliminar nodo de la lista doblemente enlazada
                    if (actual->getPrev()) actual->getPrev()->setNext(actual->getNext());
                    else hoja->productos[i] = actual->getNext();

                    if (actual->getNext()) actual->getNext()->setPrev(actual->getPrev());

                    delete actual->getValue();
                    delete actual;
                    encontrado = true;
                    // B+ rebalance is complex. Given the prompt constraints and frequent practical simplifications,
                    // lazy deletion for the keys is acceptable if the list is just emptied.
                    break;
                }
                actual = actual->getNext();
            }
            if(encontrado) break;
        }
        hoja = hoja->siguienteHoja;
    }

    if (!encontrado) {
        errorRollback = "Producto no encontrado en el Árbol B+";
        return false;
    }
    return true;
}

std::string ArbolBPlus::exportarCSV() const
{
    std::ostringstream oss;
    oss << "Nombre,CodigoBarra,Categoria,FechaCaducidad,Marca,Precio,Stock\n";

    if (!raiz) return oss.str();
    
    BPlusNode *hoja = raiz;
    while (!hoja->esHoja) hoja = hoja->hijos[0];

    while (hoja) {
        for (int i = 0; i < hoja->numClaves; ++i) {
            Nodo *actual = hoja->productos[i];
            while (actual) {
                Product* p = actual->getValue();
                oss << p->getName() << ","
                    << p->getBarcode() << ","
                    << p->getCategory() << ","
                    << p->getExpiryDate() << ","
                    << p->getBrand() << ","
                    << p->getPrice() << ","
                    << p->getStock() << "\n";
                actual = actual->getNext();
            }
        }
        hoja = hoja->siguienteHoja;
    }
    return oss.str();
}

static void generarDOTArbolBPlusRec(BPlusNode* nodo, std::ostringstream& ss) {
    if (!nodo) return;
    long id = reinterpret_cast<long>(nodo);
    
    ss << "  node" << id << " [label=\"";
    for(int i=0; i<nodo->numClaves; i++) {
        ss << "<f" << i << "> " << nodo->claves[i];
        if(i != nodo->numClaves - 1) ss << " | ";
    }
    ss << "\"];\n";

    if (!nodo->esHoja) {
        for(int i=0; i<=nodo->numClaves; i++) {
            if(nodo->hijos[i]) {
                long hid = reinterpret_cast<long>(nodo->hijos[i]);
                ss << "  node" << id << ":f" << i << " -> node" << hid << ";\n";
                generarDOTArbolBPlusRec(nodo->hijos[i], ss);
            }
        }
    } else {
        // Enlazar al siguiente nodo hoja
        if (nodo->siguienteHoja) {
            long sigId = reinterpret_cast<long>(nodo->siguienteHoja);
            ss << "  node" << id << " -> node" << sigId << " [color=\"blue\", style=\"dashed\"];\n";
        }
    }
}

std::string ArbolBPlus::generarDOT() const {
    std::ostringstream ss;
    ss << "digraph BPlusTree {\n";
    ss << "  node [shape=record, style=filled, fillcolor=\"#E1BEE7\", color=\"#4A148C\"];\n";
    if (raiz) generarDOTArbolBPlusRec(raiz, ss);
    ss << "}\n";
    return ss.str();
}