#include "appcontroller.h"
AppController::AppController(PantallaSistema* view):
    view(view){

    connect(view, &PantallaSistema::agregarProducto, &AppController::agregarProducto);
}

