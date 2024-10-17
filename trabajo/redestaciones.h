#ifndef REDESTACIONES_H
#define REDESTACIONES_H

#include "estacionservicio.h"
#include <string>

class RedEstaciones {
private:
    EstacionServicio** estaciones;  // Puntero a puntero para un arreglo dinámico de punteros a EstacionServicio
    int contadorEstaciones;  // Cantidad actual de estaciones agregadas
    int maxEstaciones;       // Capacidad máxima del arreglo

public:
    RedEstaciones(int maxEstaciones);  // Constructor con capacidad máxima
    ~RedEstaciones();  // Destructor para liberar memoria

    // Métodos
    void agregarEstacion(const EstacionServicio& estacion);  // Agregar una nueva estación
    void eliminarEstacion(const std::string& codigo);  // Eliminar estación por código
    void calcularVentasTotal(float& totalRegular, float& totalPremium, float& totalEcoExtra) const;  // Calcular las ventas totales

    // Método para obtener una estación por índice
    EstacionServicio* getEstacion(int index);  // Retorna puntero para manejar errores sin excepciones
    int getContadorEstaciones() const;  // Retorna la cantidad actual de estaciones
};

#endif // REDESTACIONES_H