#include "pantallaeliminar.h"
#include "ui_pantallaeliminar.h"

PantallaEliminar::PantallaEliminar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaEliminar)
{
    ui->setupUi(this);
}

PantallaEliminar::~PantallaEliminar()
{
    delete ui;
}
