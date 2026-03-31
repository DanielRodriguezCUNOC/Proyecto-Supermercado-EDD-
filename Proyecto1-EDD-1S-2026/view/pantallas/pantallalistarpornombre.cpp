#include "pantallalistarpornombre.h"
#include "ui_pantallalistarpornombre.h"

PantallaListarPorNombre::PantallaListarPorNombre(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaListarPorNombre)
{
    ui->setupUi(this);
}

PantallaListarPorNombre::~PantallaListarPorNombre()
{
    delete ui;
}
