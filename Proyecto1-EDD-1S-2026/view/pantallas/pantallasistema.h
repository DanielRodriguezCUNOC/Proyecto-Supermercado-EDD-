#ifndef PANTALLASISTEMA_H
#define PANTALLASISTEMA_H
#include "view/pantallas/pantallaagregarproducto.h"
#include <QWidget>
#include <QGraphicsScene>

namespace Ui
{
    class PantallaSistema;
}

class AppController;
class PantallaSistema : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaSistema(QWidget *parent = nullptr);
    ~PantallaSistema();

    void actualizarReloj();
    void mostrarArboles();
    void btnAgregarClicked();
    void inicializarPantallas();

    void setAppController(AppController *controller) { appController = controller; }

private:
    Ui::PantallaSistema *ui;
    QGraphicsScene *scene1;
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QGraphicsScene *scene4;
    AppController *appController = nullptr;
    PantallaAgregarProducto *agregarProducto = nullptr;

signals:
    void addProducto();
    void archivoCSVSeleccionado(const QString &ruta);
};

#endif // PANTALLASISTEMA_H
