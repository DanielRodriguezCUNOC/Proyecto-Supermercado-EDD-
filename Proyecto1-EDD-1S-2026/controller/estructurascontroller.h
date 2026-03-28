#ifndef ESTRUCTURASCONTROLLER_H
#define ESTRUCTURASCONTROLLER_H
#include <QObject>
#include "estructuras/arbolavl.h"
#include "estructuras/arbolb.h"
#include "estructuras/arbolbplus.h"
#include "estructuras/listaenlazadanoordenada.h"
#include "estructuras/listaenlazadaordenada.h"
class EstructurasController : public QObject
{
    Q_OBJECT
private:
    ListaEnlazadaNoOrdenada *unorderedList;
    ListaEnlazadaOrdenada *listaOrdenada;
    ArbolB *arbolB;
    ArbolBPlus *arbolBPlus;
    ArbolAVL *arbolAVL;

public:
    EstructurasController();
    EstructurasController(
        ListaEnlazadaNoOrdenada *unorderedList,
        ListaEnlazadaOrdenada *listaOrdenada,
        ArbolB *arbolB,
        ArbolBPlus *arbolBPlus,
        ArbolAVL *arbolAVL);
public slots:
    void agregarProducto(std::string name,
                         std::string barcode,
                         std::string category,
                         std::string expiry_date,
                         std::string brand,
                         double price,
                         int stock);
    void eliminarProducto(std::string barcode);
signals:
    void etructurasActualizadas();
};

#endif // ESTRUCTURASCONTROLLER_H
