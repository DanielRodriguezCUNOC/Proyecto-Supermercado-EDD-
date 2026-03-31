#ifndef PANTALLALISTARPORNOMBRE_H
#define PANTALLALISTARPORNOMBRE_H

#include <QWidget>

namespace Ui {
class PantallaListarPorNombre;
}

class PantallaListarPorNombre : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaListarPorNombre(QWidget *parent = nullptr);
    ~PantallaListarPorNombre();

private:
    Ui::PantallaListarPorNombre *ui;
};

#endif // PANTALLALISTARPORNOMBRE_H
