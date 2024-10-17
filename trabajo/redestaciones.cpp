#include "redestaciones.h"
#include <iostream>

// Constructor que inicializa la red de estaciones
RedEstaciones::RedEstaciones(int maxEstaciones)
    : contadorEstaciones(0), maxEstaciones(maxEstaciones) {
    estaciones = new EstacionServicio*[maxEstaciones];  // Asignar memoria para arreglo de punteros a estaciones
    for (int i = 0; i < maxEstaciones; ++i) {
        estaciones[i] = nullptr;  // Inicializar todos los punteros en nullptr
    }
}

// Destructor que libera la memoria utilizada
RedEstaciones::~RedEstaciones() {
    for (int i = 0; i < contadorEstaciones; ++i) {
        delete estaciones[i];  // Liberar la memoria de cada estación
    }
    delete[] estaciones;  // Liberar el arreglo dinámico de punteros
}

// Método para agregar una nueva estación
void RedEstaciones::agregarEstacion(const EstacionServicio& estacion) {
    if (contadorEstaciones < maxEstaciones) {
        estaciones[contadorEstaciones] = new EstacionServicio(estacion);  // Asignar memoria y copiar la estación
        contadorEstaciones++;
    } else {
        std::cout << "Límite de estaciones alcanzado." << std::endl;
    }
}

// Método para eliminar una estación por código
void RedEstaciones::eliminarEstacion(const std::string& codigo) {
    for (int i = 0; i < contadorEstaciones; ++i) {
        if (estaciones[i]->getCodigo() == codigo) {
            if (estaciones[i]->tieneSurtidoresActivos()) {
                std::cout << "No se puede eliminar la estación " << codigo << " porque tiene surtidores activos." << std::endl;
                    return;
            }
            delete estaciones[i];  // Liberar la memoria de la estación eliminada
            // Desplazar las estaciones restantes
            for (int j = i; j < contadorEstaciones - 1; ++j) {
                estaciones[j] = estaciones[j + 1];
            }
            estaciones[contadorEstaciones - 1] = nullptr;  // Limpiar el último puntero
            contadorEstaciones--;
            std::cout << "Estación " << codigo << " eliminada." << std::endl;
                return;
        }
    }
    std::cout << "Estación no encontrada." << std::endl;
}

// Método para calcular las ventas totales
void RedEstaciones::calcularVentasTotal(float& totalRegular, float& totalPremium, float& totalEcoExtra) const {
    totalRegular = 0.0;
    totalPremium = 0.0;
    totalEcoExtra = 0.0;
    for (int i = 0; i < contadorEstaciones; ++i) {
        estaciones[i]->calcularVentasPorCategoria(totalRegular, totalPremium, totalEcoExtra);
    }
}

// Método para obtener una estación por índice
EstacionServicio* RedEstaciones::getEstacion(int index) {
    if (index < 0 || index >= contadorEstaciones) {
        std::cout << "Índice fuera de rango: " << index << std::endl;
            return nullptr;  // Retorna nullptr si el índice es inválido
    }
    return estaciones[index];  // Retorna un puntero a la estación
}

// Método que retorna la cantidad actual de estaciones
int RedEstaciones::getContadorEstaciones() const {
    return contadorEstaciones;
}

bool RedEstaciones::verificarFugas(const std::string& codigoEstacion) const {
    EstacionServicio* estacion = getEstacionPorCodigo(codigoEstacion);
    if (estacion) {
        return estacion->verificarFugas();  // Llama al método de la estación para verificar fugas
    } else {
        std::cout << "Estación no encontrada." << std::endl;
        return false; // Retorna false si la estación no se encuentra
    }
}

