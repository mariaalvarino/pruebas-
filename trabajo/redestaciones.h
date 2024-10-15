#ifndef REDESTACIONES_H
#define REDESTACIONES_H

#include "estacionservicio.h"
#include <string>

class RedEstaciones {
private:
    EstacionServicio** estaciones;  // Puntero a puntero para un arreglo dinamico de punteros
    int contadorEstaciones;  // Cantidad actual de estaciones agregadas
    int maxEstaciones;       // Capacidad máxima del arreglo
    float preciosCombustible[3];
public:
    RedEstaciones(int maxEstaciones);  // Constructor con capacidad maxima
    ~RedEstaciones();  // Destructor para liberar memoria
    void agregarEstacion(const EstacionServicio& estacion);  // Agregar una nueva estación
    void eliminarEstacion(const std::string& codigo);  // Eliminar estación por código
    void calcularVentasTotal(float& totalRegular, float& totalPremium, float& totalEcoExtra) const;  // Calcular las ventas totales
    void fijarPreciosCombustible(float precioRegular, float precioPremium, float precioEcoExtra);
    EstacionServicio* getEstacion(int index);  // Retorna puntero para manejar errores sin excepciones
    int getContadorEstaciones() const;  // Retorna la cantidad actual de estaciones
    bool verificarFugas(const std::string& codigoEstacion) const;
    EstacionServicio* getEstacionPorCodigo(const std::string& codigo) const;
};

#endif // REDESTACIONES_H
