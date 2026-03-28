#ifndef PANTALLASISTEMA_H
#define PANTALLASISTEMA_H

#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class PantallaSistema;
}

class PantallaSistema : public QWidget
{
    Q_OBJECT

private:
    Ui::PantallaSistema *ui;
    void mostrarArboles();
    QGraphicsScene *scene1;
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QGraphicsScene *scene4;

private slots:
    void actualizarReloj();
    void btnAgregarClicked();

public:
    explicit PantallaSistema(QWidget *parent = nullptr);
    ~PantallaSistema();

signals:
    void agregarProducto();

};

#endif // PANTALLASISTEMA_H
