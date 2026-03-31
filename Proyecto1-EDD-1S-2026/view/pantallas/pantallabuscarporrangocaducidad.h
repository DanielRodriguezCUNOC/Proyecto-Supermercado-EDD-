#ifndef PANTALLABUSCARPORRANGOCADUCIDAD_H
#define PANTALLABUSCARPORRANGOCADUCIDAD_H

#include <QWidget>

namespace Ui {
class PantallaBuscarPorRangoCaducidad;
}

class PantallaBuscarPorRangoCaducidad : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaBuscarPorRangoCaducidad(QWidget *parent = nullptr);
    ~PantallaBuscarPorRangoCaducidad();

private:
    Ui::PantallaBuscarPorRangoCaducidad *ui;
};

#endif // PANTALLABUSCARPORRANGOCADUCIDAD_H
