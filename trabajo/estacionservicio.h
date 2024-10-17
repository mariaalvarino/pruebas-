#ifndef ESTACIONSERVICIO_H
#define ESTACIONSERVICIO_H

#include "precioscombustible.h"
#include "surtidor.h"
#include "tanque.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>


using namespace std;

class EstacionServicio {
private:
    string nombre;              // Nombre de la estación
    string codigo;              // Código de la estación
    string gerente;             // Gerente de la estación
    string region;              // Región de la estación
    float coordenadas[2];       // [LATITUD, LONGITUD]
    Surtidor surtidores[12];    // Arreglo de surtidores
    int surtidorCount;          // Contador de surtidores
    Tanque tanque;              // Objeto tanque
    

public:
    PreciosCombustible precios;
    // Constructor por defecto
    EstacionServicio();

    // Constructor con parámetros
    EstacionServicio(string n, string c, string g, string r, float lat, float lon, float capReg, float capPrem, float capEco);

    // Métodos
    string getRegion() const;
    string getCodigo() const;
    bool agregarSurtidor(int codigo, string modelo);
    bool eliminarSurtidor(int codigo);
    void reportarLitrosVendidos(string categoria) const;
    void simularVenta(float cantidadSolicitada, const string& categoria, int documentoCliente);
    void mostrarSurtidores() const;
    bool tieneSurtidoresActivos() const;
    void calcularVentasPorCategoria(float& totalRegular, float& totalPremium, float& totalEcoExtra) const;
    Tanque& getTanque();
    float obtenerPrecioPorCategoria(const std::string& categoria) const;
};

#endif // ESTACIONSERVICIO_H