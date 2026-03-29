#include "bplusnode.h"

BPlusNode::~BPlusNode() {
    for (auto hijo : hijos) {
        delete hijo;
    }
    // No borrar siguienteHoja, ya que es solo un puntero de enlace
}
