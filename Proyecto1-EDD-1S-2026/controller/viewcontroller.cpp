#include "viewcontroller.h"
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "../model/estructuras/listaenlazadanoordenada.h"
#include "../model/estructuras/listaenlazadaordenada.h"
#include "../model/estructuras/arbolb.h"
#include "../model/estructuras/arbolbplus.h"
#include "../model/estructuras/arbolavl.h"

ViewController::ViewController(ListaEnlazadaNoOrdenada* l1, ListaEnlazadaOrdenada* l2, ArbolB* b, ArbolBPlus* bp, ArbolAVL* a)
    : listNoOrd(l1), listOrd(l2), btree(b), bplustree(bp), avl(a)
{
}

void ViewController::renderizarYMostrar(const std::string& dotContent, const QString& baseName, QGraphicsView* view)
{
    QString dotFile = baseName + ".dot";
    QString pngFile = baseName + ".png";

    // Guardar archivo .dot
    QFile file(dotFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << QString::fromStdString(dotContent);
        file.close();
    }

    // Compilar con graphviz
    QProcess process;
    process.start("dot", QStringList() << "-Tpng" << dotFile << "-o" << pngFile);
    process.waitForFinished();

    // Renderizar en el QGraphicsView
    QPixmap pixmap(pngFile);
    if (!pixmap.isNull()) {
        QGraphicsScene* scene = new QGraphicsScene(this);
        scene->addPixmap(pixmap);
        view->setScene(scene);
        view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
}

void ViewController::mostrarListaDesordenada(QGraphicsView *view) {
    if(listNoOrd) renderizarYMostrar(listNoOrd->generarDOT(), "lista_no_ord", view);
}

void ViewController::mostrarListaOrdenada(QGraphicsView *view) {
    if(listOrd) renderizarYMostrar(listOrd->generarDOT(), "lista_ord", view);
}

void ViewController::mostrarArbolB(QGraphicsView *view) {
    if(btree) renderizarYMostrar(btree->generarDOT(), "arbol_b", view);
}

void ViewController::mostrarArbolBPlus(QGraphicsView *view) {
    if(bplustree) renderizarYMostrar(bplustree->generarDOT(), "arbol_bplus", view);
}

void ViewController::mostrarArbolAVL(QGraphicsView *view) {
    if(avl) renderizarYMostrar(avl->generarDOT(), "arbol_avl", view);
}

void ViewController::actualizarVista() {}
void ViewController::productoAgregado() {}
