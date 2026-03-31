#ifndef PANTALLAAGREGARPRODUCTO_H
#define PANTALLAAGREGARPRODUCTO_H

#include <QWidget>

namespace Ui {
class PantallaAgregarProducto;
}

class PantallaAgregarProducto : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaAgregarProducto(QWidget *parent = nullptr);
    ~PantallaAgregarProducto();

private:
    Ui::PantallaAgregarProducto *ui;
};

#endif // PANTALLAAGREGARPRODUCTO_H
