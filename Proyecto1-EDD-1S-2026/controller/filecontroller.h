#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H
#include <QObject>
#include "entidades/product.h"

class FileController: public QObject
{
    Q_OBJECT

public:
    FileController();
    QList<Product> cargarCSV(QString ruta);
};

#endif // FILECONTROLLER_H
