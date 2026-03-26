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

public:
    explicit PantallaSistema(QWidget *parent = nullptr);
    ~PantallaSistema();

private:
    Ui::PantallaSistema *ui;
    void mostrarArboles();
    QGraphicsScene *scene1;
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QGraphicsScene *scene4;

private slots:
    void actualizarReloj();
};

#endif // PANTALLASISTEMA_H
