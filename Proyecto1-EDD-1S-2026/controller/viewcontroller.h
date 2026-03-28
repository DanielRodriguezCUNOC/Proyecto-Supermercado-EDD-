#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H
#include <QObject>
#include <QGraphicsView>
class ViewController : public QObject
{
    Q_OBJECT
public:
    ViewController();
    void mostrarListaDesordenada(QGraphicsView *view);
    void mostrarListaOrdenada(QGraphicsView *view);
    void mostrarArbolB(QGraphicsView *view);
    void mostrarArbolBPlus(QGraphicsView *view);
    void mostrarArbolAVL(QGraphicsView *view);

public slots:
    void actualizarVista();
    void productoAgregado();
};

#endif // VIEWCONTROLLER_H
