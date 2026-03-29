#include "arbolb.h"
#include "../entidades/product.h"
#include <iostream>
using namespace std;

NodoB::NodoB(int _t, bool _hoja) : t(_t), hoja(_hoja), n(0)
{
    claves = new Product[2 * t - 1];
    hijos = new NodoB *[2 * t];
    for (int i = 0; i < 2 * t; i++) hijos[i] = nullptr;
}

NodoB::~NodoB()
{
    delete[] claves;
    delete[] hijos;
}

void NodoB::recorrer()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!hoja) hijos[i]->recorrer();
        cout << claves[i].getBarcode() << " (" << claves[i].getExpiryDate() << ") ";
    }
    if (!hoja) hijos[i]->recorrer();
}

int NodoB::buscarClave(const std::string &codigo)
{
    int idx = 0;
    while (idx < n && claves[idx].getBarcode() < codigo)
        ++idx;
    return idx;
}

void NodoB::eliminar(const std::string &codigo)
{
    int idx = buscarClave(codigo);

    if (idx < n && claves[idx].getBarcode() == codigo) {
        if (hoja) removerDeHoja(idx);
        else removerDeNoHoja(idx);
    } else {
        if (hoja) {
            // No encontrado en el árbol
            return;
        }
        bool flag = (idx == n);
        if (hijos[idx]->n < t) llenar(idx);
        if (flag && idx > n) hijos[idx - 1]->eliminar(codigo);
        else hijos[idx]->eliminar(codigo);
    }
}

void NodoB::removerDeHoja(int idx)
{
    for (int i = idx + 1; i < n; ++i)
        claves[i - 1] = claves[i];
    n--;
}

void NodoB::removerDeNoHoja(int idx)
{
    Product k = claves[idx];
    if (hijos[idx]->n >= t) {
        Product pred = obtenerPredecesor(idx);
        claves[idx] = pred;
        hijos[idx]->eliminar(pred.getBarcode());
    } else if (hijos[idx + 1]->n >= t) {
        Product suc = obtenerSucesor(idx);
        claves[idx] = suc;
        hijos[idx + 1]->eliminar(suc.getBarcode());
    } else {
        fusionar(idx);
        hijos[idx]->eliminar(k.getBarcode());
    }
}

Product NodoB::obtenerPredecesor(int idx)
{
    NodoB* cur = hijos[idx];
    while (!cur->hoja) cur = cur->hijos[cur->n];
    return cur->claves[cur->n - 1];
}

Product NodoB::obtenerSucesor(int idx)
{
    NodoB* cur = hijos[idx + 1];
    while (!cur->hoja) cur = cur->hijos[0];
    return cur->claves[0];
}

void NodoB::llenar(int idx)
{
    if (idx != 0 && hijos[idx - 1]->n >= t) pedirPrestadoAnterior(idx);
    else if (idx != n && hijos[idx + 1]->n >= t) pedirPrestadoSiguiente(idx);
    else {
        if (idx != n) fusionar(idx);
        else fusionar(idx - 1);
    }
}

void NodoB::pedirPrestadoAnterior(int idx)
{
    NodoB* hijo = hijos[idx];
    NodoB* hermano = hijos[idx - 1];

    for (int i = hijo->n - 1; i >= 0; --i) hijo->claves[i + 1] = hijo->claves[i];
    if (!hijo->hoja) {
        for (int i = hijo->n; i >= 0; --i) hijo->hijos[i + 1] = hijo->hijos[i];
    }
    hijo->claves[0] = claves[idx - 1];
    if (!hijo->hoja) hijo->hijos[0] = hermano->hijos[hermano->n];
    claves[idx - 1] = hermano->claves[hermano->n - 1];
    hijo->n += 1;
    hermano->n -= 1;
}

void NodoB::pedirPrestadoSiguiente(int idx)
{
    NodoB* hijo = hijos[idx];
    NodoB* hermano = hijos[idx + 1];

    hijo->claves[hijo->n] = claves[idx];
    if (!hijo->hoja) hijo->hijos[hijo->n + 1] = hermano->hijos[0];
    claves[idx] = hermano->claves[0];
    for (int i = 1; i < hermano->n; ++i) hermano->claves[i - 1] = hermano->claves[i];
    if (!hermano->hoja) {
        for (int i = 1; i <= hermano->n; ++i) hermano->hijos[i - 1] = hermano->hijos[i];
    }
    hijo->n += 1;
    hermano->n -= 1;
}

void NodoB::fusionar(int idx)
{
    NodoB* hijo = hijos[idx];
    NodoB* hermano = hijos[idx + 1];

    hijo->claves[t - 1] = claves[idx];
    for (int i = 0; i < hermano->n; ++i) hijo->claves[i + t] = hermano->claves[i];
    if (!hijo->hoja) {
        for (int i = 0; i <= hermano->n; ++i) hijo->hijos[i + t] = hermano->hijos[i];
    }
    for (int i = idx + 1; i < n; ++i) claves[i - 1] = claves[i];
    for (int i = idx + 2; i <= n; ++i) hijos[i - 1] = hijos[i];
    hijo->n += hermano->n + 1;
    n--;
    delete hermano;
}

void NodoB::insertarNoLleno(const Product &k)
{
    int i = n - 1;
    if (hoja) {
        // Ordenamos por fecha de caducidad. Si son iguales, por código de barras.
        while (i >= 0 && (claves[i].getExpiryDate() > k.getExpiryDate() || 
              (claves[i].getExpiryDate() == k.getExpiryDate() && claves[i].getBarcode() > k.getBarcode())))
        {
            claves[i + 1] = claves[i];
            i--;
        }
        claves[i + 1] = k;
        n++;
    } else {
        while (i >= 0 && (claves[i].getExpiryDate() > k.getExpiryDate() || 
              (claves[i].getExpiryDate() == k.getExpiryDate() && claves[i].getBarcode() > k.getBarcode())))
        {
            i--;
        }
        i++;
        if (hijos[i]->n == 2 * t - 1) {
            dividirHijo(i, hijos[i]);
            if (claves[i].getExpiryDate() < k.getExpiryDate() ||
                (claves[i].getExpiryDate() == k.getExpiryDate() && claves[i].getBarcode() < k.getBarcode()))
                i++;
        }
        hijos[i]->insertarNoLleno(k);
    }
}

void NodoB::dividirHijo(int i, NodoB *y)
{
    NodoB *z = new NodoB(y->t, y->hoja);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) z->claves[j] = y->claves[j + t];
    if (!y->hoja) {
        for (int j = 0; j < t; j++) z->hijos[j] = y->hijos[j + t];
    }
    y->n = t - 1;

    for (int j = n; j >= i + 1; j--) hijos[j + 1] = hijos[j];
    hijos[i + 1] = z;

    for (int j = n - 1; j >= i; j--) claves[j + 1] = claves[j];
    claves[i] = y->claves[t - 1];
    n++;
}

void NodoB::buscarPorCaducidadRec(const std::string &desde, const std::string &hasta, ListaResultados* resultados)
{
    int i = 0;
    while (i < n && claves[i].getExpiryDate() < desde)
        i++;
        
    for (; i < n && claves[i].getExpiryDate() <= hasta; i++) {
        if (!hoja) hijos[i]->buscarPorCaducidadRec(desde, hasta, resultados);
        resultados->agregar(claves[i]);
    }
    if (!hoja) {
        hijos[i]->buscarPorCaducidadRec(desde, hasta, resultados);
    }
}

// --------------------------------------------------------------------------
// ArbolB
// --------------------------------------------------------------------------

ArbolB::ArbolB(int _t)
{
    raiz = nullptr;
    t = _t;
}

void ArbolB::destruirRec(NodoB* nodo)
{
    if (nodo) {
        if (!nodo->hoja) {
            for (int i = 0; i <= nodo->n; i++) {
                destruirRec(nodo->hijos[i]);
            }
        }
        delete nodo;
    }
}

ArbolB::~ArbolB()
{
    destruirRec(raiz);
}

void ArbolB::insertar(const Product &k)
{
    if (!raiz) {
        raiz = new NodoB(t, true);
        raiz->claves[0] = k;
        raiz->n = 1;
    } else {
        if (raiz->n == 2 * t - 1) {
            NodoB *s = new NodoB(t, false);
            s->hijos[0] = raiz;
            s->dividirHijo(0, raiz);
            int i = 0;
            if (s->claves[0].getExpiryDate() < k.getExpiryDate() ||
               (s->claves[0].getExpiryDate() == k.getExpiryDate() && s->claves[0].getBarcode() < k.getBarcode()))
                i++;
            s->hijos[i]->insertarNoLleno(k);
            raiz = s;
        } else {
            raiz->insertarNoLleno(k);
        }
    }
}

void ArbolB::eliminarPorCodigo(const std::string &codigo)
{
    if (!raiz) return;
    raiz->eliminar(codigo);
    if (raiz->n == 0) {
        NodoB *tmp = raiz;
        if (raiz->hoja) raiz = nullptr;
        else raiz = raiz->hijos[0];
        delete[] tmp->claves;
        delete[] tmp->hijos;
        ::operator delete(tmp); 
    }
}

void ArbolB::imprimir()
{
    if (raiz) raiz->recorrer();
    cout << endl;
}

ListaResultados* ArbolB::buscarPorCaducidad(const std::string &desde, const std::string &hasta)
{
    ListaResultados* resultados = new ListaResultados();
    if (raiz) {
        raiz->buscarPorCaducidadRec(desde, hasta, resultados);
    }
    return resultados;
}
