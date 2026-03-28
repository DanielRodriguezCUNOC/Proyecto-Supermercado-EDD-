#include "pantallasistema.h"
#include "ui_pantallasistema.h"
#include <QTimer>
#include <QTime>
#include <QDate>
#include <QGraphicsPixmapItem>
#include <QPixmap>


PantallaSistema::PantallaSistema(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaSistema)
{
    ui->setupUi(this);

    this->setStyleSheet(R"(

QPushButton {
    background-color: #2ECC71;
    color: #ECF0F1;
    border-radius: 8px;
    padding: 5px 10px;
    font-size: 18px;
    font-weight: bold;

    min-width: 141px;
    max-width: 141px;

    min-height: 81px;
    max-height: 81px;
}

QPushButton:hover {
    background-color: #27AE60;
}

QPushButton:pressed {
    background-color: #1E8449;
}

QPushButton#btnEliminar {
    background-color: #E74C3C;
    font-size: 28px;
}

QPushButton#btnEliminar:hover {
    background-color: #ff3923;
}

QPushButton#btnEliminar:pressed {
    background-color: #D4210D;
}

QPushButton#btnAgregar {
    background-color:#2ECC71;
    font-size: 28px;
}

QPushButton#btnAgregar:hover {
    background-color: #2FA35F;
}

QPushButton#btnAgregar:pressed {
    background-color: #1E8449;
}

QPushButton#btnCargarArchivo {
    background-color: #FFAA4F;
    font-size: 18px;

    min-width: 160px;
    max-width: 180px;

    min-height: 65px;
    max-height: 70px;
}

QPushButton#btnCargarArchivo:hover {
    background-color: #F78B17;
}

QPushButton#btnCargarArchivo:pressed {
    background-color: #E67C0B;
}

QPushButton#btnVerArbol {
    background-color: #4DB0F2;
    font-size: 18px;

    min-width: 180px;
    max-width: 200px;

    min-height: 65px;
    max-height: 70px;
}

QPushButton#btnVerArbol:hover {
    background-color: #1DA2FA;
}

QPushButton#btnVerArbol:pressed {
    background-color: #0C88DB;
}

QFrame#header {
    background: qlineargradient(
        x1:0, y1:0,
        x2:1, y2:0,
        stop:0 #1A252F,
        stop:1 #22303C
    );
}

QLabel#tituloHeader {
    color: #ECF0F1;
    font-size: 28px;
    font-weight: bold;
}

QFrame#panelAcciones {
    background: qlineargradient(
        x1:0, y1:0,
        x2:1, y2:0,
        stop:0 #2C313A,
        stop:1 #353B45
    );
}

QFrame#panelContenido{
    background-color: #1E2228;
}

QLCDNumber {
    background-color: #1A252F;
    color: #ff9b2d;
    border: none;
}

QLabel#lblFecha{
    font-size: 28px;
    font-weight: bold
}

)");
    ui->btnBuscarPorNombre->setText("Buscar\npor\nNombre");
    ui->btnBuscarPorCodigo->setText("Buscar\npor\nCodigo");
    ui->btnBuscarPorCategoria->setText("Buscar\npor\nCategoria");
    ui->btnBuscarPorCaducidad->setText("Buscar\npor\nCaducidad");
    ui->btnListarPorNombre->setText("Listar\npor\nNombre");
    ui->btnCompararBusquedas->setText("Comparar\nBusquedas");
    ui->btnCargarArchivo->setText("Cargar Archivo");
    ui->btnVerArbol->setText("Visualizar Arboles");

//* Elimina los botones de minimizar, etc.
setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    //* Evitar doble scroll en los graphics view
    ui->gvListaEnlazadaNoOrdenada->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gvListaEnlazadaNoOrdenada->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gvListaEnlazadaNoOrdenada->viewport()->setAttribute(Qt::WA_AcceptTouchEvents, false);
    ui->scrollArea->setWidgetResizable(true);
    actualizarReloj();

    scene1 = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    scene3 = new QGraphicsScene(this);
    scene4 = new QGraphicsScene(this);

    ui->gvListaEnlazadaNoOrdenada->setScene(scene1);
    ui->gvListaEnlazadaOrdenada->setScene(scene2);
    ui->gvArbolB->setScene(scene3);
    ui->gvArbolBPlus->setScene(scene4);

    mostrarArboles();

}

PantallaSistema::~PantallaSistema()
{
    delete ui;
}

void PantallaSistema::actualizarReloj(){
    QTime hora = QTime::currentTime();
    QDate fecha = QDate::currentDate();

    ui->lcdNumber->display(hora.toString("hh:mm:ss"));
    ui->lblFecha->setText(fecha.toString("dddd dd MMMM yyyy"));

    int msRestantes = 1000 - hora.msec();
    QTimer::singleShot(msRestantes, this, &PantallaSistema::actualizarReloj);
}

void PantallaSistema::mostrarArboles()
{
    scene1->clear();
    scene2->clear();
    scene3->clear();
    scene4->clear();

    QPixmap imagen1("/home/luluwalilith/Imágenes/fondos/266089.jpg");
    QPixmap imagen2("/home/luluwalilith/Imágenes/fondos/1358899.png");
    QPixmap imagen3("/home/luluwalilith/Imágenes/fondos/Claymore.jpg");
    QPixmap imagen4("/home/luluwalilith/Imágenes/fondos/nebulosa-de-carina_23f22b15.png");

    scene1->addPixmap(imagen1);
    scene2->addPixmap(imagen2);
    scene3->addPixmap(imagen3);
    scene4->addPixmap(imagen4);

    ui->gvListaEnlazadaNoOrdenada->fitInView(scene1->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui->gvListaEnlazadaOrdenada->fitInView(scene2->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui->gvArbolB->fitInView(scene3->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui->gvArbolBPlus->fitInView(scene4->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void PantallaSistema::btnAgregarClicked(){
    emit agregarProducto();
}
