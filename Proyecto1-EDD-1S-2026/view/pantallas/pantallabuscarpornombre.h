#ifndef PANTALLABUSCARPORNOMBRE_H
#define PANTALLABUSCARPORNOMBRE_H

#include <QWidget>

namespace Ui {
class PantallaBuscarPorNombre;
}

class PantallaBuscarPorNombre : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaBuscarPorNombre(QWidget *parent = nullptr);
    ~PantallaBuscarPorNombre();

private:
    Ui::PantallaBuscarPorNombre *ui;
    void limpiarResultados();

public slots:
    void mostrarResultados(ListaEnlazadaNoOrdenada* resultados, long tUL, long tOL, long tAVL);

private slots:
    void on_pushButton_clicked(); // Botón Buscar

signals:
    void buscarSolicitado(const QString& nombre);
};

#endif // PANTALLABUSCARPORNOMBRE_H
