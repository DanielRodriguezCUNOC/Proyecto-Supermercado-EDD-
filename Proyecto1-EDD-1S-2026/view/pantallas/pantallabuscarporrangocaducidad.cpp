#include "pantallabuscarporrangocaducidad.h"
#include "ui_pantallabuscarporrangocaducidad.h"

PantallaBuscarPorRangoCaducidad::PantallaBuscarPorRangoCaducidad(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaBuscarPorRangoCaducidad)
{
    ui->setupUi(this);
}

PantallaBuscarPorRangoCaducidad::~PantallaBuscarPorRangoCaducidad()
{
    delete ui;
}
