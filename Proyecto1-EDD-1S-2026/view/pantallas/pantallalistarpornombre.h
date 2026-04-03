#ifndef PANTALLALISTARPORNOMBRE_H
#define PANTALLALISTARPORNOMBRE_H

#include <QWidget>

namespace Ui {
class PantallaListarPorNombre;
}

class PantallaListarPorNombre : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaListarPorNombre(QWidget *parent = nullptr);
    ~PantallaListarPorNombre();

public slots:
    void mostrarResultados(ListaGenerica<Product*>* resultados);

signals:
    void listarSolicitado();

private:
    void limpiarResultados();
    Ui::PantallaListarPorNombre *ui;
};

#endif // PANTALLALISTARPORNOMBRE_H
