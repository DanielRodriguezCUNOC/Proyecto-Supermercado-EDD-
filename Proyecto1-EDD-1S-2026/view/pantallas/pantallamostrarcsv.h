#ifndef PANTALLAMOSTRARCSV_H
#define PANTALLAMOSTRARCSV_H

#include <QWidget>

namespace Ui {
class PantallaMostrarCSV;
}

class PantallaMostrarCSV : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaMostrarCSV(QWidget *parent = nullptr);
    ~PantallaMostrarCSV();

private:
    Ui::PantallaMostrarCSV *ui;
};

#endif // PANTALLAMOSTRARCSV_H
