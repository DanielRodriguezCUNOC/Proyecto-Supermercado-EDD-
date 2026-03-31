#ifndef PANTALLAELIMINAR_H
#define PANTALLAELIMINAR_H

#include <QWidget>

namespace Ui {
class PantallaEliminar;
}

class PantallaEliminar : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaEliminar(QWidget *parent = nullptr);
    ~PantallaEliminar();

private:
    Ui::PantallaEliminar *ui;
};

#endif // PANTALLAELIMINAR_H
