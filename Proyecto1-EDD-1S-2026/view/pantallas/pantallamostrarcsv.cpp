#include "pantallamostrarcsv.h"
#include "ui_pantallamostrarcsv.h"

PantallaMostrarCSV::PantallaMostrarCSV(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaMostrarCSV)
{
    ui->setupUi(this);
}

PantallaMostrarCSV::~PantallaMostrarCSV()
{
    delete ui;
}
