#include "pantallaagregarproducto.h"
#include "ui_pantallaagregarproducto.h"

PantallaAgregarProducto::PantallaAgregarProducto(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaAgregarProducto)
{
    ui->setupUi(this);
}

PantallaAgregarProducto::~PantallaAgregarProducto()
{
    delete ui;
}
