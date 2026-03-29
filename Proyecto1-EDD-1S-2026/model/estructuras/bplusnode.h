#pragma once
#include <vector>
#include "../../entidades/product.h"

class BPlusNode {
public:
    bool esHoja;
    std::vector<std::string> claves; // Usar código de barra como clave
    std::vector<Product> productos; // Solo en hojas
    std::vector<BPlusNode*> hijos;
    BPlusNode* siguienteHoja; // Para recorrido por hojas

    BPlusNode(bool hoja) : esHoja(hoja), siguienteHoja(nullptr) {}
    ~BPlusNode();
};
