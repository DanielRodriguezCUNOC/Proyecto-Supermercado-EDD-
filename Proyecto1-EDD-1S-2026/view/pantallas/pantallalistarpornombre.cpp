#include "pantallalistarpornombre.h"
#include "ui_pantallalistarpornombre.h"

PantallaListarPorNombre::PantallaListarPorNombre(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaListarPorNombre)
{
    ui->setupUi(this);
    this->setStyleSheet(this->styleSheet() + ";\n" + R"(
        QPushButton {
            background-color: #2ECC71;
            color: #ECF0F1;
            border-radius: 8px;
            padding: 5px 10px;
            font-size: 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #27AE60;
        }
        QPushButton:pressed {
            background-color: #1E8449;
        }
    )");

}

PantallaListarPorNombre::~PantallaListarPorNombre()
{
    delete ui;
}
